#include "../exercise.h"
#include <future>
#include <iostream>
#include <numeric>// for std::accumulate
#include <string>
#include <thread>
#include <vector>

// READ: std::future <https://zh.cppreference.com/w/cpp/thread/future>
// READ: std::promise <https://zh.cppreference.com/w/cpp/thread/promise>
// READ: std::packaged_task <https://zh.cppreference.com/w/cpp/thread/packaged_task>

// TODO: 将下列 `?` 替换为正确的代码

// 异步计算函数
int calculate_sum(const std::vector<int> &data) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));// 模拟耗时计算
    return std::accumulate(data.begin(), data.end(), 0);
}

// 异步函数，模拟可能抛出异常的操作
int risky_calculation(bool fail) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    if (fail) {
        throw std::runtime_error("计算失败");
    }
    return 42;
}

int main(int argc, char **argv) {
    std::vector<int> data = {1, 2, 3, 4, 5};

    // 1. 使用 std::async 启动异步任务
    // READ: std::async <https://zh.cppreference.com/w/cpp/thread/async>
    std::future<int> sum_future = std::async(std::launch::async, calculate_sum, data);
    // 等待结果并获取
    int sum_result = sum_future.get();
    ASSERT(sum_result == 15, "异步计算结果应为 15");

    // 2. 使用 std::packaged_task 包装任务
    std::packaged_task<int(const std::vector<int> &)> task(calculate_sum);
    std::future<int> task_future = task.get_future();
    // 在新线程中执行任务
    std::thread task_thread(std::move(task), data);
    task_thread.detach();// 分离线程，让它自行运行
    // 等待并获取结果
    int task_result = task_future.get();
    ASSERT(task_result == 15, "packaged_task 计算结果应为 15");

    // 3. 使用 std::promise 在线程间传递值
    std::promise<std::string> promise_obj;
    std::future<std::string> promise_future = promise_obj.get_future();
    std::thread promise_thread([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        try {
            // 模拟一些工作，然后设置值
            std::string result = "来自 promise 的数据";
            promise_obj.set_value(result);
        } catch (...) {
            // 发生异常时设置异常
            promise_obj.set_exception(std::current_exception());
        }
    });
    // 从 future 获取值
    std::string promise_result = promise_future.get();
    ASSERT(promise_result == "来自 promise 的数据", "从 promise 获取的值不正确");
    promise_thread.join();// 等待线程结束

    // 4. 处理 std::future 中的异常 (使用 std::async)
    std::future<int> exception_future = std::async(std::launch::async, risky_calculation, true);
    try {
        int exception_result = exception_future.get();
        ASSERT(false, "这里不应该被执行，因为 future 应该包含异常");
    } catch (const std::runtime_error &e) {
        ASSERT(std::string(e.what()) == "计算失败", "捕获到的异常信息不正确");
    } catch (...) {
        ASSERT(false, "捕获到了未知的异常类型");
    }

    // 5. 处理 std::future 中的异常 (使用 std::promise)
    std::promise<int> promise_exception;
    std::future<int> future_exception_promise = promise_exception.get_future();
    std::thread thread_exception([&]() {
        try {
            throw std::logic_error("逻辑错误");
        } catch (...) {
            promise_exception.set_exception(std::current_exception());
        }
    });
    try {
        future_exception_promise.get();
        ASSERT(false, "这里不应该被执行，因为 future 应该包含异常");
    } catch (const std::logic_error &e) {
        ASSERT(std::string(e.what()) == "逻辑错误", "通过 promise 传递的异常信息不正确");
    } catch (...) {
        ASSERT(false, "捕获到了未知的异常类型");
    }
    thread_exception.join();

    // 6. 使用 std::future 的 wait_for 来检查状态
    std::future<void> wait_future = std::async(std::launch::async, []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    });
    std::future_status status = wait_future.wait_for(std::chrono::milliseconds(50));
    ASSERT(status == std::future_status::timeout, "在 50ms 时，future 应该仍在运行");
    status = wait_future.wait_for(std::chrono::milliseconds(300));
    ASSERT(status == std::future_status::ready, "在 300ms 时，future 应该已经完成");

    return 0;
}