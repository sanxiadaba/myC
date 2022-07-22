#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>
#include<stdbool.h>
#define debug_n(x) printf("%d\n", x)
#define debug_s(x) printf("%s\n", x)
#define line_x() printf("*****************\n")
#define line_d() printf("=================\n")
// 定义二叉树里的数据类型
typedef int myType;
typedef struct BiTree {
    myType data;
    struct BiTree* leftTree;
    struct BiTree* rightTree;
} BiTree;

// 创建一个节点
BiTree* createNode(int data) {
    BiTree* node = (BiTree*)malloc(sizeof(BiTree));
    node->data = data;
    node->leftTree = node->rightTree = NULL;
    return node;
}

// 插入数据
// 在左右节点非空的情况下，保证左节点小于根节点，右节点大于根节点
void insertNode(int data, BiTree* node) {

    // 等于的话直接结束
    if (data == node->data) {
        return;
    }

    if (data < node->data) {
        // 先判断左节点是否为空
        if (node->leftTree == NULL) {
            node->leftTree = createNode(data);
        } else {
            insertNode(data, node->leftTree);
        }
    } else {
        if (node->rightTree == NULL) {
            node->rightTree = createNode(data);
        } else {
            insertNode(data, node->rightTree);
        }

    }
}

/*
前序遍历，先检查节点值，然后递归遍历左子树和右子树
中序遍历，先遍历左子树，然后检查当前节点值，最后遍历右子树
后序遍历，先递归遍历左右子树，然后检查当前节点值
层次遍历，如名字所言，从第一层开始，一层一层往下遍历
*/

// 先序遍历
void preOrderTraverse(BiTree* node) {
    if (node == NULL) {   //递归出口; 
        return;
    }
    printf("%d\t", node->data); //显示结点值;
    preOrderTraverse(node->leftTree); //先左子树；
    preOrderTraverse(node->rightTree);// 再右子树;
}

// 中序遍历
void inOrderTraverse(BiTree* node) {
    if (node == NULL) {   //递归出口; 
        return;
    }
    preOrderTraverse(node->leftTree); //先左子树；
    printf("%d\t", node->data); //显示结点值;
    preOrderTraverse(node->rightTree);// 再右子树;
}

// 后序遍历
void aftOrderTraverse(BiTree* node) {
    if (node == NULL) {   //递归出口; 
        return;
    }
    preOrderTraverse(node->leftTree); //先左子树；
    preOrderTraverse(node->rightTree);// 再右子树;
    printf("%d\t", node->data); //显示结点值;
}

// 层次遍历
void lelTraverse(BiTree* node) {
    printf("begin level tarvel\n");
    // 先打印根节点的值
    printf("%d\n", node->data);
    int count = 2;
    // 数组里面存的是结构体指针
    BiTree** array = (BiTree**)malloc(sizeof(BiTree*) * count);
    // 先初始化
    for (int i = 0; i < count; i++) {
        array[0] = node->leftTree;
        array[1] = node->rightTree;
    }
    while (true) {
        // 计算数组里多少个Null
        int tmpCount = 0;

        for (int i = 0; i < count; i++) {
            if (array[i] == NULL) {
                tmpCount++;
                printf("NULL\t");
            } else {
                printf("%d\t", array[i]->data);
            }

        }
        printf("\n");
        // 都是null的话就提前退出了
        if (tmpCount == count) {
            break;
        }
        // 对下个数组进行填写数值时用到的指针
        tmpCount = 0;
        // 存储下一层的指针列表
        count *= 2;
        BiTree** tmpArray = (BiTree**)malloc(sizeof(BiTree*) * count);

        for (int i = 0; i < (count / 2); i++) {
            if (array[i] == NULL) {
                tmpArray[tmpCount] = NULL;
                tmpCount++;
                tmpArray[tmpCount] = NULL;
                tmpCount++;
            } else {
                tmpArray[tmpCount] = array[i]->leftTree;
                tmpCount++;
                tmpArray[tmpCount] = array[i]->rightTree;
                tmpCount++;
            }

        }
        free(array);
        array = tmpArray;
    }
    free(array);

}



// 释放内存 
// 采用后序遍历的方式来进行内存释放
void freeTree(BiTree* node) {
    if (node == NULL)
        return;
    freeTree(node->leftTree);
    freeTree(node->rightTree);
    free(node);
}


int main(void) {
    BiTree* root = createNode(9);
    insertNode(4, root);
    insertNode(15, root);
    insertNode(2, root);
    insertNode(6, root);
    insertNode(12, root);
    insertNode(17, root);


    // 结构没有问题
    printf("%d\t", root->data);
    printf("%d\t", root->leftTree->data);
    printf("%d\t", root->rightTree->data);
    printf("%d\t", root->leftTree->leftTree->data);
    printf("%d\t", root->leftTree->rightTree->data);
    printf("%d\t", root->rightTree->leftTree->data);
    printf("%d\n", root->rightTree->rightTree->data);
    // 9       4       15      2       6       12      17

    // 先序遍历
    preOrderTraverse(root);
    // 9       4       2       6       15      12      17
    printf("\n");
    // 中序遍历
    inOrderTraverse(root);
    printf("\n");
    // 4       2       6       9       15      12      17
    // 后序遍历
    aftOrderTraverse(root);
    printf("\n");
    // 4       2       6       15      12      17      9
    // 层次遍历
    lelTraverse(root);
    // 
    // 释放内存
    freeTree(root);
    root = NULL;
    return 0;
}