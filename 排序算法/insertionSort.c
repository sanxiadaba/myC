#include "myUtil.h"
// 插入排序
void insertionSort(int* arr, int size) {
    // 注意边界，插入排序的第一个元素不需要遍历
    for (int i = 1; i < size; i++) {
        // 开始向前比较,这个j-- 是精髓
        // 因为前面的数组都是有序的，所以里面一个if else 即可排好序
        for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j - 1]) {
                swapInt(&arr[j], &arr[j - 1]);
            } else {
                // 提前终止的条件
                break;
            }

        }
    }

}