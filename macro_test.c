// 对my_util.h里功能的测试
#include "my_util.h"

void test_sleep()
{
    // usleep(500 * 1000);   // 休眠指定微秒
    sleep(1);
}

int main(void)
{
    my_log("值为：%d", 3);
    line(1);
    print_time(test_sleep());
    line(2);
    int a[3] = { 1, 2, 3 };
    printf("%d\n", arr_size((a)));
    print_arr(a, arr_size(a));
    line(3);
    int b, c;
    b = 100;
    c = 200;
    swap(&b, &c);
    printf("%d %d\n", b, c);
    printf("%d\n", max_two_num(b, c));
    printf("%d\n", average_num(b, c));
    reverse_arr(a, arr_size(a));
    print_arr(a, arr_size((a)));
    reverse_arr_begin_and_end(a, 0, 1);
    print_arr(a, arr_size((a)));
    if (is_odd_num(a[0]) == true)
    {
        printf("is odd\n");
    }
    else
    {
        printf("not odd\n");
    }
    line_deng();
    int d = 100;
    char e = 'a';
    float32 f = 1.22;
    my_print(d);
    my_print(e);
    my_print(f);

    return EXIT_SUCCESS;
}
