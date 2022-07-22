#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    // 指向一个数组的指针
    int* mem;
    // 当前已存储数据多少
    int size;
    // 总共多少的容量
    int capcity;
} List;

// 插入元素
void ListAdd(List* p, int n) {
    // 当size==capcity时自动扩容
    if (p->size == p->capcity) {
        int oldCapcity = p->capcity;
        // 扩容到原先的两倍空间
        p->capcity *= 2;
        // 申请空间
        p->mem = (int*)realloc(p->mem, (p->capcity) * sizeof(int));
        memset((p->mem) + oldCapcity, 0, sizeof(int) * oldCapcity);
    }
    // 插入数据
    (p->mem)[p->size] = n;
    // size加一
    (p->size)++;
}

// 从list中取数据
int ListGet(List* p, int i) {
    // 检查数据是否合法
    if (i >= 0 && i < p->size) {
        return p->mem[i];
    }
    // 内存异常的返回值
    return 0xcccccccc;
}

// 创建列表
List* CreateList() {
    // 先定义一个结构体指针
    List* p = (List*)malloc(sizeof(List));
    // 初始化capcity、size、mem
    p->capcity = 8;
    p->size = 0;
    p->mem = (int*)malloc(sizeof(int) * (p->capcity));
    memset(p->mem, 0, sizeof(int) * (p->capcity));
    return p;
}

int main(void) {
    List* list;
    list = CreateList();
    for (int i = 0; i < 17; i++) {
        ListAdd(list, i);
    }
    for (int i = 0; i < 17; i++) {
        printf("%d ", ListGet(list, i));
    }
    // 释放存放数组的空间的内存
    free(list->mem);
    list->mem = NULL;
    // 释放的结构体的内存
    free(list);
    list = NULL;
}