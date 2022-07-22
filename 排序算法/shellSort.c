#include "myUtil.h"
// 希尔排序
void shellSort(int* arr, int size) {
    int gap = size / 2;
    while (gap > 0) {
        // 里面是插入排序
        for (int i = gap; i < size; i++) {
            for (int j = i; j >= gap; j -= gap) {
                if (arr[j] < arr[j - gap]) {
                    swapInt(&arr[j], &arr[j - gap]);
                } else {
                    break;
                }
            }
        }

        gap /= 2;

    }

}