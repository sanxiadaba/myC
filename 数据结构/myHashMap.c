#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define resizeNum 0.75  // 扩容因子
// 一开始散列表的长度,全局变量
int bucketCount = 16;

// 存储key-value的结构体链表
typedef struct HashEntry {
    // key-value 两个都是字符串类型
    const char* key;
    char* value;
    struct HashEntry* next;
} HashEntry;


// 散列表
typedef struct {
    // 指向bucketCount个HashEntry的数组指针
    HashEntry* bucket;
    // 非空的bucket数量,后续计算加载因子时使用
    int size;
    // 已存储的HashEntry数量
    int count;
    // 每个bucket里hashEntry的数量
    int* bucketNum;
} HashTable;


// 返回一个初始化的哈希表
// 相当于把bucket指向的hashEntry数组初始化
// 注意这里返回的是指针的指针
HashTable** creatHashTable() {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->size = 0;
    hashTable->count = 0;
    hashTable->bucket = (HashEntry*)malloc(sizeof(HashEntry) * bucketCount);
    hashTable->bucketNum = (int*)malloc(sizeof(int) * bucketCount);
    memset(hashTable->bucketNum, 0, sizeof(int) * bucketCount); // 初始化数组
    for (int i = 0; i < bucketCount; i++) {
        (&((hashTable->bucket)[i]))->key = NULL;
        (&((hashTable->bucket)[i]))->value = NULL;
        (&((hashTable->bucket)[i]))->next = NULL;
    }

    HashTable** myHash = (HashTable**)(malloc(sizeof(HashTable*)));
    *myHash = hashTable;
    return myHash;
}

// 不仅仅需要释放 hashTable、bucket申请的空间 还需要释放散列表里对应链表
// 链表里需要释放key-value以及它本身(除了最开始的桶的头节点)
void freeHashTable(HashTable** myHash) {
    // 这个函数
    HashTable* hashTable = *myHash;
    if (myHash == NULL || hashTable == NULL) {
        return;
    }
    // 逐步遍历的hashTable用的hashEntry
    HashEntry* hashEntry, * nextHashEntry;
    hashEntry = nextHashEntry = NULL;
    for (int i = 0; i < bucketCount; i++) {
        // hashTable->bucket[i] 拿到的是一个结构体
        hashEntry = &((hashTable->bucket)[i]);
        // 这个散列表为空，又是第一个，所以不需要释放
        if (hashEntry->key == NULL) {
            continue;
        }
        // 散列表不为空
        free((char*)(hashEntry->key));
        free(hashEntry->value);
        // 如果是bucket里的最后一个
        if (hashEntry->next == NULL) {
            continue;;
        }
        // 释放bucket之后的链表
        nextHashEntry = hashEntry->next;
        hashEntry->next = NULL;
        // 释放nextHashEntry以及它之后的所有hashEntry
        while (nextHashEntry != NULL) {
            free((char*)(nextHashEntry->key));
            free(nextHashEntry->value);
            hashEntry = nextHashEntry;
            nextHashEntry = nextHashEntry->next;
            free(hashEntry);
        }
    }
    free(hashTable->bucket);
    hashTable->bucket = NULL;
    free(hashTable->bucketNum);
    hashTable->bucketNum = NULL;
    free(hashTable);
    *myHash = NULL;
    free(myHash);
}

// 哈希函数,Daniel J.Bernstein 教授发明的,是目前公布的最有效的哈希函数之一
// 也称未 times33 hash
unsigned int DJBHash(const char* str, unsigned int len) {
    unsigned int hash = 5381;
    for (unsigned int i = 0; i < len; str++, i++) {
        hash = ((hash << 5) + hash) + (*str);
    }
    return hash;
}

// 将哈希后的数值映射到散列表上
int keyToIndex(const char* key) {
    return (DJBHash(key, strlen(key)) % bucketCount);
}



// 扩容函数，当加载因子（size/bucketCount）时就触发扩容
void resizeHash(HashTable** myHash) {
    // 原哈希表的指针
    HashTable* oldHash = *myHash;
    HashTable* newHash = (HashTable*)malloc(sizeof(HashTable));
    // 遍历用的变量
    HashEntry* newHashEntry, * oldHashEntry = NULL;
    int newIndex; // char* 在新的hashTable里的的bucket位置
    // 初始化新的hashTable
    newHash->size = 0;
    newHash->count = oldHash->count;
    bucketCount = bucketCount * 2;
    newHash->bucketNum = (int*)malloc(sizeof(int) * bucketCount);
    free(oldHash->bucketNum); // 释放原来的bucketNum数组
    // 扩容
    newHash->bucket = (HashEntry*)malloc(sizeof(HashEntry) * bucketCount);
    memset(newHash->bucketNum, 0, sizeof(int) * bucketCount); // 初始化数组
    // 复制bucket以及后面的数据 // 注意，因为采用了新的bucket数量,所以对应的bucket索引也要改变
    for (int i = 0; i < oldHash->size; i++) {
        oldHashEntry = &((oldHash->bucket)[i]);

        while (oldHashEntry != NULL) {
            if (oldHashEntry->key == NULL) { // 是第一个元素，且为空的话
                break;
            }
            // 非空情况
            newIndex = keyToIndex(oldHashEntry->key);
            newHashEntry = &((newHash->bucket)[newIndex]);
            (newHash->bucketNum)[newIndex]++;
            // 确保newHashEntry是bucket里的最后一个hashEntry
            while (newHashEntry->next != NULL) {
                newHashEntry = newHashEntry->next;
            }
            // 如果是填充第一个bucket里的hashEntry且为空的情况
            // 事实上，经过上面的判定，newHashEntry->key == NULL 只能对应第一个元素且为null的情况
            if (newHashEntry->key == NULL) {
                (newHash->size)++;
                newHashEntry->key = oldHashEntry->key;
                newHashEntry->value = oldHashEntry->value;
            } else { // newHashEntry后面存放值的情况下
                newHashEntry->next = (HashEntry*)malloc(sizeof(HashEntry));
                newHashEntry->next->key = oldHashEntry->key;
                newHashEntry->next->value = oldHashEntry->value;
                newHashEntry->next->next = NULL;
            }
            // 释放除bucket第一个hashEntry之外的结构
            if (oldHashEntry != &((oldHash->bucket)[i])) {
                free(oldHashEntry);
            }

            oldHashEntry = oldHashEntry->next;
        }

    }
    // 释放bucket
    free(oldHash->bucket);
    oldHash->bucket = NULL;
    // 释放oldHash
    free(oldHash);
    *myHash = newHash;
}

// 这个了插入和修改是一个方法,如果key在哈希表中已经存在,那么就是修改value,否则就是插入一个节点。
//向哈希表中插入数据
// 为了实现扩容，这里传的时hashTable指针的指针
void insertEntry(HashTable** myHash, const char* key, char* value) {
    // 输入数据有误，直接返回-1
    if (myHash == NULL || *myHash == NULL || key == NULL || value == NULL) {
        printf("data error");
        return;
    }
    // 如果size满了，进行扩容
    if (((*myHash)->size) / bucketCount >= resizeNum) {
        resizeHash(myHash);
    }
    HashTable* hashTable = *myHash;
    // 添加的话里面hashEntry个数加一
    (hashTable->count)++;
    // 在散列表中的索引位置
    int index = keyToIndex(key);
    (hashTable->bucketNum)[index]++;
    // 以前value的长度，现在value的长度，如果老的value长度比新的value长的划，使用memcpy即可，
    // 不然的话还要开辟新空间
    int  oldValueLen, newValueLen;
    // 存储key-value的实体指针,以及记录上一个hashEntrt的指针
    HashEntry* hashEntry, * beforeHashEntry;
    hashEntry = beforeHashEntry = NULL;
    // 散列表中的这个hashEntry什么都没存储时
    if ((&((hashTable->bucket)[index]))->key == NULL) {
        // 已存储的HashEntry数量加一
        (hashTable->size)++;
        (&((hashTable->bucket)[index]))->key = strdup(key);
        (&((hashTable->bucket)[index]))->value = strdup(value);
        (&((hashTable->bucket)[index]))->next = NULL;
        // 新增完成
        return;
    }

    // 在后面不存在时执行更改,否则是插入的操作
    hashEntry = &((hashTable->bucket)[index]);
    while (hashEntry != NULL) {  // 开始对链表进行遍历,寻找key是否已经插入
        // 比较链表的key与要插入的key // 比较成功的话执行“更新”操作
        if (strcmp(hashEntry->key, key) == 0) {
            // value相等的情况下
            if (strcmp(hashEntry->value, value)) {
                return;
            }
            //找到key所在,替换值
            oldValueLen = strlen(hashEntry->value);
            newValueLen = strlen(value);
            // 新value的len大于oldValue的len
            if (newValueLen > oldValueLen) {
                // 先释放原先value的内存
                free(hashEntry->value);
                // 指向新的内存
                hashEntry->value = strdup(value);
            } else { // 新value的len小于oldValue的len
                memset(hashEntry->value, '\0', oldValueLen);
                memcpy(hashEntry->value, value, newValueLen);
            }
            return;   // 更新哈希表完成
        }
        beforeHashEntry = hashEntry;
        hashEntry = hashEntry->next;
    }
    // 桶中没有找到key，那就在末尾添加
    // 此时的hashEntry指向的是null，而beforeHashEntry指向的是最后一个结构体
    beforeHashEntry->next = (HashEntry*)malloc(sizeof(HashEntry));
    beforeHashEntry->next->key = strdup(key);
    beforeHashEntry->next->value = strdup(value);
    beforeHashEntry->next->next = NULL;
    return; // 在末尾添加成功
}

//在哈希表中查找key对应的value
//找到了返回value的地址，没找到返回NULL
char* findValueByKey(HashTable** myHash, const char* key) {
    HashTable* hashTable = *myHash;
    int index; // bucket的索引
    HashEntry* hashEntry;
    // 输入的数据格式不对
    if (myHash == NULL || hashTable == NULL || key == NULL) {
        return NULL;
    }
    index = keyToIndex(key);
    hashEntry = &((hashTable->bucket)[index]);
    if (hashEntry->key == NULL) {
        return NULL;//这个桶还没有元素
    }
    while (hashEntry != NULL) {
        if (0 == strcmp(key, hashEntry->key)) {
            return hashEntry->value;    //找到了，返回值
        }
        hashEntry = hashEntry->next;
    }
    // 遍历了列表，没有找到
    return NULL;
}


// 在哈希表中查找key对应的entry,找到了就删除
// 没找到返回1,异常返回-1,已删除返回0
int removeHashEntry(HashTable** myHash, const char* key) {
    HashTable* hashTable = *myHash;
    // 遍历使用的结构体指针
    // 这里需要使用nextHashEntry
    HashEntry* hashEntry, * nextHashEntry;
    // 输出数据不对
    if (myHash == NULL || hashTable == NULL || key == NULL) {
        return -1;
    }
    int index = keyToIndex(key);
    hashEntry = &((hashTable->bucket)[index]);
    // 桶为空的话
    if (hashEntry->key == NULL) {
        return 1;
    }

    // 如果是第一个的话
    if (0 == strcmp(key, hashEntry->key)) {
        free((char*)(hashEntry->key));
        free(hashEntry->value);
        // 同时也是最后一个的话
        if (hashEntry->next == NULL) {
            hashTable->size--;
            hashEntry->key = NULL;
            hashEntry->value = NULL;
            // hashEntry->next = NULL; 不用写，因为如果此时hashEntry->next本来就为null
        } else { // 不是最后一个的话 // 相当于把下面一个元素复制到第一个，然后删除第一个
            nextHashEntry = hashEntry->next;
            hashEntry->key = nextHashEntry->key;
            hashEntry->value = nextHashEntry->value;
            hashEntry->next = nextHashEntry->next;
            free(nextHashEntry);
        }
        return 0;
    }
    // 这里nextHashEntry必不可能是第一个了,上面是对第一个的判定
    nextHashEntry = hashEntry->next;
    // 不是第一个的情况
    while (nextHashEntry != NULL) {
        // 匹配到时
        if (0 == strcmp(key, nextHashEntry->key)) {
            // 释放内存
            free((char*)(nextHashEntry->key));
            free(nextHashEntry->value);
            // 如果是最后一个
            if (nextHashEntry->next == NULL) {
                // 上一个节点的next直接为null即可
                hashEntry->next = NULL;
            } else { // nextHashEntry后面还有
                // 那么就上个节点的next指向nextHashEntry的next即可
                hashEntry->next = nextHashEntry->next;
            }
            free(nextHashEntry);
            return 0;
        }
        hashEntry = nextHashEntry;
        nextHashEntry = nextHashEntry->next;
    }
    // 没找到
    return 1;
}

// 打印哈希表
void printHashTable(HashTable** myHash) {
    HashTable* hashTable = *myHash;
    HashEntry* hashEntry;
    if (myHash == NULL || hashTable == NULL) {
        return;
    }
    // 打印hashTable的size、count
    printf("hashSize=%d\thashCount=%d\n", hashTable->size, hashTable->count);
    // 打印每个bucket又多少个元素
    for (int i = 0; i < bucketCount; i++) {
        if ((hashTable->bucketNum)[i] != 0) {
            printf("bucket[%d]: %d\n", i, (hashTable->bucketNum)[i]);
        }
    }

    for (int i = 0; i < bucketCount; i++) {
        printf("\nbucket[%d]:\n", i);
        hashEntry = &((hashTable->bucket)[i]);
        while (hashEntry->key != NULL) {
            printf("\t%s\t=\t%s\n", hashEntry->key, hashEntry->value);
            if (hashEntry->next == NULL) {
                break;
            }
            hashEntry = hashEntry->next;
        }
    }
}


int main(void) {
    HashTable** myHash = creatHashTable();
    int code; // 判断删除状态的状态码
    insertEntry(myHash, "电脑型号", "华硕 X550JK 笔记本电脑");
    insertEntry(myHash, "操作系统", "Windows 8.1 64位 (DirectX 11)");
    insertEntry(myHash, "处理器", "英特尔 Core i7 - 4710HQ @ 2.50GHz 四核");
    insertEntry(myHash, "主板", "华硕 X550JK(英特尔 Haswell)");
    insertEntry(myHash, "内存", "4 GB(Hynix / Hyundai)");
    insertEntry(myHash, "主硬盘", "日立 HGST HTS541010A9E680(1 TB / 5400 转 / 分)");
    insertEntry(myHash, "显卡", "NVIDIA GeForce GTX 850M       (2 GB / 华硕)");
    insertEntry(myHash, "显示器", "奇美 CMN15C4(15.3 英寸)");
    insertEntry(myHash, "光驱", "松下 DVD - RAM UJ8E2 S DVD刻录机");
    insertEntry(myHash, "声卡", "Conexant SmartAudio HD @ 英特尔 Lynx Point 高保真音频");
    insertEntry(myHash, "网卡", "瑞昱 RTL8168 / 8111 / 8112 Gigabit Ethernet Controller / 华硕");
    insertEntry(myHash, "主板型号", "华硕 X550JK");
    insertEntry(myHash, "芯片组", "英特尔 Haswell");
    insertEntry(myHash, "BIOS", "X550JK.301");
    insertEntry(myHash, "制造日期", "06 / 26 / 2014");
    insertEntry(myHash, "主人", "就是我");
    insertEntry(myHash, "价格", "六十张红色毛主席");
    insertEntry(myHash, "主硬盘1", "换了个120G的固态");
    insertEntry(myHash, "主硬盘2", "换了个120G的固态");
    insertEntry(myHash, "主硬盘3", "换了个120G的固态");
    insertEntry(myHash, "主硬盘4", "换了个120G的固态");
    insertEntry(myHash, "主硬盘5", "换了个120G的固态");
    insertEntry(myHash, "主硬盘6", "换了个120G的固态");
    insertEntry(myHash, "主硬盘7", "换了个120G的固态");
    insertEntry(myHash, "主硬盘8", "换了个120G的固态");
    insertEntry(myHash, "主硬盘9", "换了个120G的固态");
    insertEntry(myHash, "主硬盘10", "换了个120G的固态");
    insertEntry(myHash, "主硬盘11", "换了个120G的固态");
    insertEntry(myHash, "主硬盘12", "换了个120G的固态");
    insertEntry(myHash, "主硬盘13", "换了个120G的固态");
    insertEntry(myHash, "主硬盘14", "换了个120G的固态");
    insertEntry(myHash, "主硬盘15", "换了个120G的固态");
    insertEntry(myHash, "主硬盘16", "换了个120G的固态");

    code = removeHashEntry(myHash, "主板型号");
    switch (code) {
    case 0:
        printf("删除成功\n");
        break;
    case 1:
        printf("未找到\n");
        break;
    case -1:
        printf("数据异常\n");
        break;
    default:
        break;
    }
    printf("\n");

    printHashTable(myHash);
    char* keys[] = { "显示器" , "主人","没有" , "处理器" };
    for (int i = 0; i < 4; ++i) {
        char* value = findValueByKey(myHash, keys[i]);
        if (value != NULL) {
            printf("find %s\t=\t%s\n", keys[i], value);
        } else {
            printf("not found\t %s\n", keys[i]);
        }
    }

    freeHashTable(myHash);
    myHash = NULL;
    return 0;
}