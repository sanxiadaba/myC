#include "../my_util.h"
// 冒泡排序
void bubble_sort(int arr[], int size)
{
    // 外层循环size-1次就行,因为在其它元素都排好的情况下,最后一个元素是不用排序的
    fori(0, size - 1)
    {
        // 内层循环
        forj(0, size - 1 - i)
        {
            // 让大的数,慢慢"浮"出在最右端
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main(void)
{
    int arr[] = { 3,44,38,5,47,15,36,26,27,2,46,4,19,50,48 };
    int size = sizeof(arr) / sizeof(arr[0]);
    arr_print(arr, size);
    line(1);
    bubble_sort(arr, size);
    arr_print(arr, size);
    return 0;
}