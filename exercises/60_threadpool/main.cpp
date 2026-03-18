#include "../exercise.h"
#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

// READ: 线程池的基本概念和实现
// READ: std::thread <https://zh.cppreference.com/w/cpp/thread/thread>
// READ: std::mutex <https://zh.cppreference.com/w/cpp/thread/mutex>
// READ: std::condition_variable <https://zh.cppreference.com/w/cpp/thread/condition_variable>
// READ: std::future <https://zh.cppreference.com/w/cpp/thread/future>
// READ: std::packaged_task <https://zh.cppreference.com/w/cpp/thread/packaged_task>


// TODO: 实现一个简化的线程池
// HINT：使用 std::thread, std::mutex, std::condition_variable, std::future, std::packaged_task
class ThreadPool {
public:
    explicit ThreadPool(size_t num_threads) {
        // TODO: 初始化线程池，创建指定数量的线程
        workers_.reserve(num_threads);
        for (size_t i = 0; i < num_threads; ++i) {
            workers_.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex_);
                        // 等待直到有任务或线程池停止
                        condition_.wait(lock, [this] {
                            return stopped_ || !tasks_.empty();
                        });

                        // 线程池已停止且任务队列为空，退出线程
                        if (stopped_ && tasks_.empty()) {
                            return;
                        }

                        // 取出队首任务
                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }
                    // 在锁外执行任务，避免长时间持锁
                    task();
                }
            });
        }
    }

    // 禁止拷贝和移动
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;
    ThreadPool(ThreadPool &&) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;

    // 析构函数，停止线程池
    ~ThreadPool() {
        // TODO: 停止线程池，等待所有任务完成
        stop();
    }

    // 向线程池提交一个任务
    // 返回 std::future 以便调用者获取任务结果
    template<class F, class... Args>
    auto enqueue(F &&f, Args &&...args) -> std::future<decltype(std::declval<F>()(std::declval<Args>()...))> {
        // TODO: 提交任务到线程池
        using ReturnType = decltype(std::declval<F>()(std::declval<Args>()...));

        // 将函数和参数绑定，包装为 packaged_task
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        // 获取 future，用于返回给调用者
        std::future<ReturnType> result = task->get_future();

        {
            std::unique_lock<std::mutex> lock(queue_mutex_);

            // 线程池已停止，禁止提交新任务
            if (stopped_) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }

            // 将任务加入队列（包装为 std::function<void()>）
            tasks_.emplace([task]() { (*task)(); });
        }

        // 通知一个等待中的工作线程
        condition_.notify_one();
        return result;
    }

    // 停止线程池
    void stop() {
        // TODO: 停止线程池，等待所有任务完成
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            if (stopped_) return; // 防止重复调用
            stopped_ = true;
        }
        // 唤醒所有工作线程，让它们检查退出条件
        condition_.notify_all();
        join();
    }

    // 等待所有工作线程结束
    void join() {
        // TODO: 等待所有任务完成
        for (auto &worker : workers_) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

private:
    std::vector<std::thread>          workers_;      // 工作线程列表
    std::queue<std::function<void()>> tasks_;        // 任务队列
    std::mutex                        queue_mutex_;  // 保护任务队列的互斥锁
    std::condition_variable           condition_;    // 用于线程间通知
    bool                              stopped_{false}; // 线程池停止标志
};

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 1. 创建一个包含 4 个线程的线程池
    ThreadPool pool(4);

    std::atomic<int> counter = 0;
    auto increment_counter = [&counter]() {
        counter.fetch_add(1, std::memory_order_relaxed);
    };

    // 2. 向线程池提交一个简单的任务 (增加计数器)
    std::future<void> future1 = pool.enqueue(increment_counter);
    future1.get();// 等待任务完成
    ASSERT(counter.load() == 1, "Counter should be 1 after one task");

    // 3. 提交一个返回值的任务
    auto multiply = [](int a, int b) { return a * b; };
    std::future<int> future2 = pool.enqueue(multiply, 5, 6);
    int result = future2.get();// 等待并获取结果
    ASSERT(result == 30, "Result of 5 * 6 should be 30");

    // 4. 提交多个任务
    std::vector<std::future<void>> futures;
    int num_tasks = 10;
    for (int i = 0; i < num_tasks; ++i) {
        futures.emplace_back(pool.enqueue(increment_counter));
    }

    // 等待所有任务完成
    for (auto &fut : futures) {
        fut.get();
    }

    // 验证计数器的最终值 (初始为1，加上10次递增)
    ASSERT(counter.load() == 11, "Counter should be 11 after 10 more tasks");

    // 5. 线程池析构函数会自动停止并Join所有线程
    // (无需显式调用 stop 或 join)
    return 0;
}