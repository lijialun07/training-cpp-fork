#include "../exercise.h"
#include <iostream>
#include <sstream>

// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

// 定义一个简单的二维向量结构体
struct Vector2D {
    double x, y;

    // 实现向量加法：(a, b) + (c, d) = (a+c, b+d)
    Vector2D operator+(const Vector2D& other) const {
        return {x + other.x, y + other.y};
    }

    // TODO: 重载减法运算符 (-)
    // 实现向量减法：(a, b) - (c, d) = (a-c, b-d)
    Vector2D operator-(const Vector2D& other) const {
        // ?
        return {x - other.x, y - other.y};
    }

    // TODO: 重载标量乘法运算符 (*)
    // 实现向量与标量的乘法：k * (a, b) = (k*a, k*b)
    // 注意：通常标量乘法有两种形式：scalar * vector 和 vector * scalar
    // 这里我们先实现 vector * scalar
    Vector2D operator*(double scalar) const {
        // ?
        return {scalar * x, scalar * y};
    }

    friend Vector2D operator*(double scalar, const Vector2D& vec);

    // TODO: 重载相等运算符 (==)
    // 判断两个向量是否相等（所有分量都相等）
    bool operator==(const Vector2D& other) const {
        // ?
        return (x == other.x && y == other.y);
    }

    // TODO: 重载不等运算符 (!=)
    // 判断两个向量是否不相等
    bool operator!=(const Vector2D& other) const {
        // ?
        return (x != other.x || y != other.y);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec);
};

// TODO: 重载标量乘法运算符 (*) - scalar * vector 形式
// 实现标量与向量的乘法：k * (a, b) = (k*a, k*b)
// 提示：这通常实现为非成员函数
Vector2D operator*(double scalar, const Vector2D& vec) {
    // ?
    return {scalar * vec.x, scalar * vec.y};
}

// TODO: 重载流插入运算符 (<<)
//使得 std::cout << vec; 可以输出 "(x, y)" 格式
std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
    // ?
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

int main(int argc, char **argv) {
    Vector2D v1{1.0, 2.0};
    Vector2D v2{3.0, 4.0};
    double scalar = 2.0;

    // 测试加法
    Vector2D sum = v1 + v2;
    ASSERT(sum.x == 4.0, "Vector addition x component");
    ASSERT(sum.y == 6.0, "Vector addition y component");

    // 测试减法
    Vector2D diff = v1 - v2;
    ASSERT(diff.x == -2.0, "Vector subtraction x component");
    ASSERT(diff.y == -2.0, "Vector subtraction y component");

    // 测试标量乘法 (vector * scalar)
    Vector2D prod1 = v1 * scalar;
    ASSERT(prod1.x == 2.0, "Vector times scalar x component");
    ASSERT(prod1.y == 4.0, "Vector times scalar y component");

    // 测试标量乘法 (scalar * vector)
    Vector2D prod2 = scalar * v2;
    ASSERT(prod2.x == 6.0, "Scalar times vector x component");
    ASSERT(prod2.y == 8.0, "Scalar times vector y component");

    // 测试相等性
    Vector2D v3{1.0, 2.0};
    ASSERT(v1 == v3, "Vector equality check");
    ASSERT(v1 != v2, "Vector inequality check");

    // 测试流插入
    std::stringstream ss;
    ss << v1;
    ASSERT(ss.str() == "(1, 2)", "Stream insertion check");

    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    std::cout << "v1 + v2 = " << sum << std::endl;
    std::cout << "v1 - v2 = " << diff << std::endl;
    std::cout << "v1 * " << scalar << " = " << prod1 << std::endl;
    std::cout << scalar << " * v2 = " << prod2 << std::endl;

    return 0;
}