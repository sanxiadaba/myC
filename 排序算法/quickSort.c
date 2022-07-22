#include "myUtil.h"
// 快排
// 因为快排用到了递归函数调用，所以会多两个左右界参数
// 其本质是“挖坑”与“填坑”
void quickSort(int* arr, int size, int left, int right) {
    // 记录下没有改变前的左右边界，作为递归函数的传参
    int tmpLeft = left;
    int tmpRight = right;
    // 递归的终止条件
    if (left >= right) {
        return;
    } else {
        // 比较基准(或者说坑位？)
        int pivot = left;
        // 因为默认选取最左边为比较基准，所以这里left向右移动1
        left++;
        // 当此数组被基准左右分开之前，按照一定规则进行交换
        while (left <= right) {
            // 注意左指针与右指针的指向的数字与基准的比较规则是不同的
            // 并且，先是右边的“填坑”，然后左边的再“填”
            if (arr[right] >= arr[pivot]) {
                // 直到找到“坑位”
                right--;
                continue;
            }
            // 右边找到“坑位”，开始“填坑”
            swapInt(&arr[pivot], &arr[right]);
            // "坑位"转移
            pivot = right;
            // 指针移动
            right--;

            // 左边开始“找坑”
            if (arr[left] <= arr[pivot]) {
                // 直到找到“坑位”
                left++;
                continue;
            }
            // 左边找到“坑位”，开始“填坑”
            swapInt(&arr[pivot], &arr[left]);
            // "坑位"转移
            pivot = left;
            // 指针移动
            left++;
        }
        // 讲过上面的“挖坑”、“填坑”操作后，数组以pivot分界线，基本有序，开始对左右数组再进行快排
        quickSort(arr, size, tmpLeft, pivot - 1);
        quickSort(arr, size, pivot + 1, tmpRight);

    }

}