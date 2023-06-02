#include "../my_util.h"
// 计数排序
void count_sort(int arr[], int size)
{
    int min = 0;
    int max = 0;
    // 先统计出原数组最大、最小值(这里是对正整数排序)
    fori(0, size)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
        else if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    // 开辟max-min+1 大小的数组
    int num = max - min + 1;
    int *tmp_num = (int *)(malloc(sizeof(int) * num));
    // 申请数组后初始化数组
    memset(tmp_num, 0, sizeof(int) * num);
    // 再进行一次遍历,把各个元素"填"进去
    fori(0, size)
    {
        // 对应位置的元素加上一
        tmp_num[arr[i] - min]++;
    }
    // 把元素取出来
    int count = 0;
    // 遍历临时数组
    fori(0, size)
    {
        // 判断临时数组的对应元素是否在原数组中存在,没有的话就跳过
        if (tmp_num[i] != 0)
        {
            // 有的话,要进行遍历,因为原数组相同的元素可能存在多个
            for (int j = tmp_num[i]; j > 0; j--)
            {
                arr[count] = i + min;
                count++;
            }

        }
    }

    // 别忘了释放内存,事实上,申请内存的时候其实就要处理申请的内存
    free(tmp_num);
    tmp_num = NULL;
}



int main(void)
{
    int arr[] = { 3,44,38,5,47,15,36,26,27,2,46,4,19,50,48 };
    int size = sizeof(arr) / sizeof(arr[0]);
    arr_print(arr, size);
    line(1);
    count_sort(arr, size);
    arr_print(arr, size);
    return 0;
}