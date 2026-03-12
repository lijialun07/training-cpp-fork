#include "../exercise.h"
#include <map>
#include <unordered_map>

// READ: `std::map` <https://zh.cppreference.com/w/cpp/container/map>
// READ: `std::unordered_map` <https://zh.cppreference.com/w/cpp/container/unordered_map>

template<class k, class v>
bool key_exists(std::map<k, v> const &map, k const &key) {
    // TODO: 实现函数
    bool ret = false;
    for (auto [k_, v_] : map) {
        if (key == k_) {
            ret = true;
            break;
        }
    }
    return ret;
}

template<class k, class v>
void set(std::map<k, v> &map, k key, v value) {
    // TODO: 实现函数
    auto it = map.find(key);
    if (it == map.end()) {
        map.insert(std::pair<k, v>(key, value));
    } else {
        it->second = value;
    }
}

// READ: `std::unordered_map` <https://zh.cppreference.com/w/cpp/container/unordered_map>
// `std::unordered_map` 是哈希表，平均情况下查找、插入和删除的时间复杂度为 O(1)，但最坏情况下为 O(n)。
// 元素无序。

// `std::map` 是红黑树，查找、插入和删除的时间复杂度为 O(log n)。
// 元素按键排序。

template<class k, class v>
bool unordered_key_exists(std::unordered_map<k, v> const &map, k const &key) {
    // TODO: 实现函数
    bool ret = false;
    for (auto [k_, v_] : map) {
        if (key == k_) {
            ret = true;
            break;
        }
    }
    return ret;
}

template<class k, class v>
void unordered_set(std::unordered_map<k, v> &map, k key, v value) {
    // TODO: 实现函数
    auto it = map.find(key);
    if (it == map.end()) {
        map.insert(std::pair<k, v>(key, value));
    } else {
        it->second = value;
    }
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    using namespace std::string_literals;

    std::map<std::string, std::string> secrets;

    set(secrets, "hello"s, "world"s);
    ASSERT(key_exists(secrets, "hello"s), "\"hello\" shoud be in `secrets`");
    ASSERT(!key_exists(secrets, "foo"s), "\"foo\" shoud not be in `secrets`");

    set(secrets, "foo"s, "bar"s);
    set(secrets, "Infini"s, "Tensor"s);
    ASSERT(secrets["hello"] == "world", "hello -> world");
    ASSERT(secrets["foo"] == "bar", "foo -> bar");
    ASSERT(secrets["Infini"] == "Tensor", "Infini -> Tensor");

    set(secrets, "hello"s, "developer"s);
    ASSERT(secrets["hello"] == "developer", "hello -> developer");

    // ---- unordered_map tests ----
    std::unordered_map<std::string, std::string> unordered_secrets;

    // TODO: 补全以下代码
    unordered_set(unordered_secrets, "hello"s, "world"s);
    ASSERT(unordered_key_exists(unordered_secrets, "hello"s), "'hello' should be in `unordered_secrets`");
    ASSERT(!unordered_key_exists(unordered_secrets, "foo"s), "'foo' should not be in `unordered_secrets`");

    unordered_set(unordered_secrets, "foo"s, "bar"s);
    unordered_set(unordered_secrets, "Infini"s, "Tensor"s);
    // NOTICE: `std::unordered_map` 无法保证元素顺序，因此 ASSERT 中的值需要根据实际运行情况或特定哈希实现来确定。
    // 这里我们仅验证键值对是否正确设置。
    ASSERT(unordered_secrets["hello"] == "world", "hello -> world");
    ASSERT(unordered_secrets["foo"] == "bar", "foo -> bar");
    ASSERT(unordered_secrets["Infini"] == "Tensor", "Infini -> Tensor");

    unordered_set(unordered_secrets, "hello"s, "developer"s);
    ASSERT(unordered_secrets["hello"] == "developer", "hello -> developer");

    // THINK: `std::map` 和 `std::unordered_map` 的关键区别是什么？
    //        在什么情况下应该选择 `std::map`？什么情况下选择 `std::unordered_map`？
    //        尝试修改代码，使用不同的键类型（例如 int），观察行为。

    return 0;
}
