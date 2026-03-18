add_rules("mode.debug", "mode.release")
set_encodings("utf-8")
set_warnings("all")
set_kind("binary")
set_languages("cxx17")

-- 格式化输出
target("exercise00")
add_files("00_hello_world/main.cpp")

-- 变量与运算符
target("exercise01")
add_files("01_variable&add/main.cpp")

-- 函数、声明和定义
target("exercise02")
add_files("02_function/main.cpp")

-- 形参实参
target("exercise03")
add_files("03_argument&parameter/main.cpp")

-- static 关键字
target("exercise04")
add_files("04_static/main.cpp")

-- constexpr 编译时常量和运算
target("exercise05")
add_files("05_constexpr/main.cpp")

-- 数组
target("exercise06")
add_files("06_array/main.cpp")

-- 循环
target("exercise07")
add_files("07_loop/main.cpp")

-- 指针
target("exercise08")
add_files("08_pointer/main.cpp")

-- 枚举/联合体
target("exercise09")
add_files("09_enum&union/main.cpp")

-- “普通”类型
target("exercise10")
add_files("10_trivial/main.cpp")

-- 方法
target("exercise11")
add_files("11_method/main.cpp")

-- const 修饰方法
target("exercise12")
add_files("12_method_const/main.cpp")

-- 类
target("exercise13")
add_files("13_class/main.cpp")

-- 析构器
target("exercise14")
add_files("14_class_destruct/main.cpp")

-- 复制构造函数
target("exercise15")
add_files("15_class_clone/main.cpp")

-- 移动语义
target("exercise16")
add_files("16_class_move/main.cpp")

-- 派生
target("exercise17")
add_files("17_class_derive/main.cpp")

-- 虚函数
target("exercise18")
add_files("18_class_virtual/main.cpp")

-- 虚析构函数
target("exercise19")
add_files("19_class_virtual_destruct/main.cpp")

-- 函数模板
target("exercise20")
add_files("20_function_template/main.cpp")

-- 习题：用于编译器的运行时类型
target("exercise21")
add_files("21_runtime_datatype/main.cpp")

-- 类模板
target("exercise22")
add_files("22_class_template/main.cpp")

-- 模板非类型实参
target("exercise23")
add_files("23_template_const/main.cpp")

-- std::array
target("exercise24")
add_files("24_std_array/main.cpp")

-- std::vector
target("exercise25")
add_files("25_std_vector/main.cpp")

-- std::vector<bool>
target("exercise26")
add_files("26_std_vector_bool/main.cpp")

-- 习题：步长计算
target("exercise27")
add_files("27_strides/main.cpp")

-- std::string
target("exercise28")
add_files("28_std_string/main.cpp")

-- std::map
target("exercise29")
add_files("29_std_map/main.cpp")

-- std::transform
target("exercise30")
add_files("30_std_unique_ptr/main.cpp")

-- std::accumulate
target("exercise31")
add_files("31_std_shared_ptr/main.cpp")

-- std::transform
target("exercise32")
add_files("32_std_transform/main.cpp")

-- std::accumulate
target("exercise33")
add_files("33_std_accumulate/main.cpp")

-- exercise34
target("exercise34")
add_files("34_namespace/main.cpp")

-- exercise35
target("exercise35")
add_files("35_reference_vs_pointer/main.cpp")

-- exercise36
target("exercise36")
add_files("36_exception/main.cpp")

-- exercise37
target("exercise37")
add_files("37_new_delete/main.cpp")

-- exercise38
target("exercise38")
add_files("38_lrvalue/main.cpp")

-- exercise39
target("exercise39")
add_files("39_raii/main.cpp")

-- exercise40
target("exercise40")
add_files("40_class_struct/main.cpp")

-- exercise41
target("exercise41")
add_files("41_cast/main.cpp")

-- exercise42
target("exercise42")
add_files("42_list_init/main.cpp")

-- exercise43
target("exercise43")
add_files("43_operator/main.cpp")

-- exercise44
target("exercise44")
add_files("44_friend/main.cpp")

-- exercise45
target("exercise45")
add_files("45_deque/main.cpp")

-- exercise46
target("exercise46")
add_files("46_queue/main.cpp")

-- exercise47
target("exercise47")
add_files("47_stack/main.cpp")

-- exercise48
target("exercise48")
add_files("48_priority_queue/main.cpp")

-- exercise49
target("exercise49")
add_files("49_set/main.cpp")

-- exercise50
target("exercise50")
add_files("50_filesystem/main.cpp")

-- exercise51
target("exercise51")
add_files("51_list/main.cpp")

-- exercise52
target("exercise52")
add_files("52_pair/main.cpp")

-- exercise53
target("exercise53")
add_files("53_tuple/main.cpp")

-- exercise54
target("exercise54")
add_files("54_function/main.cpp")

-- exercise55
target("exercise55")
add_files("55_chrono/main.cpp")

-- exercise56
target("exercise56")
add_files("56_multithread/main.cpp")

-- exercise57
target("exercise57")
add_files("57_future/main.cpp")

-- exercise58
target("exercise58")
add_files("58_mutex/main.cpp")

-- exercise59
target("exercise59")
add_files("59_atomic/main.cpp")

-- exercise60
target("exercise60")
add_files("60_threadpool/main.cpp")

-- exercise61
target("exercise61")
add_files("61_memory_alignment/main.cpp")

-- std::variant (C++17)
target("exercise62")
add_files("62_variant/main.cpp")

-- std::optional (C++17)
target("exercise63")
add_files("63_optional/main.cpp")

-- std::any (C++17)
target("exercise64")
add_files("64_any/main.cpp")

-- Structured Bindings (C++17)
target("exercise65")
add_files("65_structured_bindings/main.cpp")

-- if get_config("enable_optional_exercises") then

-- if constexpr (C++17)
target("exercise66")
add_files("66_if_constexpr/main.cpp")

-- Concepts (C++20)
target("exercise67")
set_languages("cxx20")
add_files("67_concepts/main.cpp")

-- Ranges (C++20)
target("exercise68")
set_languages("cxx20")
add_files("68_ranges/main.cpp")

-- Coroutines (C++20)
target("exercise69")
set_languages("cxx20")
add_files("69_coroutines/main.cpp")

-- std::bitset
target("exercise70")
add_files("70_bitset/main.cpp")

-- std::string_view (C++17)
target("exercise71")
add_files("71_string_view/main.cpp")

-- std::scoped_lock (C++17)
target("exercise72")
add_files("72_scoped_lock/main.cpp")

-- std::byte (C++17)
target("exercise73")
add_files("73_byte/main.cpp")

-- std::shared_mutex (C++14/17)
target("exercise74")
add_files("74_shared_mutex/main.cpp")

-- std::invoke (C++17)
target("exercise75")
add_files("75_invoke/main.cpp")

-- std::apply (C++17)
target("exercise76")
add_files("76_apply/main.cpp")

-- Attributes (C++11/14/17)
target("exercise77")
add_files("77_attributes/main.cpp")

-- Class Template Argument Deduction (CTAD) (C++17)
target("exercise78")
add_files("78_ctad/main.cpp")

-- CRTP (Curiously Recurring Template Pattern)
target("exercise79")
add_files("79_crtp/main.cpp")

-- end
