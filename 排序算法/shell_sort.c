#include "../my_util.h"
// 希尔排序
void shell_sort(array arr, int32 size) {
    int32 gap = size / 2;
    while (gap > 0) {
        // 里面是插入排序
        fori(gap, size) {
            for (int j = i; j >= gap; j -= gap) {
                if (arr[j] < arr[j - gap]) {
                    swap(&arr[j], &arr[j - gap]);
                } else {
                    break;
                }
            }
        }
        gap /= 2;
    }

}

int32 main(void) {
    array arr = { 3,44,38,5,47,15,36,26,27,2,46,4,19,50,48 };
    int32 size = arr_size(arr);
    print_arr(arr, size);
    line_deng_hao();
    shell_sort(arr, size);
    print_arr(arr, size);
    return 0;
}