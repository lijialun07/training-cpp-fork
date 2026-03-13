#include "../exercise.h"


// READ: `namespace` <https://en.cppreference.com/w/cpp/language/namespace>


// 命名空间定义
namespace MyNamespace {
    int value = 10;
    int add(int a, int b) {
        return a + b;
    }
}

// 嵌套命名空间
namespace Outer {
    namespace Inner {
        std::string message = "Nested namespace";
    }
}

// 未命名命名空间 (行为类似静态局部变量)
namespace {
    double pi = 3.14159;
}

// 命名空间别名
namespace OIN = Outer::Inner;

// 另一个用于演示冲突解决的命名空间
namespace Conflict {
    int value = 20;
}

int main(int argc, char **argv) {
    // 练习 1: 使用作用域解析运算符访问成员
    {
        ASSERT(MyNamespace::value == 10, "从 MyNamespace 访问 value");
        ASSERT(MyNamespace::add(5, 3) == 8, "从 MyNamespace 调用 add 函数");
    }

    // 练习 2: 使用 `using` 声明
    {
        using MyNamespace::value;
        ASSERT(value == 10, "使用 using 声明后访问 value");
        // ASSERT(add(1, 2) == 3, "如果没有 `using MyNamespace::add;` 或 `MyNamespace::`，这应该会失败"); // 取消注释测试一下
    }

    // 练习 3: 使用 `using` 指令
    {
        using namespace MyNamespace;
        ASSERT(value == 10, "在带有 using 指令的代码块内访问 value");
        ASSERT(add(10, 5) == 15, "在带有 using 指令的代码块内调用 add 函数");
    }
    // ASSERT(add(1, 2) == 3, "这应该在代码块外失败"); // 取消注释测试一下

    // 练习 4: 嵌套命名空间
    ASSERT(Outer::Inner::message == "Nested namespace", "从嵌套命名空间访问 message");

    // 练习 5: 命名空间别名
    ASSERT(OIN::message == "Nested namespace", "使用命名空间别名访问 message");

    // 练习 6: 未命名命名空间
    // 未命名命名空间提供内部链接。成员可以在同一翻译单元中直接访问。
    ASSERT(pi > 3.14 && pi < 3.15, "从未命名命名空间访问变量");

    // 练习 7: 解决名称冲突
    ASSERT(MyNamespace::value == 10, "显式访问 MyNamespace 的 value");
    ASSERT(Conflict::value == 20, "显式访问 Conflict 的 value");

    // 练习 8: 将特定成员引入作用域以解决歧义
    {
        using MyNamespace::value; // 将 MyNamespace::value 引入此作用域
        ASSERT(value == 10, "在特定 using 声明后访问 MyNamespace::value");
        ASSERT(Conflict::value == 20, "显式访问 Conflict::value");
    }
    {
        using namespace Conflict; // 将 Conflict 中的所有内容引入此作用域
        ASSERT(value == 20, "在使用 using 指令后访问 Conflict::value");
        ASSERT(MyNamespace::value == 10, "显式访问 MyNamespace::value");
        // ASSERT(MyNamespace::add(1,1) == 2, "显式访问 MyNamespace::add"); // 这仍然有效
    }

    return 0;
}
