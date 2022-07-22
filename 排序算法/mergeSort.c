#include "myUtil.h"
// 归并排序
// 用最多的大括号，实现最复杂的逻辑 doge
void mergeSort(int* arr, int size) {
    // 每次合并的间隔，逐次乘以2
    int gap = 1;
    // 定义一些中间变量，左数组起始、右数组起始、左数组结尾（不包括），右数组结尾（不包括），辅助数组该记哪个数
    int left, right, tmpLeft, tmpRight, count;
    // 申请额外空间，辅助数组
    int* tmpArr = (int*)(malloc(sizeof(int) * size));
    // 初始化数组
    memset(tmpArr, 0, sizeof(int) * size);
    // 当gap大于等于数组时，证明数组已经完成了排序
    while (gap < size) {
        // 初始辅助数组的起始位置
        count = 0;
        // 遍历左数组的起始位置 这里left是加两个gap，因为right已经在left的基础上加上了一个gap
        for (int i = 0; i < size - gap; i += 2 * gap) {
            // 四个临时变量的值
            left = i;
            right = left + gap;
            tmpLeft = left + gap;
            tmpRight = right + gap;
            // 开始遍历
            for (int i = 0; i < 2 * gap; i++) {
                // 特殊情况，当左右数组中的一个提前到达边界时
                // 右数组到达边界 注意这里的right要>=tmp 而不是==tmpRight 因为right不是递增的，它可能跳跃加
                if (right >= tmpRight || right >= size) {
                    for (int j = left; j < tmpLeft && j < size; j++) {
                        tmpArr[count] = arr[j];
                        count++;
                    }
                    break;
                } else if (left == tmpLeft || left >= size) // 左数组到达边界的情况
                {
                    for (int j = right; j < tmpRight && j < size; j++) {
                        tmpArr[count] = arr[j];
                        count++;
                    }
                } else {  // 左右数组都没到达边界，那就比较
                    if (arr[left] < arr[right]) {
                        tmpArr[count] = arr[left];
                        left++;
                    } else {
                        tmpArr[count] = arr[right];
                        right++;
                    }
                    count++;
                }
            }
        }
        // 复制数组
        memcpy(arr, tmpArr, sizeof(int) * size);
        gap *= 2;
    }
    // 释放内存
    free(tmpArr);
    tmpArr = NULL;
}