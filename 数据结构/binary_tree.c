#include "../my_util.h"
// 定义二叉树里的数据类型
// #define my_type int32 
// 小细节,这里不能这样,因为typedef是在编译器进行的替换
// #define my_type int 是可以的因为int是基本类型,但#define my_type int32
// 不行,因为此时int32还未定义
typedef int32 my_type;
typedef struct BiTree {
    my_type data;
    struct BiTree* left_tree;
    struct BiTree* right_ree;
} BiTree;

// 创建一个节点
BiTree* create_node(my_type data) {
    BiTree* node = (BiTree*)malloc(sizeof(BiTree));
    node->data = data;
    node->left_tree = node->right_ree = NULL;
    return node;
}

// 插入数据
// 在左右节点非空的情况下,保证左节点小于根节点,右节点大于根节点
void insert_node(my_type data, BiTree* node) {

    // 等于的话直接结束
    if (data == (node->data)) {
        return;
    }

    if (data < (node->data)) {
        // 先判断左节点是否为空
        if (node->left_tree == NULL) {
            node->left_tree = create_node(data);
        } else {
            insert_node(data, node->left_tree);
        }
    } else {
        if (node->right_ree == NULL) {
            node->right_ree = create_node(data);
        } else {
            insert_node(data, node->right_ree);
        }

    }
}

/*
前序遍历,先检查节点值,然后递归遍历左子树和右子树
中序遍历,先遍历左子树,然后检查当前节点值,最后遍历右子树
后序遍历,先递归遍历左右子树,然后检查当前节点值
层次遍历,如名字所言,从第一层开始,一层一层往下遍历
*/

// 先序遍历
void pre_order_traverse(BiTree* node) {
    if (node == NULL) {   //递归出口; 
        return;
    }
    my_print_t(node->data);    //显示结点值;   
    pre_order_traverse(node->left_tree); //先左子树；
    pre_order_traverse(node->right_ree);// 再右子树;
}

// 中序遍历
void in_order_traverse(BiTree* node) {
    if (node == NULL) {   //递归出口; 
        return;
    }
    pre_order_traverse(node->left_tree); //先左子树；
    my_print_t(node->data);    //显示结点值;
    pre_order_traverse(node->right_ree);// 再右子树;
}

// 后序遍历
void aft_order_traverse(BiTree* node) {
    if (node == NULL) {   //递归出口; 
        return;
    }
    pre_order_traverse(node->left_tree); //先左子树；
    pre_order_traverse(node->right_ree);// 再右子树;
    my_print_t(node->data);    //显示结点值;
}

// 层次遍历
void lel_traverse(BiTree* node) {
    line_deng_hao();
    printf("begin level tarvel\n");
    line_deng_hao();
    // 先打印根节点的值
    my_print_t(node->data);    //显示结点值;
    printf("\n");
    int32 count = 2;            // 下一层节点的个数
    // 数组里面存的是结构体指针
    BiTree** arr = (BiTree**)malloc(sizeof(BiTree*) * count);
    // 先初始化
    fori(0, 2) {
        arr[0] = node->left_tree;
        arr[1] = node->right_ree;
    }
    while (true) {
        // 计算数组里多少个Null
        int32 tmp_count = 0;

        fori(0, count) {
            if (arr[i] == NULL) {
                tmp_count++;
                printf("NULL\t");
            } else {
                my_print_t(arr[i]->data);    //显示结点值;
            }

        }
        printf("\n");
        // 都是null的话就提前退出了
        if (tmp_count == count) {
            break;
        }
        // 对下个数组进行填写数值时用到的指针
        tmp_count = 0;
        // 存储下一层的指针列表
        count *= 2;
        BiTree** tmp_array = (BiTree**)malloc(sizeof(BiTree*) * count);

        fori(0, count / 2) {
            if (arr[i] == NULL) {
                tmp_array[tmp_count] = NULL;
                tmp_count++;
                tmp_array[tmp_count] = NULL;
                tmp_count++;
            } else {
                tmp_array[tmp_count] = arr[i]->left_tree;
                tmp_count++;
                tmp_array[tmp_count] = arr[i]->right_ree;
                tmp_count++;
            }

        }
        free(arr);
        arr = tmp_array;
    }
    free(arr);

}



// 释放内存 
// 采用后序遍历的方式来进行内存释放
void freeTree(BiTree* node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left_tree);
    freeTree(node->right_ree);
    free(node);
}


int main(void) {
    BiTree* root = create_node(9);
    insert_node(4, root);
    insert_node(15, root);
    insert_node(2, root);
    insert_node(6, root);
    insert_node(12, root);
    insert_node(17, root);


    // 结构没有问题
    my_print_t(root->data);
    my_print_t(root->left_tree->data);
    my_print_t(root->right_ree->data);
    my_print_t(root->left_tree->left_tree->data);
    my_print_t(root->left_tree->right_ree->data);
    my_print_t(root->right_ree->left_tree->data);
    my_print_t(root->right_ree->right_ree->data);
    printf("\n");
    // 9       4       15      2       6       12      17

    // 先序遍历
    pre_order_traverse(root);
    // 9       4       2       6       15      12      17
    printf("\n");
    // 中序遍历
    in_order_traverse(root);
    printf("\n");
    // 4       2       6       9       15      12      17
    // 后序遍历
    aft_order_traverse(root);
    printf("\n");
    // 4       2       6       15      12      17      9
    // 层次遍历
    lel_traverse(root);
    // 
    // 释放内存
    freeTree(root);
    root = NULL;
    return 0;
}