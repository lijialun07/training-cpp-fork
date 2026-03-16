#include "../exercise.h"

// READ: <https://stackoverflow.com/questions/156767/whats-the-difference-between-an-argument-and-a-parameter>
// THINK: 参数都有哪些传递方式？如何选择传递方式？
// THINK: 不同的参数传递方式有什么优缺点？什么场景下应该使用哪种传递方式？

// 值传递示例
void func_by_value(int);

// 引用传递示例
void func_by_reference(int&);

// 指针传递示例
void func_by_pointer(int*);

// 常量引用传递示例
void func_by_const_reference(const int&);

// TODO: 为下列 ASSERT 填写正确的值
int main(int argc, char **argv) {
    // 值传递示例
    auto arg1 = 99;
    ASSERT(arg1 == 99, "arg1 should be ?");
    std::cout << "[值传递] befor func call: " << arg1 << std::endl;
    func_by_value(arg1);
    ASSERT(arg1 == 99, "arg1 should be ?");
    std::cout << "[值传递] after func call: " << arg1 << std::endl;

    // 引用传递示例
    auto arg2 = 99;
    ASSERT(arg2 == 99, "arg2 should be ?");
    std::cout << "[引用传递] befor func call: " << arg2 << std::endl;
    func_by_reference(arg2);
    ASSERT(arg2 == 100, "arg2 should be ?");
    std::cout << "[引用传递] after func call: " << arg2 << std::endl;

    // 指针传递示例
    auto arg3 = 99;
    ASSERT(arg3 == 99, "arg3 should be ?");
    std::cout << "[指针传递] befor func call: " << arg3 << std::endl;
    func_by_pointer(&arg3);
    ASSERT(arg3 == 100, "arg3 should be ?");
    std::cout << "[指针传递] after func call: " << arg3 << std::endl;

    // 常量引用传递示例
    auto arg4 = 99;
    ASSERT(arg4 == 99, "arg4 should be ?");
    std::cout << "[常量引用传递] befor func call: " << arg4 << std::endl;
    func_by_const_reference(arg4);
    ASSERT(arg4 == 99, "arg4 should be ?");
    std::cout << "[常量引用传递] after func call: " << arg4 << std::endl;

    return 0;
}

// TODO: 为下列 ASSERT 填写正确的值
void func_by_value(int param) {
    ASSERT(param == 99, "param should be ?");
    std::cout << "[值传递] befor add: " << param << std::endl;
    param += 1;
    ASSERT(param == 100, "param should be ?");
    std::cout << "[值传递] after add: " << param << std::endl;
}

void func_by_reference(int& param) {
    ASSERT(param == 99, "param should be ?");
    std::cout << "[引用传递] befor add: " << param << std::endl;
    param += 1;
    ASSERT(param == 100, "param should be ?");
    std::cout << "[引用传递] after add: " << param << std::endl;
}

void func_by_pointer(int* param) {
    ASSERT(*param == 99, "*param should be ?");
    std::cout << "[指针传递] befor add: " << *param << std::endl;
    *param += 1;
    ASSERT(*param == 100, "*param should be ?");
    std::cout << "[指针传递] after add: " << *param << std::endl;
}

void func_by_const_reference(const int& param) {
    ASSERT(param == 99, "param should be ?");
    std::cout << "[常量引用传递] befor add: " << param << std::endl;
    // 注意：常量引用参数不能被修改
    // param += 1;  // 这行代码会导致编译错误
    ASSERT(param == 99, "param should be ?");
    std::cout << "[常量引用传递] after add: " << param << std::endl;
}
