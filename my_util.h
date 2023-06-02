#pragma once 							// 保证只被编译一次

/* 常用库导入 */
#include <stdio.h> 						// 输入输出
#include <stdbool.h> 					// 使用 true false
#include <stdlib.h> 					// 使用 malloc 与 free
#include <string.h> 					// 使用 memset
#include <math.h> 						// math 计算常用库
#include <time.h> 						// 计算时间用的宏
#include <unistd.h> 					// 封装一些系统 api 比如 sleep
#include <assert.h>						// 使用 assert


/* 常见类型的 typedef */
// 数字定义
// typedef signed char					int8; 		// -128 到 127
// typedef signed short int			int16; 		// -32,768 到 32,767
// typedef signed int					int32; 		// -2,147,483,648 到 2,147,483,647
typedef signed long	long int		int64;  	// -9223372036854775808 到 +9223372036854775807
// typedef float 						float32;	// 与 int32 取值范围相同,精度较低


typedef unsigned char				uchar;
// typedef unsigned short int			uint16;
// typedef unsigned int				uint32;
typedef unsigned long long int		uint64;
// typedef double 						float64;


// 常见类型定义
// typedef const char *string;	// 常量字符串
// typedef int array[];	// 一维数组
// typedef int *ptr_int32;
// typedef int *ptr_int64;
// typedef float *ptr_float32;
// typedef double *ptr_float64;


// 函数、行号的宏
// #define func_and_line __FUNCTION__,__LINE__


// do,while 常用包裹
#define __XXX(x...) ({do{x}while(0);})


// 打印不同颜色字符串
#define __print_color(back_color,font_color,str) printf("\033[" #back_color ";" #font_color "m" str "\033[0m")
// 红色
#define __print_color_red(str) __print_color(40,31,str)
// 绿色
#define __print_color_green(str) __print_color(40,32,str)
// 黄色
#define __print_color_yello(str) __print_color(40,33,str)
// 蓝色
#define __print_color_blue(str) __print_color(40,34,str)
// 紫色
#define __print_color_purple(str) __print_color(40,35,str)
// 白色
#define __print_color_white(str) __print_color(40,37,str)
// back_color表示字体的背景颜色 font_color代表字体颜色 str表示字符串
// 部分颜色代码:
// 字背景颜色: 40--49                字颜色: 30--39
// 40: 黑                           30: 黑
// 41: 红                           31: 红
// 42: 绿                           32: 绿
// 43: 黄                           33: 黄
// 44: 蓝                           34: 蓝
// 45: 紫                           35: 紫
// 46: 深绿                         36: 深绿
// 47：白色                         37：白色



// 打印什么函数、第几行
#define __func_and_line()	printf("\033[40;32m[%s-%d]: \033[0m",__FUNCTION__,__LINE__);

// 分割线
#define line(num) __print_color_green("分割线 " #num " ============================== "#num" ============================== " #num "\n");


#define fori(a,b) for(int i=(a); i<(b); i++)
#define forj(a,b) for(int j=(a); j<(b); j++)
#define fork(a,b) for(int k=(a); k<(b); k++)

// 逻辑判断符
#define and &&
#define or ||

// 打印日志的宏
#define __my_log(fmt,args...)	 printf("\x1b[32m" "[%s-%d]: "  fmt "\n" "\x1b[0m",__FUNCTION__,__LINE__,##args);


// 打印函数运行时间的宏
#define func_time(express) __XXX(																	\
		clock_t start,finish;																		\
		start = clock();																			\
		express;																					\
		finish = clock();																			\
		double duration = ((double)((finish-start)) / CLOCKS_PER_SEC);								\
		__my_log("函数:%s 运行时间: %lf",#express,duration); 									 	 \
)

// 返回较大、小数字的宏
#define max_two_num(x,y) 	(x)>(y)?(x):(y) 		// 返回较大数
#define min_two_num(x,y) 	(x)<(y)?(x):(y) 		// 返回较小数


// 两个数的平均数,防溢出
#define average_two_num(a,b) 		(a+(b-a)/2)

// 交换两个类型相同的变量
#define swap(a,b) ({																				\
		typeof(*a) temp = *a;																		\
		*a = *b;																					\
		*b = temp;																					\
})

// 翻转数组
#define reverse_arr(arr,arr_size)	XXX(															\
		fori(0,arr_size/2){																			\
			swap(&arr[i],&arr[arr_size-1-i]);														\
		}																							\
)

// 翻转数组的指定区间 前后都是闭区间
#define reverse_arr_begin_and_end(arr,start,end)	({												\
		int left = start;																			\
		int right = end;																			\
		do{																							\
			swap(&(arr[left]),&(arr[right]));														\
			left++;																					\
			right--;																				\
		}while(left < right);																		\
})

// 判断是奇数还是偶数
// 这里是使用的 "按位与" 进行的判断
// "按位与" 也就是 & 符号的规则是两个 bit 位都为 1 结果才为 1
// 我们知道,计算机存储数据是以二进制格式存储的
// 一个数字,如果是偶数,其二进制数字末尾必然是 0 
// 与 1 进行 "按位与" ,其实本质是判断最后一位是 1 还是 0
// 最后一位是 1 的话返回 false(奇数)
#define is_odd_num(x) ({																			\
		bool is_odd = false;																		\
		if((x & 1) == 1) {																			\
			is_odd = true;																			\
		}																							\
		is_odd;																						\
})


// clear清屏
#ifdef _WIN32
#define clear()   system("cls"); 			// win 清屏命令
#elif __linux__
#define clear()   system("clear"); 			// linux 清屏命令
#elif __APPLE__								// mac 系统
#endif


/* windows情况下的提前运行 */
#ifdef _WIN32
static __attribute__((constructor)) void before_main()
{
	system("chcp 65001");
	clear();	// 清屏
}
#endif


/* 一些常量 */
// PI 的值
const double PI = 3.141592653589793;
// 误差,在比较两个浮点数相等时使用
const double EPS = 1e-8;
// // int 里的"无穷大"
// const int INF = 0x3f;
// // 真正的无穷大( int 能表示的数字的最大值)
// const int INF_REAL = 0x7f;


// 判断两个变量是否相同（前面变量是否是后面的类型）
#define __type_judges(x,type)	__builtin_types_compatible_p(typeof(x), type)



// 判断变量的类型
#define __judge_var(var) _Generic((var), 	\
	int:"int",								\
    unsigned int:"uint",					\
	char:"char", 							\
	unsigned char:"uchar", 					\
	float:"float", 							\
	int64:"int64", 							\
	uint64:"uint64", 						\
	double:"double")


// 打印输出变量
#define my_printf(x) _Generic((x), 						\
		int: printf("%s: %d\n",#x,x),					\
		unsigned int: printf("%s: %d\n",#x,x),			\
		char: printf("%s: %d\n", #x, x), 				\
		float: printf("%s: %f\n",#x,x),					\
		unsigned char: printf("%s: %d\n",#x,x),			\
		char *: printf("%s: %s\n",#x,x),				\
		int64: printf("%s: %lld\n",#x,x),				\
		uint64: printf("%s: %lld\n",#x,x),				\
		double: printf("%s: %lf\n", #x, x))


// 输出打印一维数组
#define arr_print(arr,arr_size)	 __XXX(																\
	char * tmp =__judge_var(arr[0]);																\
	printf("%s: [", #arr);																			\
	if(tmp=="int"  or tmp=="char" or tmp=="uchar"){													\
		fori(0, arr_size-1) {																		\
				printf("%d, ",(*(arr + i)));														\
		}																							\
		printf("%d",arr[arr_size-1]);																\
	}																								\
	if(tmp=="uint"){																				\
		fori(0, arr_size-1) {																		\
				printf("%u, ",(*(arr + i)));														\
		}																							\
		printf("%u",arr[arr_size-1]);																\
	}																								\
	if(tmp=="int64"){																				\
		fori(0, arr_size-1) {																		\
				printf("%lld, ",(*(arr + i)));														\
		}																							\
		printf("%lld",arr[arr_size-1]);																\
	}																								\
	if(tmp=="uint64"){																				\
		fori(0, arr_size-1) {																		\
				printf("%llu, ",(*(arr + i)));														\
		}																							\
		printf("%llu",arr[arr_size-1]);																\
	}																								\
	if(tmp=="float"){																				\
		fori(0, arr_size-1) {																		\
				printf("%f, ",(*(arr + i)));														\
		}																							\
		printf("%f",arr[arr_size-1]);																\
	}																								\
	if(tmp=="double"){																				\
		fori(0, arr_size-1) {																		\
				printf("%lf, ",(*(arr + i)));														\
		}																							\
		printf("%lf",arr[arr_size-1]);																\
	}																								\
	printf("]");																					\
	printf("\n");																					\
)
