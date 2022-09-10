#include "../my_util.h"

typedef int my_data;    // 节点里存储的数据类型
// 定义二叉平衡树
typedef struct AVLNode
{
    my_data data;
    int height;     //  树的高度
    struct AVLNode *left_child, *right_child;   // 左右孩子
}AVLNode;

// 返回一个指向node的指针
AVLNode *create_avl_node()
{
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->left_child = NULL;
    node->right_child = NULL;
    node->height = 1;
    return node;
}

// 返回指向指向AVLTree的指针(指针的指针)
AVLNode **get_avl_tree()
{
    AVLNode **root = (AVLNode **)malloc(sizeof(AVLNode *));
    *root = NULL;   // 一开始指向的是一个空指针
    return root;
}

// 释放以这个节点为根子树的所有内存(后续递归释放)
void free_node(AVLNode *node)
{
    if (node == NULL)
    {
        // 递归出口
        return;
    }
    free_node(node->left_child);
    free_node(node->right_child);
    free(node);
}

// 释放AVLTree内存,传入根指针
void free_avl_tree(AVLNode **root)
{
    // 释放节点内存
    free_node(*root);
    // 最后,释放root内存
    free((AVLNode **)root);
}

// 根节点右旋
void root_right_rotate(AVLNode **root)
{
    // 存在至少一个节点
    assert(*root != NULL);
    // 这个节点的左节点不为空
    assert((*root)->left_child != NULL);
    AVLNode *old_root = *root;
    *root = old_root->left_child;
    old_root->left_child = (*root)->right_child;
    (*root)->right_child = old_root;
    // 开始更新height
    // 注意顺序
    AVLNode *new_root = *root;
    new_root->right_child->height = max_two_num(new_root->right_child->left_child->height, \
        new_root->right_child->right_child)->height;
    new_root->height = max_two_num(new_root->left_child->height, new_root->right_child->height);
}

// 根节点左旋(其实相对于上面的函数,左右颠倒一下就行了)
void right_left_rotate(AVLNode **root)
{
    // 存在至少一个节点
    assert(*root != NULL);
    // 这个节点的左节点不为空
    assert((*root)->right_child != NULL);
    AVLNode *old_root = *root;
    *root = old_root->right_child;
    old_root->right_child = (*root)->left_child;
    (*root)->right_child = old_root;
    // 开始更新height
    // 注意顺序
    AVLNode *new_root = *root;
    new_root->left_child->height = max_two_num(new_root->left_child->left_child->height, \
        new_root->left_child->right_child)->height;
    new_root->height = max_two_num(new_root->left_child->height, new_root->right_child->height);
}




// 插入数据
void insert_data(AVLNode **root, my_data my_data)
{

}

// 查看数据是否存在
bool find_data(AVLNode **root, my_data my_data)
{

}

// 删除数据
void delete_data(my_data data)
{

}


int main(void)
{
    AVLNode **avl_root = get_avl_tree();
    return 0;
}