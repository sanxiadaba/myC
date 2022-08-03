// 双向链表
#include "../my_util.h"
typedef int32 my_type;  // 自定义数据结构
// 先定义结构体
typedef struct Node
{
    my_type data;
    // 结构体里面要包含指向这个结构体的指针,这样才能实现链表的效果
    struct Node *next;
    struct Node *prev;
} Node;

typedef Node *Head;
typedef Node *Last;

// 初始化头节点
Head init_linklist()
{
    Head head = (Node *)malloc(sizeof(Node));
    head->data = 0;     // 头节点存放着后面存储链表的长度
    head->next = head;  // 这里前后节点指向自己也是方便后面的操作
    head->prev = head;
    return head;
}

// 创建一个节点
Node *create_node_linklist(my_type data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}


// 在末尾添加节点
void pushback_linklist(Head head, my_type data)
{
    // 要添加的node
    Last last = create_node_linklist(data);
    // 因为是在末尾,所以要改变四个指向,这里通过一开始初始化head时,巧妙地不用特别考虑了
    head->prev->next = last;
    last->prev = head->prev;
    last->next = head;
    head->prev = last;
    // 节点个数加一
    (head->data)++;
}

// 删除最末尾的节点
void delete_linklist_last(Head head)
{
    // 已经删除完的情况下
    if ((head->data) == 0)
    {
        log_error("链表已空,index:%d", 0);
        assert(false);
        return;
    }
    Last last = head->prev; // 最末尾的元素
    last->prev->next = head;
    head->prev = last->prev;
    free(last);
    (head->data)--;
}


// 在指定节点添加一个节点,第一个传的参数是头节点
void insert_linklist(Head head, int32 index, my_type data)
{
    // 先判断索引是否合法
    if (index<0 or index>(head->data))
    {
        log_error("插入链表的节点索引不合法,index: %d", index);
        assert(0);
        return;
    }

    // 要插入的数据
    Node *node = create_node_linklist(data);
    // 下一个node
    Node *next_node = head;
    // 根据index与head->data的关系,判断是从前往后进行遍历还是从后往前进行遍历
    if (index <= (head->data) / 2)
    {
        // 正向遍历
        fori(0, index)
        {
            next_node = next_node->next;
        }
    }
    else
    {    // 反向遍历到指定位置
        fori(0, (head->data) - index + 1)
        {
            next_node = next_node->prev;
        }
    }
    node->prev = next_node;
    node->next = next_node->next;
    next_node->next->prev = node;
    next_node->next = node;
    // 特殊情况,如果node是最后一个,head->prev的值要变化
    if (index == (head->data))
    {
        head->prev = node;
    }
    // 最后将链表个数更新
    (head->data)++;
}

// 在指定节点删除一个节点,整体逻辑类似在指定位置添加节点
void delete_linklist(Head head, int32 index)
{
    // 先判断索引是否合法
    if (index<0 or index>(head->data))
    {
        log_error("删除链表的节点索引不合法,index: %d", index);
        assert(0);
        return;
    }

    Node *next_node = head;
    // 节点删除,根据index与head->data的关系,判断是从前往后进行遍历还是从后往前进行遍历
    if (index <= (head->data) / 2)
    {
        // 正向遍历
        fori(0, index)
        {
            next_node = next_node->next;
        }
    }
    else
    {    // 反向遍历到指定位置
        fori(0, (head->data) - index + 1)
        {
            next_node = next_node->prev;
        }
    }
    Node *tmp_node = next_node->next;
    next_node->next->next->prev = next_node;
    next_node->next = next_node->next->next;
    free(tmp_node);
    // 特殊情况,如果删除的是最后一个,head->prev的值要变化
    if (index == (head->data))
    {
        head->prev = next_node->next;
    }
    // 最后将链表个数更新
    (head->data)--;
}


// 打印链表
void print_linklist(Head head)
{
    int32 all_num = head->data;
    printf("链表元素的个数:%d\n", head->data);
    fori(0, all_num)
    {
        head = head->next;
        printf("%d ", head->data);
    }
    printf("\n");
}

// 删除链表(释放内存)
void free_linklist(Head head)
{
    int32 all_num = head->data;
    Node *next_node = head->next;
    fori(0, all_num + 1)
    {
        next_node = head->next;
        free(head);
        head = next_node;
    }
}



int32 main(void)
{
    Head head = init_linklist();
    // 在末尾添加元素
    fori(0, 10)
    {
        pushback_linklist(head, i);
    }
    // 在指定位置添加元素
    insert_linklist(head, 10, 200);  // 在末尾添加元素
    insert_linklist(head, 0, -100);  // 在开头添加元素
    insert_linklist(head, 1, 50);  // 在中间添加元素
    log_green("删除元素前%s", "");
    print_linklist(head);
    // 删除元素
    delete_linklist_last(head); // 删除末尾
    // 删除指定位置元素
    delete_linklist(head, 1); // 删除中间
    delete_linklist(head, 0); // 删除开头
    delete_linklist(head, (head->data) - 1); // 删除末尾
    log_magenta("删除元素后%s", "");
    print_linklist(head);
    log_magenta("查看链表个数%d", head->data);
    log_yello("清空链表%s", "");
    free_linklist(head);
    return 0;
}