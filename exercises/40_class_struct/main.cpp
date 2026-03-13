#include "../exercise.h"
#include <memory>
#include <string>

// READ: class 和 struct 的区别 <https://learn.microsoft.com/zh-cn/cpp/cpp/struct-cpp?view=msvc-170>

// 定义一个结构体和一个类
struct MyStruct {
    int data; // 默认是 public
};

class MyClass {
    int data; // 默认是 private
};

// 定义基类结构体
struct BaseStruct {
    int base_data = 1;
};

// 定义基类类
class BaseClass {
public:
    int base_data = 2;
};

// 派生结构体和类
struct DerivedStruct : BaseStruct { // 默认 public 继承
    int derived_data = 3;
};

class DerivedClass : BaseClass { // 默认 private 继承
    int derived_data = 4;

// TODO: 如何能让外部访问基类的成员？
public:
    int get_base_data() const { return base_data; } // 需要公有方法访问基类成员
};

struct DerivedStructFromClass : BaseClass { // 默认 public 继承
    int derived_data = 5;
};

class DerivedClassFromStruct : BaseStruct { // 默认 private 继承
    int derived_data = 6;
public:
    int get_base_data() const { return base_data; }
};


int main(int argc, char **argv) {
    // 成员访问权限测试
    MyStruct s;
    s.data = 10; // 可以直接访问 struct 的成员
    ASSERT(s.data == 10, "结构体成员默认是 public");

    MyClass c;
    // c.data = 20; // 编译错误！类成员默认是 private
    // ASSERT(?, "类成员默认是 private，无法直接访问"); // 此行无法直接测试，需要通过公有方法

    // 继承访问权限测试
    DerivedStruct ds;
    ASSERT(ds.base_data == 1, "结构体默认 public 继承，可以访问基类 public 成员");
    ASSERT(ds.derived_data == 3, "派生结构体可以访问自己的成员");

    DerivedClass dc;
    // ASSERT(dc.base_data == ?, "类默认 private 继承，无法直接访问基类 public 成员"); // 编译错误
    ASSERT(dc.get_base_data() == 2, "通过派生类的公有方法访问基类成员");
    // ASSERT(dc.derived_data == ?, "派生类无法直接访问自己的 private 成员"); // 编译错误

    DerivedStructFromClass dsfc;
    ASSERT(dsfc.base_data == 2, "结构体继承类，默认 public 继承，可以访问基类 public 成员");
    ASSERT(dsfc.derived_data == 5, "派生结构体可以访问自己的成员");

    DerivedClassFromStruct dcfs;
    // ASSERT(dcfs.base_data == ?, "类继承结构体，默认 private 继承，无法直接访问基类 public 成员"); // 编译错误
    ASSERT(dcfs.get_base_data() == 1, "通过派生类的公有方法访问基类成员");
    // ASSERT(dcfs.derived_data == ?, "派生类无法直接访问自己的 private 成员"); // 编译错误

    return 0;
}