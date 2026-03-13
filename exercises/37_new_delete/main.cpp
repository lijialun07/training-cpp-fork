#include "../exercise.h"
#include <iostream>

// READ: new/delete <https://zh.cppreference.com/w/cpp/memory/new/operator_new>
// READ: 配对使用 <https://lb3fn675fh.feishu.cn/wiki/VUp6wCMGyikdiDkDM51cKPQenAg>

int main(int argc, char **argv) {
    // 练习 1: 基本的 new 和 delete
    // 分配一个 int 类型的动态内存
    int *p_int = new int(10);
    ASSERT(*p_int == 10, "p_int 指向的值应该是 10");
    // 释放内存
    delete p_int;
    // ASSERT(*p_int == ?, "访问已释放的内存是未定义行为，这里只是为了演示，实际不应访问"); // 取消注释这行会导致未定义行为

    // 练习 2: 基本的 new[] 和 delete[]
    // 分配一个包含 5 个 int 的数组
    int *p_arr = new int[5]{1, 2, 3, 4, 5};
    ASSERT(p_arr[0] == 1, "数组第一个元素应该是 1");
    ASSERT(p_arr[4] == 5, "数组第五个元素应该是 5");
    // 释放数组内存
    delete[] p_arr;
    // ASSERT(p_arr[0] == ?, "访问已释放的内存是未定义行为"); // 取消注释这行会导致未定义行为

    // 练习 3: 错误使用 delete (应该用 delete[])
    // 分配数组
    int *p_arr_err = new int[3]{10, 20, 30};
    // 错误地使用 delete 而不是 delete[] 来释放数组
    // delete p_arr_err; // 这会导致未定义行为，可能只释放了第一个元素的内存，或者程序崩溃
    // 正确的释放方式应该是 delete[] p_arr_err;
    // 由于 delete p_arr_err 是未定义行为，我们无法用 ASSERT 来可靠地测试其后果。
    // 请思考：为什么必须使用 delete[] 释放 new[] 分配的内存？
    // 提示：编译器需要知道要调用多少次析构函数（对于类类型）以及释放多少内存。
    delete[] p_arr_err; // 使用正确的释放方式

    // 练习 4: 错误使用 delete[] (应该用 delete)
    // 分配单个对象
    int *p_int_err = new int(100);
    // 错误地使用 delete[] 而不是 delete 来释放单个对象
    // delete[] p_int_err; // 这同样是未定义行为
    // 正确的释放方式应该是 delete p_int_err;
    // 请思考：为什么必须使用 delete 释放 new 分配的内存？
    delete p_int_err; // 使用正确的释放方式

    // 练习 5: 内存泄漏
    // 只分配不释放
    int *p_leak = new int(50);
    // 如果没有下面的 delete p_leak; 就会发生内存泄漏
    // ASSERT(*p_leak == ?, "检查分配的值");
    delete p_leak; // 记得释放

    // THINK：
    // 1. new 和 malloc 的主要区别是什么？
    // 2. delete 和 free 的主要区别是什么？
    // 3. 什么时候应该使用动态内存分配？什么时候应该避免？
    // 4. 智能指针（如 std::unique_ptr, std::shared_ptr）如何帮助避免 new/delete 的陷阱？

    return 0;
}