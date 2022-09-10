#include "../my_util.h"
// 定义二叉树里的数据类型
typedef int my_type;    // 二叉树存放的数据类型时int
typedef struct BiTree
{
    my_type data;
    struct BiTree *left_tree;   // 左子树
    struct BiTree *right_tree;   // 右子树
} BiTree;


// 创建一个节点,返回的是指向树的指针
BiTree *create_node(my_type data)
{
    BiTree *node = (BiTree *)malloc(sizeof(BiTree));    // 开辟空间
    node->data = data;
    node->left_tree = node->right_tree = NULL;
    return node;
}

// 插入数据
// 在左右节点非空的情况下,保证左节点小于根节点,右节点大于根节点
void insert_node(my_type data, BiTree *node)
{

    // 等于的话直接结束,毕竟我们的目的是搜索与更改,重复元素无意义
    if (data == (node->data))
    {
        return;
    }

    if (data < (node->data))
    {
        // 先判断左节点是否为空
        if (node->left_tree == NULL)
        {
            node->left_tree = create_node(data);
        }
        else
        {
            insert_node(data, node->left_tree);
        }
    }
    else
    {
        if (node->right_tree == NULL)
        {
            node->right_tree = create_node(data);
        }
        else
        {
            insert_node(data, node->right_tree);
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
void pre_order_traverse(BiTree *node)
{
    if (node == NULL)
    {   //递归出口; 
        return;
    }
    my_print_t(node->data);    //显示结点值;   
    pre_order_traverse(node->left_tree); //先左子树；
    pre_order_traverse(node->right_tree);// 再右子树;
}

// 中序遍历
void in_order_traverse(BiTree *node)
{
    if (node == NULL)
    {   //递归出口; 
        return;
    }
    pre_order_traverse(node->left_tree); //先左子树；
    my_print_t(node->data);    //显示结点值;
    pre_order_traverse(node->right_tree);// 再右子树;
}

// 后序遍历
void aft_order_traverse(BiTree *node)
{
    if (node == NULL)
    {   //递归出口; 
        return;
    }
    pre_order_traverse(node->left_tree); //先左子树；
    pre_order_traverse(node->right_tree);// 再右子树;
    my_print_t(node->data);    //显示结点值;
}

// 层次遍历
// 核心思想是,每层建立一个指向结构体指针的数组,每回进行更新
void lel_traverse(BiTree *node)
{
    line_deng();
    printf("begin level tarvel\n");
    line_deng();
    // 先打印根节点的值
    my_print_t(node->data);    //显示结点值;
    printf("\n");
    int count = 2;            // 下一层节点的个数
    // 数组里面存的是结构体指针
    BiTree **arr = (BiTree **)malloc(sizeof(BiTree *) * count);
    // 先初始化第二层
    fori(0, 2)
    {
        arr[0] = node->left_tree;
        arr[1] = node->right_tree;
    }
    while (true)
    {
        // 计算数组里多少个Null
        int tmp_count = 0;

        fori(0, count)
        {
            if (arr[i] == NULL)
            {
                tmp_count++;
                printf("NULL\t");
            }
            else
            {
                my_print_t(arr[i]->data);    //显示结点值;
            }

        }
        printf("\n");
        // 都是null的话就提前退出了
        if (tmp_count == count)
        {
            break;
        }
        // 对下个数组进行填写数值时用到的指针
        tmp_count = 0;
        // 存储下一层的指针列表
        count *= 2;
        BiTree **tmp_array = (BiTree **)malloc(sizeof(BiTree *) * count);

        fori(0, count / 2)
        {
            if (arr[i] == NULL)
            {
                tmp_array[tmp_count] = NULL;
                tmp_count++;
                tmp_array[tmp_count] = NULL;
                tmp_count++;
            }
            else
            {
                tmp_array[tmp_count] = arr[i]->left_tree;
                tmp_count++;
                tmp_array[tmp_count] = arr[i]->right_tree;
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
void free_tree(BiTree *node)
{
    if (node == NULL)
    {
        return;
    }
    free_tree(node->left_tree);
    free_tree(node->right_tree);
    free(node);
}


int main(void)
{
    BiTree *root = create_node(9);
    insert_node(4, root);
    insert_node(15, root);
    insert_node(2, root);
    insert_node(6, root);
    insert_node(12, root);
    insert_node(17, root);


    // 结构没有问题
    my_print_t(root->data);
    my_print_t(root->left_tree->data);
    my_print_t(root->right_tree->data);
    my_print_t(root->left_tree->left_tree->data);
    my_print_t(root->left_tree->right_tree->data);
    my_print_t(root->right_tree->left_tree->data);
    my_print_t(root->right_tree->right_tree->data);
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
    free_tree(root);
    root = NULL;
    return 0;
}