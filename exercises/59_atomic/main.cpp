#include "../exercise.h"
#include <atomic>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

// READ: std::atomic <https://zh.cppreference.com/w/cpp/atomic/atomic>
// READ: std::memory_order <https://zh.cppreference.com/w/cpp/atomic/memory_order>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 1. 基本原子操作
    std::atomic<int> atomic_var(0);

    // 原子加载 (默认 memory_order_seq_cst)
    int loaded_value = atomic_var.load();
    ASSERT(loaded_value == 0, "Initial value should be 0");

    // 原子存储 (默认 memory_order_seq_cst)
    atomic_var.store(10);
    ASSERT(atomic_var.load() == 10, "Value should be 10 after store");

    // 原子加法 (fetch_add)
    int previous_value = atomic_var.fetch_add(5);// 返回加之前的值
    ASSERT(previous_value == 10, "Previous value before fetch_add was 10");
    ASSERT(atomic_var.load() == 15, "Value should be 15 after fetch_add");

    // 原子减法 (fetch_sub)
    previous_value = atomic_var.fetch_sub(3);// 返回减之前的值
    ASSERT(previous_value == 15, "Previous value before fetch_sub was 15");
    ASSERT(atomic_var.load() == 12, "Value should be 12 after fetch_sub");

    // 比较并交换 (compare_exchange_strong)
    int expected = 12;
    bool exchanged = atomic_var.compare_exchange_strong(expected, 20);
    ASSERT(exchanged == true, "Exchange should succeed as expected value matches");
    ASSERT(atomic_var.load() == 20, "Value should be 20 after successful exchange");
    ASSERT(expected == 12, "Expected value remains 12 if exchange succeeds the first time");

    expected = 15;// 期望值与当前值(20)不符
    exchanged = atomic_var.compare_exchange_strong(expected, 30);
    ASSERT(exchanged == false, "Exchange should fail as expected value doesn't match");
    ASSERT(atomic_var.load() == 20, "Value should remain 20 after failed exchange");
    // IMPORTANT: 如果 compare_exchange 失败，expected 会被更新为原子变量的当前值
    ASSERT(expected == 20, "Expected value is updated to the current value (20) on failure");

    // 2. 内存序 (Memory Order)
    std::atomic<int> counter(0);
    std::atomic<bool> flag(false);
    int non_atomic_data = 0;

    std::thread writer([&]() {
        non_atomic_data = 42;// 非原子写
        // 使用 release 内存序确保 non_atomic_data 的写入在 flag 写入之前完成
        // 并且对其他线程可见 (如果它们使用 acquire 或 seq_cst 读取 flag)
        flag.store(true, std::memory_order_release);
        counter.fetch_add(1, std::memory_order_relaxed);// relaxed 通常用于计数器
    });

    std::thread reader([&]() {
        // 使用 acquire 内存序确保在读取 flag 为 true 后，
        // writer 线程在 release 之前的写操作 (non_atomic_data = 42) 对本线程可见
        while (!flag.load(std::memory_order_acquire)) {
            // 自旋等待
            std::this_thread::yield();// 让出 CPU 时间片
        }
        // 到这里时，flag 一定是 true，并且 non_atomic_data 的写入可见
        ASSERT(non_atomic_data == 42, "non_atomic_data should be 42 due to acquire-release ordering");
        counter.fetch_add(1, std::memory_order_relaxed);
    });

    writer.join();
    reader.join();

    ASSERT(counter.load() == 2, "Both threads should have incremented the counter");

    // 3. std::atomic_flag (最简单的原子类型，通常用于实现自旋锁)
    // READ: std::atomic_flag <https://zh.cppreference.com/w/cpp/atomic/atomic_flag>
    std::atomic_flag lock_flag = ATOMIC_FLAG_INIT;// 初始化为 clear (false) 状态

    // test_and_set: 原子地将标志设置为 true 并返回先前的值
    bool previous_flag = lock_flag.test_and_set();// 第一次调用
    ASSERT(previous_flag == false, "Initially, the flag should be clear (false)");

    previous_flag = lock_flag.test_and_set();// 第二次调用
    ASSERT(previous_flag == true, "After the first test_and_set, the flag should be set (true)");

    // clear: 原子地将标志设置为 false
    lock_flag.clear();
    previous_flag = lock_flag.test_and_set();
    ASSERT(previous_flag == false, "After clear, the flag should be clear (false) again");

    // 简单的自旋锁实现示例
    std::atomic_flag spin_lock = ATOMIC_FLAG_INIT;
    int shared_data = 0;
    std::vector<std::thread> threads;
    int num_threads = 5;
    int increments_per_thread = 1000;

    auto lock = [&]() {
        while (spin_lock.test_and_set(std::memory_order_acquire)) {
            // 自旋等待锁释放
            std::this_thread::yield();
        }
    };

    auto unlock = [&]() {
        spin_lock.clear(std::memory_order_release);
    };

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&]() {
            for (int j = 0; j < increments_per_thread; ++j) {
                lock();
                shared_data++;// 访问临界区
                unlock();
            }
        });
    }

    for (auto &t : threads) {
        t.join();
    }

    ASSERT(shared_data == 5000, "Total increments should be num_threads * increments_per_thread");


    return 0;
}