#include "../exercise.h"
#include <string>
#include <iostream>

// READ: 友元声明 <https://zh.cppreference.com/w/cpp/language/friend>

class A {
private:
    int private_val;

public:
    A(int val) : private_val(val) {}

    int get_private_val() const {
        return private_val;
    }

    // TODO: 声明全局函数 `print_private_val` 为 A 的友元
    // TIPS: 在类定义内部使用 `friend` 关键字
    friend void print_private_val(const A& a);

    // TODO: 声明类 B 为 A 的友元
    friend class B;
};

// 全局函数，尝试访问 A 的私有成员
void print_private_val(const A& a) {
    // TODO : 在这里访问和打印 A 的 private_val
    std::cout << "A's private_val from friend function: " << a.private_val << std::endl;
}

class B {
public:
    int access_private_val(const A& a) {
        return a.private_val;
    }
};


int main(int argc, char **argv) {
    A a(10);
    ASSERT(a.get_private_val() == 10, "Initial private value should be 10");

    print_private_val(a);

    B b;
    int val_from_b = b.access_private_val(a);
    ASSERT(val_from_b == 10, "Value accessed by friend class B should be 10");
    std::cout << "Value accessed by friend class B: " << val_from_b << std::endl;

    // THINK: 友元关系是单向的吗？ B 是 A 的友元，那么 A 是 B 的友元吗？
    //       尝试在 A 中访问 B 的私有成员（如果 B 有的话），看看是否可行。
    //       (可以在 B 中添加私有成员并尝试从 A 访问来验证)

    // THINK: 友元关系可以继承吗？ 如果 C 继承自 B，C 是 A 的友元吗？
    //       尝试创建一个继承自 B 的类 C，并在 C 中访问 A 的私有成员，看看是否可行。

    return 0;
}