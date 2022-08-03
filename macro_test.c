// 对my_util.h里功能的测试
#include "my_util.h"

void test_sleep()
{
    sleep(0.5);   // 休眠0.5秒
}

int32 test_return_code(int32 a)
{
    return a;
}


int32 main(void)
{
    printf(xing_xing);
    printf(deng_hao);
    printf(xu_xian);
    int32 a, b, c;
    a = -10;
    b = 2;
    c = 10;
    float64 d, e, f;
    char g, h, i;
    g = 'u';
    ptr_int32 p1 = &a;
    string name = "小明";
    printf("\n");
    printf(name);
    line_deng_hao();
    printf("%s\t", type_judges(d));
    printf("%s\t", type_judges(a));
    printf("%s\t", type_judges(g));
    printf("%s\t", type_judges(p1));
    printf("\n");
    line_xing_xing();
    my_print(d);
    my_print(a);
    my_print(g);
    my_print(p1);
    log_error("错误码为:%d\n", a);
    line_xu_xian();
    print_time(test_sleep());
    line_xu_xian();
    array arr = { 1,2,3,4,5 };
    int32 tmp_arr_size = arr_size(arr);
    printf("原数组\n");
    print_arr(arr, tmp_arr_size);
    printf("翻转数组\n");
    reverse_arr(arr, tmp_arr_size);
    print_arr(arr, tmp_arr_size);
    printf("翻转数组指定区间\n");
    reverse_arr_begin_and_end(arr, 0, 3);
    print_arr(arr, tmp_arr_size);
    line_xu_xian();
    bool tmp_bool;
    tmp_bool = in_zero_maxx(2, 10);
    printf("%d\n", tmp_bool);
    tmp_bool = in_zero_maxx(10, 2);
    printf("%d\n", tmp_bool);
    tmp_bool = in_min_max(2, -1, 10);
    printf("%d\n", tmp_bool);
    tmp_bool = in_min_max(1, 2, 3);
    printf("%d\n", tmp_bool);
    line_deng_hao();
    my_print(max_two_num(10, 20));
    my_print(min_two_num(10.65, -1));
    line_xu_xian();
    my_print(a);
    my_print(b);
    swap(&a, &b);
    my_print(a);
    my_print(b);
    my_print(average_num(a, b));
    line_xu_xian();
    a = is_odd_num(10);
    b = is_odd_num(9);
    my_print(a);
    my_print(b);









    return EXIT_SUCCESS;
}
