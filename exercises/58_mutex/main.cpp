#include "../exercise.h"
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// READ: std::mutex <https://zh.cppreference.com/w/cpp/thread/mutex>
// READ: std::lock_guard <https://zh.cppreference.com/w/cpp/thread/lock_guard>
// READ: std::unique_lock <https://zh.cppreference.com/w/cpp/thread/unique_lock>
// READ: std::recursive_mutex <https://zh.cppreference.com/w/cpp/thread/recursive_mutex>

// 全局共享资源
int shared_counter = 0;
std::mutex counter_mutex;// 保护 shared_counter 的互斥锁

// 使用 std::mutex 和 lock/unlock 手动管理锁
void increment_with_mutex(int increments) {
    for (int i = 0; i < increments; ++i) {
        counter_mutex.lock();// 获取锁
        shared_counter++;
        counter_mutex.unlock();// 释放锁
    }
}

// 使用 std::lock_guard 自动管理锁 (RAII)
void increment_with_lock_guard(int increments) {
    for (int i = 0; i < increments; ++i) {
        // lock_guard 在构造时获取锁，在析构时自动释放锁
        std::lock_guard<std::mutex> lock(counter_mutex);
        shared_counter++;
    }// lock 在这里超出作用域，自动释放
}

// 使用 std::unique_lock 提供更灵活的锁管理
void increment_with_unique_lock(int increments) {
    for (int i = 0; i < increments; ++i) {
        std::unique_lock<std::mutex> lock(counter_mutex);// 获取锁
        shared_counter++;
        // unique_lock 可以在需要时手动解锁
        if (shared_counter % 100 == 0) {
            lock.unlock();// 临时释放锁
            // ... 做一些不需要锁的操作 ...
            std::this_thread::sleep_for(std::chrono::microseconds(1));
            lock.lock();// 重新获取锁
        }
    }// lock 在这里超出作用域，自动释放 (如果还持有锁)
}

// THINK: lock_guard 和 unique_lock 的区别在哪里？

// 递归互斥锁示例
std::recursive_mutex recursive_mtx;
int recursive_counter = 0;

void recursive_function(int level) {
    std::lock_guard<std::recursive_mutex> lock(recursive_mtx);
    recursive_counter++;
    if (level > 0) {
        recursive_function(level - 1);// 同一线程可以再次获取递归锁
    }
}

// TODO: 将下列 `?` 替换为正确的代码或值
int main(int argc, char **argv) {
    int num_threads = 4;
    int increments_per_thread = 10000;
    int expected_value = num_threads * increments_per_thread;

    // 1. 使用 std::mutex 手动管理锁
    {
        std::cout << "\n--- 1. 使用 std::mutex 手动管理锁 ---" << std::endl;
        shared_counter = 0;// 重置计数器
        std::vector<std::thread> threads;
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back(increment_with_mutex, increments_per_thread);
        }
        for (auto &t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }
        std::cout << "Expected: " << expected_value << ", Actual: " << shared_counter << std::endl;
        ASSERT(shared_counter == 40000, "使用 std::mutex 后计数器值应正确");
    }

    // 2. 使用 std::lock_guard 自动管理锁 (RAII)
    {
        std::cout << "\n--- 2. 使用 std::lock_guard 自动管理锁 ---" << std::endl;
        shared_counter = 0;// 重置计数器
        std::vector<std::thread> threads;
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back(increment_with_lock_guard, increments_per_thread);
        }
        for (auto &t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }
        std::cout << "Expected: " << expected_value << ", Actual: " << shared_counter << std::endl;
        ASSERT(shared_counter == 40000, "使用 std::lock_guard 后计数器值应正确");
    }

    // 3. 使用 std::unique_lock 进行灵活的锁管理
    {
        std::cout << "\n--- 3. 使用 std::unique_lock 进行灵活的锁管理 ---" << std::endl;
        shared_counter = 0;// 重置计数器
        std::vector<std::thread> threads;
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back(increment_with_unique_lock, increments_per_thread);
        }
        for (auto &t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }
        std::cout << "Expected: " << expected_value << ", Actual: " << shared_counter << std::endl;
        ASSERT(shared_counter == 40000, "使用 std::unique_lock 后计数器值应正确");

        // unique_lock 的其他功能示例
        std::unique_lock<std::mutex> lock(counter_mutex, std::defer_lock);// 延迟锁定
        ASSERT(!lock.owns_lock(), "延迟锁定后不应持有锁");
        bool locked = lock.try_lock();// 尝试获取锁
        if (locked) {
            std::cout << "Successfully acquired lock with try_lock()" << std::endl;
            ASSERT(lock.owns_lock(), "try_lock 成功后应持有锁");
            lock.unlock();
        } else {
            std::cout << "Failed to acquire lock with try_lock()" << std::endl;
        }

        lock.lock();// 显式锁定
        ASSERT(lock.owns_lock(), "显式锁定后应持有锁");
        std::mutex *mtx_ptr = lock.release();// 释放锁的所有权，但不解锁
        ASSERT(!lock.owns_lock(), "释放所有权后不应持有锁");
        ASSERT(mtx_ptr == &counter_mutex, "释放的指针应指向原始互斥锁");
        mtx_ptr->unlock();// 需要手动解锁
    }

    // 4. 使用 std::recursive_mutex 允许同一线程多次锁定
    {
        std::cout << "\n--- 4. 使用 std::recursive_mutex ---" << std::endl;
        recursive_counter = 0;
        int recursion_depth = 5;
        recursive_function(recursion_depth);
        std::cout << "Recursive counter: " << recursive_counter << std::endl;
        // 每次调用 recursive_function (包括初始调用) 都会增加计数器
        ASSERT(recursive_counter == 6, "递归调用后计数器值应为 depth + 1");

        // 尝试从另一个线程锁定 recursive_mutex
        std::thread t([&]() {
            std::lock_guard<std::recursive_mutex> lock(recursive_mtx);
            recursive_counter += 10;
        });
        if (t.joinable()) { t.join(); }
        ASSERT(recursive_counter == 16, "另一个线程修改后计数器值应增加");
    }

    return 0;
}