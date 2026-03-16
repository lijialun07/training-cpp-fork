#include "../exercise.h"
#include <string>

// READ: 字符串 <https://zh.cppreference.com/w/cpp/string/basic_string>

std::string reverse_string(const std::string& str) {
    // TODO: 实现字符串反转函数
    if (str.length() == 0) {
        return "";
    }
    std::string ret = str;
    auto rit = str.rbegin();
    auto it = ret.begin();
    while (rit != str.rend()) {
        *it = *rit;
        it++;
        rit++;
    }
    return ret;
}

int main(int argc, char **argv) {
    // READ: 字符串字面量 <https://zh.cppreference.com/w/cpp/string/basic_string/operator%22%22s>
    using namespace std::string_literals;
    auto hello = "Hello"s;
    auto world = "world"s;
    // READ: `decltype` 表达式 <https://zh.cppreference.com/w/cpp/language/decltype>
    // READ: `std::is_same_v` 元编程判别 <https://zh.cppreference.com/w/cpp/types/is_same>
    ASSERT((std::is_same_v<decltype(hello), std::string>), "Fill in the missing type.");
    ASSERT((std::is_same_v<decltype(world), std::string>), "Fill in the missing type.");
    // TODO: 将 `?` 替换为正确的字符串
    ASSERT(hello + ", " + world + '!' == "Hello, world!", "Fill in the missing string.");

    // NOTICE: 了解字符串的基本操作，如 `size`、`substr`、`find` 等。
    // TODO: 实现字符串反转函数
    ASSERT(reverse_string("Hello world!") == "!dlrow olleH", "Fill in the missing string.");
    ASSERT(reverse_string("Hello") == "olleH", "Fill in the missing string.");
    ASSERT(reverse_string("") == "", "Fill in the missing string.");

    // size
    ASSERT(hello.size() == 5, "Fill in the missing value.");
    ASSERT(world.size() == 5, "Fill in the missing value.");

    // NOTICE: `std::string`的 size 计算方法和 `\0` 无关。
    std::string str1 = "Hello\0world!";
    std::string str2 = "Hello world!";
    ASSERT(str1.size() == 5, "Fill in the missing value.");
    ASSERT(str2.size() == 12, "Fill in the missing value.");


    // substr
    ASSERT(hello.substr(0, 2) == "He", "Fill in the missing string.");
    ASSERT(world.substr(1, 3) == "orl", "Fill in the missing string.");

    // string capacity
    hello.resize(10);
    hello.reserve(100);
    ASSERT(hello.size() == 10, "Fill in the missing value.");
    ASSERT(hello.capacity() == 100, "Fill in the missing value.");  // Mac OS -> Clang++: 103

    // NOTICE: 注意 `std::string` 的SSO优化，什么条件下使用栈内存，什么条件下使用堆内存。
    // READ: SSO优化 <https://lb3fn675fh.feishu.cn/wiki/A30KwguMein859k9xtzcJtSRnYc>
    std::string long_string(10000, 'a');
    std::string short_string(10, 'a');
    // THINK:  `long_string` 和 `short_string` 分别使用的是栈内存还是堆内存。
    // THINK: 栈内存和堆内存的区别是什么？
    // THINK: 什么是SSO优化？

    return 0;
}
