#include "myUtil.h"
// 计数排序
void countSort(int* arr, int size) {
    int min = 0;
    int max = 0;
    int i;
    // 先统计出原数组最大、最小值
    for (i = 0; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        } else if (arr[i] < min) {
            min = arr[i];
        }
    }
    // 开辟max-min+1 大小的数组
    int num = max - min + 1;
    int* tmpNum = (int*)(malloc(sizeof(int) * num));
    // 申请数组后初始化数组
    memset(tmpNum, 0, sizeof(int) * num);
    // 再进行一次遍历，把各个元素“填”进去
    for (i = 0; i < size; i++) {
        // 对应位置的元素加上一
        tmpNum[arr[i] - min]++;
    }
    // 把元素取出来
    int count = 0;
    // 遍历临时数组
    for (i = 0; i < num; i++) {
        // 判断临时数组的对应元素是否在原数组中存在，没有的话就跳过
        if (tmpNum[i] != 0) {
            // 有的话，要进行遍历，因为原数组相同的元素可能存在多个
            for (int j = tmpNum[i]; j > 0; j--) {
                arr[count] = i + min;
                count++;
            }

        }
    }

    // 别忘了释放内存，事实上，申请内存的时候其实就要处理申请的内存
    free(tmpNum);
    tmpNum = NULL;

}