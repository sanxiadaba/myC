#include "../my_util.h"
// 堆排序的辅助函数,用于维护堆
void heapify(array arr, int size, int i)
{
    // 要维护的堆的坐标
    int largest = i;
    // 左右孩子的坐标
    int lson = i * 2 + 1;
    int rson = i * 2 + 2;
    // 找出父、左右孩子结点中最大的一个
    // 注意这里要加上小于size的条件,防止越界
    if (lson < size && arr[largest] < arr[lson])
        largest = lson;
    if (rson < size && arr[largest] < arr[rson])
        largest = rson;
    // 如果父节点与孩子节点交换了,那就需要继续维护堆
    if (largest != i)
    {
        // 交换
        swap(&arr[largest], &arr[i]);
        // 继续维护
        heapify(arr, size, largest);
    }
}

// 堆排序入口
void heap_sort(array arr, int size)
{
    // 建堆
    // 这里i是各个父节点的坐标
    // 本来下标为i的节点的父节点下标为(i-1)/2 又因为坐标是从0开始的,所以最大的i=size-1
    // (size-1-1)/2 = size/2 -1
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);

    // 排序,这里的size与i>0是精髓
    for (int i = size - 1; i > 0; i--)
    {
        swap(&arr[i], &arr[0]);
        heapify(arr, i, 0);
    }
}

int main(void)
{
    array arr = { 3,44,38,5,47,15,36,26,27,2,46,4,19,50,48 };
    int size = arr_size(arr);
    print_arr(arr, size);
    line(1);
    heap_sort(arr, size);
    print_arr(arr, size);
    return 0;
}