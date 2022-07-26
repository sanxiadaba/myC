#include "../my_util.h"
// 选择排序
// 每次选择剩下最大的数,插入指定位置
void selection_sort(array arr, int size)
{
    // 最小的数
    int min;
    // 最小的数的索引index
    int index;
    // 同样排序size-1次就行
    fori(0, size - 1)
    {
        min = arr[i];
        // 注意这里的边界条件
        forj(i + 1, size)
        {
            if (arr[j] < min)
            {
                min = arr[j];
                index = j;
            }
        }
        swap(&arr[i], &arr[index]);
    }
}

int main(void)
{
    array arr = { 3,44,38,5,47,15,36,26,27,2,46,4,19,50,48 };
    int size = arr_size(arr);
    print_arr(arr, size);
    line(1);
    selection_sort(arr, size);
    print_arr(arr, size);
    return 0;
}