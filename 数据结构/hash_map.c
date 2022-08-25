#include "../my_util.h"
// 扩容因子,当哈希表里"非空bucket"/"总bucket">=0.75时,进行扩容
#define RESIZE_NUM 0.75
// 一开始散列表的长度,全局变量
int bucket_count = 8;

// 存储key-value的结构体链表
typedef struct HashEntry
{
    // key-value 两个都是字符串类型
    // key不可更改
    const char *key;
    char *value;
    struct HashEntry *next;
} HashEntry;


// 散列表
typedef struct
{
    // 指向存放bucket_count个hash_entry指针的数组的头节点
    // 意思是bucket[i] 是指向一个hash_entry的指针
    HashEntry **bucket;
    // 非空的bucket数量,后续计算加载因子时使用
    int size;
    // 已存储的hash_entry数量
    int count;
    // 每个bucket里hash_entry的数量,指向的是长度为bucket_count的数组的头节点
    int *bucket_num;
} HashTable;


// 返回一个初始化的哈希表
// 相当于把bucket指向的hash_entry数组初始化
// 返回一个指向hash_table的指针
HashTable *creat_hash_table()
{
    // 初始化hash_table并返回
    HashTable *hash_table = (HashTable *)malloc(sizeof(HashTable));
    hash_table->size = 0;
    hash_table->count = 0;
    hash_table->bucket = (HashEntry **)malloc(sizeof(HashEntry *) * bucket_count);
    fori(0, bucket_count)
    {
        // 初始化指向空指针
        (hash_table->bucket)[i] = NULL;
    }
    // 使用calloc 顺便初始化
    hash_table->bucket_num = (int *)calloc(bucket_count, sizeof(int) * bucket_count);
    return hash_table;
}

// 不仅仅需要释放 hash_table、bucket、bucket_num,还需要释放bucket里的hash_entry
void free_hash_table(HashTable *hash_table)
{
    // 逐步遍历的hash_table用的hash_entry
    HashEntry *hash_entry, *next_hash_entry;
    fori(0, bucket_count)
    {
        hash_entry = (hash_table->bucket)[i];
        // 如果bucket里第一个元素为空
        if (hash_entry == NULL)
        {
            continue;
        }
        // 散列表不为空
        next_hash_entry = hash_entry->next;
        while (hash_entry != NULL)
        {
            free((char *)(hash_entry->key));
            free((char *)(hash_entry->value));
            free((HashEntry *)hash_entry);
            hash_entry = next_hash_entry;
            if (next_hash_entry != NULL)
            {
                next_hash_entry = next_hash_entry->next;
            }
        }
    }
    free(hash_table->bucket);
    free(hash_table->bucket_num);
    free(hash_table);
}

// 哈希函数,Daniel J.Bernstein 教授发明的,是目前公布的最有效的哈希函数之一
// 也称未 times33 hash
unsigned int DJBHash(const char *str, unsigned int len)
{
    unsigned int hash = 5381;
    for (unsigned int i = 0; i < len; str++, i++)
    {
        hash = ((hash << 5) + hash) + (*str);
    }
    return hash;
}

// 将哈希后的数值映射到散列表上
int key_to_index(const char *key)
{
    // 这里使用了 "按位与" 运算
    // 这里使用的小技巧是,两个数正数进行按位与,结果会生成 0~较小数之间的数(左右闭区间）
    return (DJBHash(key, strlen(key)) & (bucket_count - 1));
}



// 扩容函数,当加载因子(size/bucket_count)超过一定时就触发扩容
// 只需修改bucket、bucket_num即可
void resize_hash(HashTable *hash_table)
{
    hash_table->size = 0;
    // 扩大原来bucket_num
    hash_table->bucket_num = realloc(hash_table->bucket_num, sizeof(int) * bucket_count * 2);
    hash_table->bucket_num = memset(hash_table->bucket_num, 0, sizeof(int) * bucket_count * 2);
    bucket_count *= 2;
    HashEntry **new_bucket = (HashEntry **)malloc(sizeof(HashEntry *) * bucket_count);
    // 初始化new_bucket
    fori(0, bucket_count)
    {
        new_bucket[i] = NULL;
    }
    HashEntry *hash_entry, *next_hash_entry;
    fori(0, bucket_count / 2)
    {
        hash_entry = (hash_table->bucket)[i];
        // 原始bucket里第一个元素为空
        if (hash_entry == NULL)
        {
            continue;
        }
        next_hash_entry = hash_entry->next;
        while (hash_entry != NULL)
        {
            // 在新的bucket的里的索引
            int new_index = key_to_index(hash_entry->key);
            // 新的bucket里面最后一个hash_entry(一开始是起始,下面会进行"寻找")
            HashEntry *finally_entry = new_bucket[new_index];
            ((hash_table->bucket_num)[new_index])++;
            // 新的bucket起始为空的话
            if (finally_entry == NULL)
            {
                ((hash_table)->size)++;
                // 注意,由于浅拷贝 这里只能用 new_bucket[new_index] 而不是 finally_entry
                new_bucket[new_index] = hash_entry;
                new_bucket[new_index]->next = NULL;
            }
            else
            {
                // 确保拿到的是最后一个
                HashEntry *before_hash_entry = finally_entry;
                finally_entry = finally_entry->next;
                while (finally_entry != NULL)
                {
                    before_hash_entry = finally_entry;
                    finally_entry = finally_entry->next;
                }
                before_hash_entry->next = hash_entry;
                before_hash_entry->next->next = NULL;
            }
            hash_entry = next_hash_entry;
            if (next_hash_entry != NULL)
            {
                next_hash_entry = next_hash_entry->next;
            }
        }
    }
    free(hash_table->bucket);
    hash_table->bucket = new_bucket;
}
// 这个了插入和修改是一个方法,如果key在哈希表中已经存在,那么就是修改value,否则就是插入一个节点.
//向哈希表中插入数据
// 为了实现扩容,这里传的时hash_table指针的指针
void insert_entry(HashTable *hash_table, const char *key, char *value)
{
    // 如果size满了,进行扩容
    if (((float32)(hash_table->size) / bucket_count) >= RESIZE_NUM)
    {
        resize_hash(hash_table);
    }
    // 在散列表中的索引位置
    int index = key_to_index(key);
    // 以前value的长度,现在value的长度,如果老的value长度比新的value长的话,使用memcpy即可,
    // 不然的话还要开辟新空间
    int  old_value_len, new_value_len;
    // 存储key-value的实体指针,以及记录上一个hash_entry的指针
    HashEntry *hash_entry, *before_hash_entry;
    hash_entry = (hash_table->bucket)[index];
    // 散列表中的这个hash_entry什么都没存储时
    if (hash_entry == NULL)
    {
        // 更新hash_table里的size count bucket_num
        (hash_table->size)++;
        (hash_table->count)++;
        ((hash_table->bucket_num)[index])++;
        // 加入第一个数据,申请第一个hash_entry的空间
        (hash_table->bucket)[index] = (HashEntry *)malloc(sizeof(HashEntry));
        hash_entry = (hash_table->bucket)[index];
        // 给第一个hash_entry赋值
        hash_entry->key = strdup(key);
        hash_entry->value = strdup(value);
        hash_entry->next = NULL;
        // 新增第一个完成
        return;
    }
    // 在后面存在时执行更改,否则是插入的操作
    while (hash_entry != NULL)
    {
        // 开始对链表进行遍历,寻找key是否已经插入
        // 比较链表的key与要插入的key // 比较成功的话执行"更新”操作
        if (strcmp(hash_entry->key, key) == 0)
        {
            // value相等的情况下
            if (strcmp(hash_entry->value, value))
            {
                return;
            }
            //找到key所在,替换值
            old_value_len = strlen(hash_entry->value);
            new_value_len = strlen(value);
            // new_value的len大于old_value的len
            if (new_value_len > old_value_len)
            {
                // 先释放原先value的内存
                free((char *)(hash_entry->value));
                // 指向新的内存
                hash_entry->value = strdup(value);
            }
            else
            {
                // 新value的len小于old_value的len
                hash_entry->value = memset(hash_entry->value, '\0', old_value_len);
                hash_entry->value = memcpy(hash_entry->value, value, new_value_len);
            }
            return;   // 更新哈希表完成
        }
        before_hash_entry = hash_entry;
        hash_entry = hash_entry->next;
    }
    // 桶中没有找到key,那就在末尾添加
    // 此时的hash_entry指向的是null,而before_hash_entry指向的是最后一个结构体
    before_hash_entry->next = (HashEntry *)malloc(sizeof(HashEntry));
    before_hash_entry->next->key = strdup(key);
    before_hash_entry->next->value = strdup(value);
    before_hash_entry->next->next = NULL;
    (hash_table->count)++;
    ((hash_table->bucket_num)[index])++;
    // 在末尾添加成功
    return;
}

//在哈希表中查找key对应的value
//找到了返回value的地址,没找到返回NULL
char *find_value_by_key(HashTable *hash_table, const char *key)
{
    int index = key_to_index(key);  // bucket的索引
    HashEntry *hash_entry = (hash_table->bucket)[index];
    index = key_to_index(key);
    // bucket没有hash_entry的情况
    if (hash_entry == NULL)
    {
        //这个桶还没有元素
        return NULL;
    }
    while (hash_entry != NULL)
    {
        if (0 == strcmp(key, hash_entry->key))
        {
            //找到了,返回值
            return hash_entry->value;
        }
        hash_entry = hash_entry->next;
    }
    // 遍历了列表,没有找到
    return NULL;
}


// 在哈希表中查找key对应的entry,找到了就删除
void remove_hash_entry(HashTable *hash_table, const char *key)
{
    // 遍历使用的结构体指针
    // 这里需要使用next_hash_entry
    int index = key_to_index(key);
    HashEntry *hash_entry = (hash_table->bucket)[index];
    // 当bucket里没有元素的情况
    if (hash_entry == NULL)
    {
        return;
    }
    // 如果是第一个bucket就匹配到
    if (0 == strcmp(key, hash_entry->key))
    {
        (hash_table->count)--;
        ((hash_table->bucket_num)[index])--;
        free((char *)(hash_entry->key));
        free((char *)(hash_entry->value));
        // hash_entry 后面还有元素的话
        if (hash_entry->next != NULL)
        {
            (hash_table->bucket)[index] = hash_entry->next;
        }
        else
        {
            // hash_entry是该bucket里唯一的元素
            (hash_table->size)--;
            // 别忘了将bucket指向空内存
            (hash_table->bucket)[index] = NULL;
        }
        // 最后释放内存
        free(hash_entry);
        return;
    }
    // 下面的情况都是对应的bucket不为空,且里面元素个数大于1
    // 此时匹配到的bucket绝对不是第一个
    HashEntry *next_hash_entry = hash_entry->next;
    while (next_hash_entry != NULL)
    {
        // 匹配到时
        if (0 == strcmp(key, next_hash_entry->key))
        {
            (hash_table->count)--;
            ((hash_table->bucket_num)[index])--;
            // 释放内存
            free((char *)(next_hash_entry->key));
            free((char *)(next_hash_entry->value));
            // 如果是最后一个
            if (next_hash_entry->next == NULL)
            {
                // 上一个节点的next直接为null即可
                hash_entry->next = NULL;
            }
            else
            {
                // next_hash_entry后面还有
                // 那么就上个节点的next指向next_hash_entry的next即可
                hash_entry->next = next_hash_entry->next;
            }
            free(next_hash_entry);
        }
        hash_entry = next_hash_entry;
        next_hash_entry = next_hash_entry->next;
    }
}

// 打印哈希表
void print_hash_table(HashTable *hash_table)
{
    HashEntry *hash_entry;
    // 打印hash_table的size、count
    my_print(bucket_count);
    printf("非空的bucket个数: %d\t 哈希表里总元素个数: %d\n", hash_table->size, hash_table->count);
    // 打印每个bucket又多少个元素
    fori(0, bucket_count)
    {
        printf("bucket[%d]: %d\n", i, (hash_table->bucket_num)[i]);
    }

    fori(0, bucket_count)
    {
        printf("\nbucket[%d]:\n", i);
        hash_entry = (hash_table->bucket)[i];
        // 第一个元素为空的情况
        if (hash_entry == NULL)
        {
            continue;
        }

        while (hash_entry != NULL)
        {
            printf("\t%s : %s\n", hash_entry->key, hash_entry->value);
            hash_entry = hash_entry->next;
        }
    }
}


int main(void)
{
    HashTable *hash_table = creat_hash_table();
    insert_entry(hash_table, "电脑型号", "1");
    insert_entry(hash_table, "操作系统", "2");
    insert_entry(hash_table, "处理器", "3");
    insert_entry(hash_table, "主板", "4");
    insert_entry(hash_table, "内存", "5");
    insert_entry(hash_table, "主硬盘", "6");
    insert_entry(hash_table, "显卡", "7");
    insert_entry(hash_table, "显示器", "8");
    insert_entry(hash_table, "光驱", "9");
    insert_entry(hash_table, "声卡", "10");
    insert_entry(hash_table, "网卡", "11");
    insert_entry(hash_table, "主板型号", "12");
    insert_entry(hash_table, "芯片组", "13");
    insert_entry(hash_table, "BIOS", "14");
    insert_entry(hash_table, "制造日期", "15");
    insert_entry(hash_table, "主人", "16");
    insert_entry(hash_table, "价格", "17");
    insert_entry(hash_table, "外观", "18");
    insert_entry(hash_table, "软件", "19");
    insert_entry(hash_table, "游戏", "20");
    insert_entry(hash_table, "浏览器", "21");
    insert_entry(hash_table, "数据线", "22");
    insert_entry(hash_table, "充电", "23");
    insert_entry(hash_table, "被子", "24");
    insert_entry(hash_table, "鼠标", "25");
    insert_entry(hash_table, "牛奶", "26");
    insert_entry(hash_table, "方便面", "27");
    insert_entry(hash_table, "巧克力", "28");
    // 移除元素
    remove_hash_entry(hash_table, "数据线");
    printf("\n");
    print_hash_table(hash_table);
    // 分割线
    char *keys[] = { "显示器" , "主人","没有" , "处理器" };
    fori(0, 4)
    {
        char *value = find_value_by_key(hash_table, keys[i]);
        if (value != NULL)
        {
            printf("find %s\t %s\n", keys[i], value);
        }
        else
        {
            printf("not found: %s\n", keys[i]);
        }
    }
    free_hash_table(hash_table);
    printf("OK\n");
    return 0;
}