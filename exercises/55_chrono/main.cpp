#include "../exercise.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>

// READ: std::chrono <https://zh.cppreference.com/w/cpp/chrono>
// READ: chrono 的设计哲学 <https://lb3fn675fh.feishu.cn/wiki/HtWswvWLiiXipkkQPCRcuiWjnkg>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 1. 获取当前时间点
    auto now = std::chrono::system_clock::now();
    // 将时间点转换为 time_t 用于打印 (注：这可能丢失精度)
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "当前时间: " << std::put_time(std::localtime(&now_c), "%F %T") << std::endl;

    // 2. 创建一个表示 100 毫秒的 duration
    std::chrono::milliseconds ms100(100);
    ASSERT(ms100.count() == 100, "100 毫秒的 count 应该是 100");

    // 3. 创建一个表示 3 秒的 duration
    std::chrono::seconds sec3(3);
    ASSERT(sec3.count() == 3, "3 秒的 count 应该是 3");

    // 4. duration 类型转换：将秒转换为毫秒
    std::chrono::milliseconds ms_from_sec = sec3;
    ASSERT(ms_from_sec.count() == 3000, "3 秒等于多少毫秒？");

    // 5. duration 类型转换：将毫秒转换为微秒
    std::chrono::microseconds micro_from_ms = ms100;
    ASSERT(micro_from_ms.count() == 100000, "100 毫秒等于多少微秒？");

    // 6. duration 运算：加法
    auto total_ms = ms100 + sec3;
    ASSERT(total_ms.count() == 3100, "100 毫秒 + 3 秒 等于多少毫秒？");
    ASSERT(std::chrono::duration_cast<std::chrono::seconds>(total_ms).count() == 3, "100 毫秒 + 3 秒 大约等于多少秒 (向下取整)？");

    // 7. duration 运算：减法
    auto diff_ms = sec3 - ms100;
    ASSERT(diff_ms.count() == 2900, "3 秒 - 100 毫秒 等于多少毫秒？");

    // 8. time_point 运算：加上 duration
    auto later = now + sec3;
    std::time_t later_c = std::chrono::system_clock::to_time_t(later);
    std::cout << "3 秒后时间: " << std::put_time(std::localtime(&later_c), "%F %T") << std::endl;

    // 9. time_point 运算：减去 duration
    auto earlier = now - std::chrono::hours(1);
    std::time_t earlier_c = std::chrono::system_clock::to_time_t(earlier);
    std::cout << "1 小时前时间: " << std::put_time(std::localtime(&earlier_c), "%F %T") << std::endl;

    // 10. time_point 运算：两个 time_point 相减得到 duration
    auto duration_diff = later - earlier;
    // 将 duration 转换为小时
    auto hours_diff = std::chrono::duration_cast<std::chrono::hours>(duration_diff);
    ASSERT(hours_diff.count() == 1, "(now + 3s) 和 (now - 1h) 之间相差大约多少小时？");
    // 将 duration 转换为分钟
    auto minutes_diff = std::chrono::duration_cast<std::chrono::minutes>(duration_diff);
    ASSERT(minutes_diff.count() == 60, "(now + 3s) 和 (now - 1h) 之间相差大约多少分钟？");

    // 11. 使用 steady_clock 进行精确计时
    auto start = std::chrono::steady_clock::now();
    // 模拟耗时操作
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "模拟操作耗时: " << elapsed_ms.count() << " 毫秒" << std::endl;
    // 注意：实际耗时可能略大于 50ms
    ASSERT(elapsed_ms.count() >= 50, "耗时至少应为 50 毫秒");

    return 0;
}