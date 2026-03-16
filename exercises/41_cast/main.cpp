#include "../exercise.h"
#include <iostream>
#include <string>
#include <vector>

// READ: C++ 强制类型转换 <https://zh.cppreference.com/w/cpp/language/explicit_cast>
// READ: static_cast <https://zh.cppreference.com/w/cpp/language/static_cast>
// READ: dynamic_cast <https://zh.cppreference.com/w/cpp/language/dynamic_cast>
// READ: const_cast <https://zh.cppreference.com/w/cpp/language/const_cast>
// READ: reinterpret_cast <https://zh.cppreference.com/w/cpp/language/reinterpret_cast>

// 定义用于 dynamic_cast 的基类和派生类
struct Base {
    virtual ~Base() = default; // 虚析构函数是 dynamic_cast 的必要条件
    virtual void print() const { std::cout << "Base\n"; }
};

struct Derived : public Base {
    void print() const override { std::cout << "Derived\n"; }
    void derived_only() { std::cout << "Derived Only\n"; }
};

struct AnotherDerived : public Base {
    void print() const override { std::cout << "AnotherDerived\n"; }
};

int main(int argc, char **argv) {
    // static_cast
    {
        // 基本类型转换
        double pi = 3.14159;
        int integer_pi = static_cast<int>(pi);
        ASSERT(integer_pi == 3, "static_cast: double to int");

        // 指针向上转换（派生类到基类）
        Derived d;
        Base* base_ptr = static_cast<Base*>(&d);
        ASSERT(base_ptr != nullptr, "static_cast: Derived* to Base*");

        // 指针向下转换（基类到派生类，不安全，但编译时允许）
        // NOTICE：只有当 base_ptr 确实指向 Derived 对象时，这才是安全的
        Derived* derived_ptr_static = static_cast<Derived*>(base_ptr);
        ASSERT(derived_ptr_static != nullptr, "static_cast: Base* to Derived* (unsafe but allowed)");

        // void* 转换
        void* void_ptr = &integer_pi;
        int* int_ptr_from_void = static_cast<int*>(void_ptr);
        ASSERT(*int_ptr_from_void == 3, "static_cast: void* to int*");
    }

    // dynamic_cast
    {
        Derived d;
        Base* base_ptr = &d;

        // 向下转换（安全的）
        Derived* derived_ptr_dynamic = dynamic_cast<Derived*>(base_ptr);
        ASSERT(derived_ptr_dynamic != nullptr, "dynamic_cast: Base* to Derived* (safe)");
        if (derived_ptr_dynamic) {
            derived_ptr_dynamic->derived_only(); // 可以调用派生类特有方法
        }

        // 尝试转换到不相关的类型
        AnotherDerived* another_derived_ptr = dynamic_cast<AnotherDerived*>(base_ptr);
        // ASSERT(another_derived_ptr == base_ptr, "dynamic_cast: Base* to AnotherDerived* (should fail)");

        // 对引用使用 dynamic_cast
        Base& base_ref = d;
        try {
            Derived& derived_ref = dynamic_cast<Derived&>(base_ref);
            // 转换成功
            derived_ref.derived_only();
            ASSERT(true, "dynamic_cast: Base& to Derived& (safe)");
        } catch (const std::bad_cast& e) {
            ASSERT(false, "dynamic_cast: Base& to Derived& should succeed");
        }

        try {
            AnotherDerived& another_derived_ref = dynamic_cast<AnotherDerived&>(base_ref);
            ASSERT(false, "dynamic_cast: Base& to AnotherDerived& should fail");
        } catch (const std::bad_cast& e) {
            // 转换失败，抛出异常
            ASSERT(true, "dynamic_cast: Base& to AnotherDerived& (should throw std::bad_cast)");
            std::cout << "Caught expected exception: " << e.what() << std::endl;
        }
    }

    // const_cast
    {
        const int const_val = 10;
        // int non_const_val = const_val; // 直接赋值是合法的，创建了一个副本

        // 移除 const
        int* non_const_ptr = const_cast<int*>(&const_val);
        *non_const_ptr = 20; // 警告：修改最初声明为 const 的对象是未定义行为！
                             // 这里仅作演示 const_cast 的语法
        // ASSERT(const_val == ?, "const_cast: Modifying const object (Undefined Behavior!)");
        // 由于是未定义行为，我们不对此进行断言检查，但需要理解其危险性

        const Base cb;
        Base* non_const_base_ptr = const_cast<Base*>(&cb);
        // non_const_base_ptr->print(); // 调用非 const 方法（如果 Base 有的话）
        ASSERT(non_const_base_ptr != nullptr, "const_cast: remove const from object pointer");

        // 添加 const
        int val = 30;
        const int* const_ptr = const_cast<const int*>(&val);
        ASSERT(*const_ptr == 30, "const_cast: add const to object pointer");
        // *const_ptr = 40; // 编译错误：不能通过 const 指针修改
    }

    // reinterpret_cast
    {
        long long large_val = 0x12345678ABCD;
        // 将指针类型重新解释为另一种指针类型
        int* int_ptr_reinterpreted = reinterpret_cast<int*>(&large_val);
        // NOTICE：访问 *int_ptr_reinterpreted 可能会导致未定义行为，取决于平台和对齐
        // 这里仅演示转换本身
        ASSERT(int_ptr_reinterpreted != nullptr, "reinterpret_cast: long long* to int*");

        // 将指针转换为整数类型
        uintptr_t ptr_as_int = reinterpret_cast<uintptr_t>(&large_val);
        ASSERT(ptr_as_int != 0, "reinterpret_cast: pointer to integer");

        // 将整数类型转换回指针
        long long* original_ptr = reinterpret_cast<long long*>(ptr_as_int);
        ASSERT(original_ptr == &large_val, "reinterpret_cast: integer to pointer");
        ASSERT(*original_ptr == 0x12345678ABCD, "reinterpret_cast: dereference recovered pointer");

        // 函数指针转换 (危险，通常不推荐)
        using FuncPtr = void(*)();
        FuncPtr func_ptr = reinterpret_cast<FuncPtr>(&main); // 将 main 函数指针转换为不同类型
        ASSERT(func_ptr != nullptr, "reinterpret_cast: function pointer conversion");
    }

    return 0;
}