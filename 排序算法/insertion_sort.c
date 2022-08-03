#include "../my_util.h"
// 插入排序
void insertion_sort(array arr, int32 size)
{
    // 注意边界,插入排序的第一个元素不需要遍历
    fori(1, size)
    {
        // 开始向前比较,这个j-- 是精髓
        // 因为前面的数组都是有序的,所以里面一个if else 即可排好序
        for (int j = i; j > 0; j--)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(&arr[j], &arr[j - 1]);
            }
            else
            {
                // 提前终止的条件
                break;
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
    insertion_sort(arr, size);
    print_arr(arr, size);
    return 0;
}