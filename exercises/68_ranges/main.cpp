#include "../exercise.h"
#include <algorithm>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

// READ: C++20 Ranges <https://zh.cppreference.com/w/cpp/ranges>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 使用 ranges::views::filter 筛选偶数
    auto even_numbers_view = numbers | std::views::filter([](int n) { return n % 2 == 0; });
    std::vector<int> even_numbers;
    std::ranges::copy(even_numbers_view, std::back_inserter(even_numbers));
    ASSERT(even_numbers.size() == 5, "筛选出的偶数数量");
    ASSERT(even_numbers[0] == 2, "第一个偶数");
    ASSERT(even_numbers.back() == 10, "最后一个偶数");

    // 使用 ranges::views::transform 将数字平方
    auto squared_numbers_view = numbers | std::views::transform([](int n) { return n * n ; });
    std::vector<int> squared_numbers;
    std::ranges::copy(squared_numbers_view, std::back_inserter(squared_numbers));
    ASSERT(squared_numbers.size() == 10, "平方后数字的数量");
    ASSERT(squared_numbers[0] == 1, "第一个数字的平方");
    ASSERT(squared_numbers[2] == 9, "第三个数字的平方");

    // 组合视图：筛选偶数，然后平方，最后取前三个
    auto processed_view = numbers
                        | std::views::filter([](int n){
        return n % 2 == 0 ; })
                        | std::views::transform([](int n){
        return n * n ; })
                        | std::views::take(3);

    std::vector<int> processed_numbers;
    std::ranges::copy(processed_view, std::back_inserter(processed_numbers));
    ASSERT(processed_numbers.size() == ?, "处理后数字的数量");
    ASSERT(processed_numbers[0] == ?, "第一个处理后的数字 (2*2)");
    ASSERT(processed_numbers[1] == ?, "第二个处理后的数字 (4*4)");
    ASSERT(processed_numbers[2] == ?, "第三个处理后的数字 (6*6)");

    // 使用 ranges 算法 (例如 ranges::sort)
    std::vector<int> unsorted = {5, 1, 4, 2, 3};
    std::ranges::sort(unsorted);
    ASSERT(std::ranges::is_sorted(unsorted), "向量应该已排序");
    ASSERT(unsorted[0] == ?, "排序后的第一个元素");
    ASSERT(unsorted.back() == ?, "排序后的最后一个元素");

    // 使用 ranges::views::iota 生成序列
    auto iota_view = std::views::iota(1, 6);// 生成 [1, 2, 3, 4, 5]
    int sum = 0;
    for (int i : iota_view) {
        sum += i;
    }
    ASSERT(sum == ?, "1到5的和");

    // THINK: Ranges 和传统迭代器+算法相比有什么优势？
    // THINK: 视图 (View) 和容器 (Container) 的主要区别是什么？
    // THINK: 管道操作符 `|` 在 Ranges 中是如何工作的？

    return 0;
}