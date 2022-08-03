#include "../my_util.h"
void bubble_sort(array arr, int32 size)
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

int32 main(void)
{
    array arr = { 3,44,38,5,47,15,36,26,27,2,46,4,19,50,48 };
    int32 size = arr_size(arr);
    print_arr(arr, size);
    line_deng_hao();
    bubble_sort(arr, size);
    print_arr(arr, size);
    return 0;
}