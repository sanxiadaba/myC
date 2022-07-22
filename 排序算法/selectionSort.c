#include "myUtil.h"
// 选择排序
// 每次选择剩下最大的数，插入指定位置
void selectionSort(int* arr, int size) {
    // 最小的数
    int min;
    // 最小的数的索引index
    int index;
    // 同样排序size-1次就行
    for (int i = 0;i < size - 1;i++) {
        min = arr[i];
        // 注意这里的边界条件
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < min) {
                min = arr[j];
                index = j;
            }
        }
        swapInt(&arr[i], &arr[index]);
    }
}