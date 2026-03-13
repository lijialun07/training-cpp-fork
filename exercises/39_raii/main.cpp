#include "../exercise.h"

#include <iostream>
#include <string>
#include <stdexcept>

// READ: RAII <https://lb3fn675fh.feishu.cn/wiki/FI6uwuRBbi30mbkbDTIcvyF3nAf>

// 模拟一个需要手动管理的资源，但实际上不需要
struct MockResource {
    std::string name;
    bool acquired = false;
    bool released = false;

    MockResource(std::string n) : name(std::move(n)) {}

    void acquire() {
        if (!acquired) {
            std::cout << "资源 '" << name << "' 已获取。" << std::endl;
            acquired = true;
        }
    }

    void release() {
        if (acquired && !released) {
            std::cout << "资源 '" << name << "' 已释放。" << std::endl;
            released = true;
        }
    }

    // 模拟资源使用
    void use() const {
        if (!acquired || released) {
            throw std::runtime_error("尝试使用未获取或已释放的资源！");
        }
        std::cout << "正在使用资源 '" << name << "'..." << std::endl;
    }
};

// TODO: 实现一个 RAII 包装器类 `ResourceGuard`
// 要求：
// 1. 构造函数获取 MockResource 指针并调用其 acquire() 方法。
// 2. 析构函数调用 MockResource 的 release() 方法。
// 3. 禁止拷贝构造和拷贝赋值（资源所有权不应被复制）。
// 4. 提供一个 get() 方法返回底层 MockResource 的指针，以便访问资源。
// 5. 提供一个重载的 -> 运算符，以便通过 ResourceGuard 对象直接调用 MockResource 的方法。

class ResourceGuard {
    MockResource* resource_ptr;

public:
    // 构造函数：获取资源
    explicit ResourceGuard(MockResource* res) : resource_ptr(res) {
        if (resource_ptr) {
            resource_ptr->acquire(); // 调用 acquire
        }
    }

    // 析构函数：释放资源
    ~ResourceGuard() {
        // TODO: 释放资源
        if (resource_ptr) {
            resource_ptr->release();
        }
    }

    // 禁止拷贝构造
    ResourceGuard(const ResourceGuard&) = delete;
    // 禁止拷贝赋值
    ResourceGuard& operator=(const ResourceGuard&) = delete;

    // 允许移动构造
    ResourceGuard(ResourceGuard&& other) noexcept : resource_ptr(other.resource_ptr) {
        other.resource_ptr = nullptr; // 源对象不再拥有资源
    }

    // 允许移动赋值
    ResourceGuard& operator=(ResourceGuard&& other) noexcept {
        if (this != &other) {
            // 释放当前持有的资源 (如果有)
            if (resource_ptr) {
                resource_ptr->release();
            }
            // 转移资源所有权
            resource_ptr = other.resource_ptr;
            other.resource_ptr = nullptr;
        }
        return *this;
    }


    // 获取底层资源指针
    MockResource* get() const {
        return resource_ptr;
    }

    // 重载 -> 运算符
    MockResource* operator->() const {
        return resource_ptr;
    }
};

int main(int argc, char **argv) {
    // 练习 1: 基本的 RAII 用法
    MockResource res1("文件句柄");
    ASSERT(!res1.acquired, "初始状态：未获取");
    ASSERT(!res1.released, "初始状态：未释放");

    {
        ResourceGuard guard(&res1);
        ASSERT(res1.acquired == true, "构造 ResourceGuard 后：应已获取");
        ASSERT(res1.released == false, "构造 ResourceGuard 后：应未释放");

        // 通过 get() 方法访问资源
        MockResource* raw_ptr = guard.get();
        ASSERT(raw_ptr == &res1, "get() 应返回底层指针");
        raw_ptr->use();

        // 通过 -> 运算符访问资源
        guard->use();
        ASSERT(guard->name == "文件句柄", "通过 -> 访问 name");

    } // guard 在这里离开作用域，析构函数被调用

    ASSERT(res1.acquired == true, "离开作用域后：应已获取");
    ASSERT(res1.released == true, "离开作用域后：应已释放");

    // 练习 2: 异常安全
    MockResource res2("网络连接");
    ASSERT(!res2.acquired, "初始状态：未获取");
    ASSERT(!res2.released, "初始状态：未释放");

    try {
        ResourceGuard guard(&res2);
        ASSERT(res2.acquired == true, "构造 ResourceGuard 后：应已获取");
        guard->use();
        // 模拟在资源使用过程中发生异常
        throw std::runtime_error("发生了一个错误！");
        // 下面的代码不会被执行
        std::cout << "这行代码不应被打印。" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "捕获到异常: " << e.what() << std::endl;
    }

    // 即使发生异常，RAII 也能保证资源被释放
    ASSERT(res2.acquired == true, "异常发生后：应已获取");
    ASSERT(res2.released == true, "异常发生后：应已释放");

    // 练习 3: 移动语义
    MockResource res3("数据库会话");
    ResourceGuard guard1(&res3);
    ASSERT(guard1.get() != nullptr, "guard1 拥有资源");
    ASSERT(res3.acquired, "资源已被 guard1 获取");

    // 使用移动构造函数转移所有权
    ResourceGuard guard2 = std::move(guard1);
    ASSERT(guard1.get() == nullptr, "guard1 移动后应为空");
    ASSERT(guard2.get() == &res3, "guard2 应拥有资源");
    ASSERT(guard2->name == "数据库会话", "guard2 可以访问资源");

    // guard1 析构时不会释放资源，因为其 resource_ptr 为 nullptr
    // guard2 析构时会释放资源

    return 0;
}