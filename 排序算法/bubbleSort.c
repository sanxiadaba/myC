#include "myUtil.h"
void bubbleSort(int* arr, int size) {

    // 外层循环size-1次就行，因为在其它元素都排好的情况下，最后一个元素是不用排序的
    for (int i = 0; i < size - 1; i++) {
        // 内层循环
        for (int j = 0; j < size - 1 - i; j++) {
            // 让大的数，慢慢"浮"出在最右端
            if (arr[j] > arr[j + 1]) {
                swapInt(&arr[j], &arr[j + 1]);
            }
        }

    }

}