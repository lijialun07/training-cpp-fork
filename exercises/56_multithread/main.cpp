#include "../exercise.h"
#include <iostream>
#include <mutex>
#include <numeric>
#include <thread>
#include <vector>

// READ: std::thread <https://zh.cppreference.com/w/cpp/thread/thread>
// READ: std::mutex <https://zh.cppreference.com/w/cpp/thread/mutex>
// READ: std::lock_guard <https://zh.cppreference.com/w/cpp/thread/lock_guard>
// READ: 并发编程系列 <https://lb3fn675fh.feishu.cn/wiki/MCsLwI7OtiXk9JkFGZJcNXbrn1g>
// READ: 并发编程指南 <https://www.cnblogs.com/haippy/p/3284540.html>

// 全局变量，用于线程间共享数据
int global_counter = 0;
std::mutex counter_mutex;// 用于保护全局计数器的互斥锁

// 简单的线程函数：打印消息
void print_message(const std::string &message) {
    // std::cout << message << std::endl; // 直接输出可能导致交错
    // TODO: 尝试不加锁直接输出，看看会发生什么
    // 使用互斥锁保护 std::cout
    static std::mutex cout_mutex;
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Message from thread [" << std::this_thread::get_id() << "]: " << message << std::endl;
}

// 线程函数：增加全局计数器
void increment_counter(int increments) {
    for (int i = 0; i < increments; ++i) {
        // 使用 lock_guard 自动管理互斥锁的锁定和解锁
        std::lock_guard<std::mutex> lock(counter_mutex);
        global_counter++;
    }
}

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 1. 创建和启动线程
    {
        std::cout << "\n--- 1. 创建和启动线程 ---" << std::endl;
        std::string msg = "Hello from thread!";
        // 创建一个新线程 t1，执行 print_message 函数，并传递参数 msg
        std::thread t1(print_message, msg);

        // 等待线程 t1 完成执行
        // NOTICE: 如果不调用 join() 或 detach()，程序在 t1 析构时会调用 std::terminate
        if (t1.joinable()) {
            t1.join();
        }

        // 检查线程是否可join (join 后 joinable() 应返回 false)
        ASSERT(!t1.joinable(), "t1 should not be joinable after join()");

        // NOTICE: 尝试再次 join 已经 join 的线程是错误的，但这里我们已经检查过 joinable()
    }

    // 2. 传递参数给线程
    {
        std::cout << "\n--- 2. 传递参数给线程 ---" << std::endl;
        std::vector<std::thread> threads;
        std::vector<std::string> messages = {"Msg 1", "Msg 2", "Msg 3"};
        for (const auto &m : messages) {
            // 创建线程并传递参数。注意：参数会按值复制或移动到线程内部存储
            threads.emplace_back(print_message, m);
        }

        // TONICE: 阻塞等待所有线程完成
        for (auto &t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }
        ASSERT(threads.size() == 3, "Should have created 3 threads");
    }

    // 3. 使用互斥锁进行同步
    {
        std::cout << "\n--- 3. 使用互斥锁进行同步 ---" << std::endl;
        global_counter = 0;// 重置计数器
        int num_threads = 5;
        int increments_per_thread = 10000;
        std::vector<std::thread> threads;

        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back(increment_counter, increments_per_thread);
        }

        for (auto &t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }

        // 验证最终的计数器值
        // NOTICE: 如果没有互斥锁保护，global_counter 的最终值可能会不等于预期值，因为存在数据竞争
        int expected_value = num_threads * increments_per_thread;
        std::cout << "Expected counter value: " << expected_value << std::endl;
        std::cout << "Actual counter value: " << global_counter << std::endl;
        ASSERT(global_counter == 50000, "Counter should be equal to num_threads * increments_per_thread");
    }

    // 4. 获取硬件并发数 (HINT：这只是一个提示值，不保证准确)
    {
        std::cout << "\n--- 4. 获取硬件并发数 ---" << std::endl;
        unsigned int hardware_threads = std::thread::hardware_concurrency();
        std::cout << "Hardware concurrency: " << hardware_threads << std::endl;
        // 这个值通常用于决定线程池的大小等
        // 注意：如果系统无法确定，可能返回 0
        ASSERT(hardware_threads > 0 || hardware_threads == 0, "Hardware concurrency should be non-negative");
    }

    return 0;
}