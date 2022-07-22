#include <stdio.h> // 输如输出
#include <stdbool.h> // bool true false
#include<stdlib.h> // 使用malloc 与free
#include<string.h> // 使用memset
#include<math.h> // math计算常用库
#define debug_n(x) printf("%d\n", x); // 打印整数
#define debug_s(x) printf("%s\n", x); // 打印字符串
#define debug_p(x) printf("%p\n", x); // 打印指针
#define line_x printf("*****************\n");
#define line_d printf("=================\n");

// 打印数组的函数
void printArr(int* arr, int arrSize) {
    for (int i = 0; i < arrSize; i++) {
        printf("%d  ", *(arr + i));
    }
}

// 两个int数字比较，并返回最大值
int maxInt(int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

// 两个int数字比较，并返回最小值
int minInt(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

// 交换两个Int类型的数字
// 交换两个变量的方法有很多，甚至有很多无消耗内存甚至使用位运算进行的交换
// 但现代编译器已经进行了大量优化，这种使用局部变量的方式反而是最快的
void swapInt(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 交换char
void swapChar(char* a, char* b) {
    if (*a == *b) {
        return;
    }
    char t = *a;
    *a = *b, * b = t;
}


// 反转int数组 注意输arrSize>1
void reverseArr(int* arr, int arrSize) {
    for (int i = 0; i < arrSize / 2; i++) {
        swapInt(&arr[i], &arr[arrSize - 1 - i]);
    }
}

// 翻转数组的指定区间
void reverseArrBeginAndEnd(int* nums, int start, int end) {
    while (start < end) {
        swapInt(&nums[start], &nums[end]);
        start += 1;
        end -= 1;
    }
}

// 翻转字符串
void reverseString(char* s, int sSize) {
    for (int i = 0; i < sSize / 2; i++) {
        swapChar(&s[i], &s[sSize - 1 - i]);
    }
}

// 申请二维数组
int** mallocTwoArray(int nrows, int ncolumns) {
    int** array;
    array = (int**)malloc(nrows * sizeof(int*));
    for (int i = 0; i < nrows; i++) {
        array[i] = (int*)malloc(ncolumns * sizeof(int));
        // 这里初始化数组为0
        memset(array[i], 0, sizeof(int) * ncolumns);
    }
    return array;
}