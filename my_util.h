#pragma once 							// 保证只被编译一次

/* 常用库导入 */
#include <stdio.h> 						// 输如输出
#include <stdbool.h> 					// 使用 bool true false
#include <stdlib.h> 					// 使用 malloc 与 free
#include <string.h> 					// 使用 memset
#include <math.h> 						// math 计算常用库
#include <errno.h> 						// 错误日志用到的库
#include <time.h> 						// 计算时间用的宏
#include <unistd.h> 					// 封装一些系统 api 比如 sleep
#include <assert.h>						// 使用 assert

/* 常见类型的 typedef */
// 数字定义
typedef signed char					int8; 		// -128 到 127
typedef signed short int			int16; 		// -32,768 到 32,767
typedef signed int					int32; 		// -2,147,483,648 到 2,147,483,647
typedef signed long	long int		int64;  	// -9223372036854775808 到 +9223372036854775807
typedef float 						float32;	// 与 int32 取值范围相同,精度较低

typedef unsigned char				uint8;
typedef unsigned short int			uint16;
typedef unsigned int				uint32;
typedef unsigned long long int		uint64;
typedef double 						float64;

// 常见类型定义
typedef char *string;	// 常量字符串
typedef int array[];	// 一维数组
typedef int *ptr_int32;
typedef int *ptr_int64;
typedef float *ptr_float32;
typedef double *ptr_float64;

// 函数、行号的宏
#define func_and_line __FUNCTION__,__LINE__

// do,while 常用包裹
#define XXX(x...) ({do{x}while(0);})

// 打印日志的宏
#define my_log(fmt,args...)	XXX(																	\
		printf("\x1b[32m" "[%s-%d] (error): "  fmt "(%s)\n" "\x1b[0m",__FUNCTION__,__LINE__,		\
		##args,strerror(errno));																	\
)		

// 分割线
#define line(num) printf("\x1b[31m" #num " ============================== "#num" ============================== " #num "\x1b[0m" "\n");
#define line_deng() printf("\x1b[31m" " ============================================================ " "\x1b[0m" "\n");


// 打印函数运行时间的宏
#define print_time(express) XXX(																	\
		clock_t start,finish;																		\
		start = clock();																			\
		express;																					\
		finish = clock();																			\
		float64 duration = ((float64)((finish-start)) / CLOCKS_PER_SEC);							\
		my_log("函数:%s 运行时间: %lf",#express,duration); 									 		 \
)

// 输出打印一维数组
#define print_arr(arr,arr_size)	 XXX(																\
	printf("%s: [",#arr);																			\
	fori(0, arr_size-1) {																			\
			printf("%lld, ",(int64)(*(arr + i)));													\
	}																								\
	printf("%lld",(int64)arr[arr_size-1]);															\
	printf("]");																					\
	printf("\n");																					\
)

// 判断类型模板宏 
#define type_judges_macro(x,y)	__builtin_types_compatible_p(typeof(x), y)

// 判断类型的宏,判断一个数据是 int、char、float、还是指针 ptr
#define type_judges(x...) ({																			\
	string my_type;																					\
	if(type_judges_macro(x,int64) or type_judges_macro(x,int32) or type_judges_macro(x,int16) or 	\
		type_judges_macro(x,uint64) or type_judges_macro(x,uint32) or type_judges_macro(x,uint16)) {\
		my_type="int";																				\
	}																								\
	else if(sizeof(x)==1) {																			\
		my_type = "char";																			\
	}																								\
	else if(type_judges_macro(x,float64) or type_judges_macro(x,float32)) {							\
		my_type = "float";																			\
	} 																								\
	else{ 																							\
		my_type = "ptr";																			\
	} 																								\
	my_type;																						\
})		


/* 常用的打印输出宏 */
// 打印变量,万能的打印宏
// 这里有一个小细节, %lld 输出时, int32 要转换成 int64 不然无法正常显示负数
// 而 float32 无需转换成 float64 不然会报错(精度丢失?）
#define my_print(x...) XXX(																			\
		string print_type=type_judges(x);															\
		if (print_type=="int") {																	\
			printf("%s: %lld\n",#x,(uint64)(x));													\
		}																							\
		else if(print_type=="char") {																\
			printf("%s: %c\n",#x,x);																\
		}																							\
		else if(print_type=="float") {																\
			printf("%s: %lf\n",#x,x);																\
		}																							\
		else if(print_type=="ptr") {																\
			printf("%s: %p\n",#x,x);																\
		}																							\
)

// 不换行的万能打印宏
#define my_print_t(x...) XXX(																		\
		string print_type=type_judges(x);															\
		if(print_type=="int") {																		\
			printf("%lld\t",(uint64)(x));															\
		}																							\
		else if(print_type=="char") {																\
			printf("%c\t",x);																		\
		}																							\
		else if(print_type=="float") {																\
			printf("%lf\t",x);																		\
		}																							\
		else if(print_type=="ptr") {																\
			printf("%p\t",x);																		\
		}																							\
)

/* 功能函数宏 */
// 返回较大、小数字的宏
#define max_two_num(x,y) 	(x)>(y)?(x):(y) 		// 返回较大数
#define min_two_num(x,y) 	(x)<(y)?(x):(y) 		// 返回较小数

// 查看数组长度,因为这里是通过宏来实现的,不用担心指针降级的问题
#define arr_size(a)				(sizeof((a))/sizeof((a[0])))

// 两个数的平均数,防溢出
#define average_num(a,b) 		(a+(b-a)/2)

// // 判断数字是否在区间	[minx, maxx] 
// // 使用位运算,更快,在的话返回 true ,否则返回 false		 
// #define in_min_max(x,minx,maxx)		({																\
// 		bool ret = false;																			\
// 		if ((int)(((uint)x-(uint)minx) | ((uint)maxx-(uint)x))>= 0){						\
// 			ret = true;																				\
// 		}																							\
// 		ret;																						\
// })

// // 判断数字是否在区间	[0, N]
// #define in_zero_maxx(x,maxx) 		({																\
// 		bool ret = false;																			\
// 			if (((uint)x) <= maxx) {																\
// 			ret = true;																				\
// 		}																							\
// 		ret;																						\
// })


// 交换两个变量,可以是 char、int、uint64 等基本类型,这里使用的 gcc 特有的 typeof 关键字
// 交换两个变量的方法有很多,甚至有很多无消耗内存甚至使用位运算进行的交换
// 但现代编译器已经进行了大量优化,这种使用局部变量的方式反而是最快的
// 注意,传进 a,b 的参数是指针
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
		bool is_odd = true;																			\
		if((x & 1) == 1) {																			\
			is_odd = false;																			\
		}																							\
		is_odd;																						\
})

// 返回数组中的最大值


// 返回数组中的最小值


/* 运算宏 */
// for循环的宏
#define fori(a,b) for(int i=(a); i<(b); i++)
#define forj(a,b) for(int j=(a); j<(b); j++)
#define fork(a,b) for(int k=(a); k<(b); k++)

// 逻辑判断符
#define and &&
#define or ||


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
	// clear();	// 清屏
}
#endif


/* 一些常量 */
// PI 的值
const double PI = 3.141592653589793;
// 误差,在比较两个浮点数相等时使用
const double EPS = 1e-8;
// int 里的"无穷大"
const int INF = 0x3f;
// 真正的无穷大( int 能表示的数字的最大值)
const int INF_REAL = 0x7f;