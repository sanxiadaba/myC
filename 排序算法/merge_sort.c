#include "../my_util.h"
// 归并排序
// 用最多的大括号,实现最复杂的逻辑 doge
void merge_sort(array arr, int32 size) {
    // 每次合并的间隔,逐次乘以2
    int32 gap = 1;
    // 定义一些中间变量,左数组起始、右数组起始、左数组结尾（不包括）,右数组结尾（不包括）,辅助数组该记哪个数
    int32 left, right, tmp_left, tmp_right, count;
    // 申请额外空间,辅助数组
    int32* tmp_arr = (ptr_int32)(malloc(sizeof(int32) * size));
    // 初始化数组
    memset(tmp_arr, 0, sizeof(int32) * size);
    // 当gap大于等于数组时,证明数组已经完成了排序
    while (gap < size) {
        // 初始辅助数组的起始位置
        count = 0;
        // 遍历左数组的起始位置 这里left是加两个gap,因为right已经在left的基础上加上了一个gap
        for (int32 i = 0; i < size - gap; i += 2 * gap) {
            // 四个临时变量的值
            left = i;
            right = left + gap;
            tmp_left = left + gap;
            tmp_right = right + gap;
            // 开始遍历
            fori(0, 2 * gap) {
                // 特殊情况,当左右数组中的一个提前到达边界时
                // 右数组到达边界 注意这里的right要>=tmp 而不是==tmpRight 因为right不是递增的,它可能跳跃加
                if (right >= tmp_right || right >= size) {
                    for (int32 j = left; j < tmp_left && j < size; j++) {
                        tmp_arr[count] = arr[j];
                        count++;
                    }
                    break;
                } else if (left == tmp_left || left >= size) // 左数组到达边界的情况
                {
                    for (int32 j = right; j < tmp_right && j < size; j++) {
                        tmp_arr[count] = arr[j];
                        count++;
                    }
                } else {  // 左右数组都没到达边界,那就比较
                    if (arr[left] < arr[right]) {
                        tmp_arr[count] = arr[left];
                        left++;
                    } else {
                        tmp_arr[count] = arr[right];
                        right++;
                    }
                    count++;
                }
            }
        }
        // 复制数组
        memcpy(arr, tmp_arr, sizeof(int32) * size);
        gap *= 2;
    }
    // 释放内存
    free(tmp_arr);
    tmp_arr = NULL;
}

int32 main(void) {
    array arr = { 3,44,38,5,47,15,36,26,27,2,46,4,19,50,48 };
    int32 size = arr_size(arr);
    print_arr(arr, size);
    line_deng_hao();
    merge_sort(arr, size);
    print_arr(arr, size);
    return 0;
}