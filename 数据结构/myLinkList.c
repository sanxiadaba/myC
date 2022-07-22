#include<stdio.h>
/*
01 构建链表
02 初始化链表  注意头节点
03 输出链表
*/

// 先定义结构体
typedef struct Node {
    int data;
    // 结构体里面要包含下个结构体的指针，这样才能实现链表的效果
    struct Node* next;
} Node;

int main(void) {
    // 定义三个结构体,一个头节点,使用头节点的原因是为了方便管理
    Node node1, node2, node3, * head;
    // 给其它结构体赋值
    node1.data = 1;
    node2.data = 2;
    node3.data = 3;
    // 头节点赋值
    head = &node1;
    head->next = &node2;
    node2.next = &node3;
    // 结束
    node3.next = NULL;

    do {
        printf("node data: %d\n", head->data);
        head = head->next; //head->next = head
    } while (head != NULL);

    return 0;
}