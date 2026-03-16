#include "../exercise.h"
#include <vector>
#include <string>
#include <initializer_list>

// READ: 列表初始化 (list initialization) <https://zh.cppreference.com/w/cpp/language/list_initialization>
// THINK:
// 1. 列表初始化有什么优势？
// 2. 什么情况下列表初始化会失败？
// 3. 列表初始化和圆括号初始化有什么区别？

struct Point {
    int x, y;
};

class MyClass {
public:
    int a;
    double b;
    std::string c;

    // 构造函数使用列表初始化
    MyClass(int val_a, double val_b, const std::string& val_c) : a{val_a}, b{val_b}, c{val_c} {}

    // 使用 std::initializer_list 的构造函数
    MyClass(std::initializer_list<int> list) : a(0), b(0.0), c("") {
        if (list.size() >= 1) {
            a = *(list.begin());
        }
        if (list.size() >= 2) {
            // 这是一个简化的例子，通常需要更复杂的逻辑
            // 这里只是为了演示 initializer_list 的使用
            b = *(list.begin() + 1);
        }
    }
};

int main(int argc, char **argv) {
    // 基本类型列表初始化
    int i{10};
    double d{3.14};
    char c{'a'};
    bool b{true};
    ASSERT(i == 10, "Fill in the correct value for i.");
    ASSERT(d == 3.14, "Fill in the correct value for d.");
    ASSERT(c == 'a', "Fill in the correct value for c.");
    ASSERT(b == true, "Fill in the correct value for b.");

    // 数组列表初始化
    int arr[]{1, 2, 3, 4, 5};
    ASSERT(arr[0] == 1, "Fill in the correct value for arr[0].");
    ASSERT(arr[4] == 5, "Fill in the correct value for arr[4].");
    ASSERT(sizeof(arr) / sizeof(arr[0]) == 5, "Fill in the correct size of arr.");

    // std::vector 列表初始化
    std::vector<int> vec{10, 20, 30};
    ASSERT(vec.size() == 3, "Fill in the correct size of vec.");
    ASSERT(vec[1] == 20, "Fill in the correct value for vec[1].");

    // 结构体列表初始化
    Point p1{1, 2};
    Point p2 = {3, 4}; // 也可以使用等号
    ASSERT(p1.x == 1, "Fill in the correct value for p1.x.");
    ASSERT(p1.y == 2, "Fill in the correct value for p1.y.");
    ASSERT(p2.x == 3, "Fill in the correct value for p2.x.");
    ASSERT(p2.y == 4, "Fill in the correct value for p2.y.");

    // 类列表初始化 (使用构造函数)
    MyClass obj1{100, 2.71, "hello"};
    ASSERT(obj1.a == 100, "Fill in the correct value for obj1.a.");
    ASSERT(obj1.b == 2.71, "Fill in the correct value for obj1.b.");
    ASSERT(obj1.c == "hello", "Fill in the correct value for obj1.c.");

    // 类列表初始化 (使用 std::initializer_list 构造函数)
    MyClass obj2{5, 8};
    ASSERT(obj2.a == 5, "Fill in the correct value for obj2.a using initializer_list.");
    ASSERT(obj2.b == 8, "Fill in the correct value for obj2.b using initializer_list.");
    ASSERT(obj2.c == "", "Fill in the correct value for obj2.c using initializer_list.");

    // 防止窄化转换 (narrowing conversions)
    // int narrow_i{3.14}; // 这行代码会编译错误，因为 double 不能窄化为 int
    // char narrow_c{1000}; // 这行代码会编译错误，因为 1000 超出 char 范围
    // 请思考为什么列表初始化可以防止窄化转换，而圆括号初始化不行？
    int round_parentheses_i(3.14); // 圆括号初始化允许窄化转换 (可能产生警告)
    ASSERT(round_parentheses_i == 3, "What is the value after narrowing conversion?");

    return 0;
}