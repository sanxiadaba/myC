#include "../my_util.h"
#define my_type int
#define my_type_ptr ptr_int32 // 储存的是int类型数据
// 动态数组
typedef struct
{
    // 指向一个指定类型的数组的指针
    my_type_ptr arr;
    // 当前已存储数据多少
    int size;
    // 总共多少的容量
    int capcity;
} List;

// 插入元素
void list_add(List *list, my_type data)
{
    // 当size==capcity时自动扩容
    if (list->size == list->capcity)
    {
        int old_capcity = list->capcity;
        // 扩容到原先的两倍空间
        list->capcity *= 2;
        // 申请空间
        list->arr = (my_type_ptr)realloc(list->arr, (list->capcity) * sizeof(my_type));
        memset((list->arr) + old_capcity, 0, sizeof(my_type) * old_capcity);
    }
    // 插入数据
    (list->arr)[list->size] = data;
    // size加一
    (list->size)++;
}

// 从list中取数据
int list_get(List *list, int index)
{
    // 检查数据是否合法
    assert(index >= 0 && index < list->size);
    return (list->arr)[index];
}

// 创建列表
List *create_list()
{
    // 先定义一个结构体指针
    List *list = (List *)malloc(sizeof(List));
    // 初始化capcity、size、arr
    list->capcity = 8;
    list->size = 0;
    list->arr = (my_type_ptr)malloc(sizeof(my_type) * (list->capcity));
    memset(list->arr, 0, sizeof(my_type) * (list->capcity));
    return list;
}




int main(void)
{
    List *list;
    list = create_list();
    fori(0, 17)
    {
        list_add(list, i);
    }
    fori(0, 17)
    {
        printf("%d ", list_get(list, i));
    }
    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 
    // 释放存放数组的空间的内存
    free(list->arr);
    // 释放的结构体的内存
    free(list);
    list = NULL;
}