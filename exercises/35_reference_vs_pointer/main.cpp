#include "../exercise.h"

// READ : 指针和引用的区别 <https://lb3fn675fh.feishu.cn/wiki/FPOVw6liGi0AO4kgNRwccE52nif>

int main(int argc, char **argv) {
    // 基础用法和初始化
    int value = 10;
    int *ptr = &value; // 指针：存储变量的地址
    int &ref = value;  // 引用：变量的别名，必须在声明时初始化

    ASSERT(*ptr == 10, "指针解引用应得到变量的值");
    ASSERT(ref == 10, "引用应等于它所引用的变量的值");
    ASSERT(ptr == &value, "指针存储的是地址，请填入 &value");

    // 可空性
    int *ptr_null = nullptr; // 指针可以为空
    // int &ref_null; // 编译错误：引用不能为空，必须引用一个存在的对象
    ASSERT(ptr_null == nullptr, "空指针的值是什么？");

    // 可重赋值性
    int another_value = 20;
    ptr = &another_value; // 指针可以重新指向另一个变量
    // ref = another_value; // 这不是重新绑定引用，而是给 `value` 赋值

    ASSERT(*ptr == 20, "指针现在指向 another_value");
    ASSERT(value == 10, "引用赋值会改变原变量的值");
    ASSERT(ref == 10, "引用仍然是 value 的别名，其值已改变");

    // 语法差异
    // 指针使用 * 解引用，使用 & 获取地址
    // 引用在声明时使用 &，之后使用时就像普通变量一样，不需要特殊符号

    *ptr = 30; // 通过指针修改 another_value 的值
    ASSERT(another_value == 30, "通过指针修改了 another_value");

    ref = 40; // 通过引用修改 value 的值
    ASSERT(value == 40, "通过引用修改了 value");

    return 0;
}