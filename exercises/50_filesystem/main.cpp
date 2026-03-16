#include "../exercise.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>


namespace fs = std::filesystem;

int main(int argc, char **argv) {
    // 获取当前可执行文件的路径
    fs::path exe_path = fs::absolute(argv[0]);
    fs::path current_dir = exe_path.parent_path();
    fs::path temp_dir = current_dir / "temp_filesystem_test";

    // 清理可能存在的旧目录和文件
    if (fs::exists(temp_dir)) {
        fs::remove_all(temp_dir);
    }

    // TODO: 创建名为 temp_dir 的目录
    // HINT: 使用 fs::create_directory 或 fs::create_directories
    fs::create_directories(temp_dir);
    ASSERT(fs::exists(temp_dir), "temp_dir should exist");
    ASSERT(fs::is_directory(temp_dir), "temp_dir should be a directory");

    fs::path file_path = temp_dir / "test_file.txt";
    // TODO: 创建一个名为 test_file.txt 的空文件
    // HINT: 使用 std::ofstream
    std::ofstream outfile(file_path);
    outfile.close();
    ASSERT(fs::exists(file_path), "test_file.txt should exist");
    ASSERT(fs::is_regular_file(file_path), "test_file.txt should be a regular file");

    // TODO: 写入一些内容到文件中
    // HINT: 再次打开文件并写入
    std::ofstream outfile_write(file_path);
    outfile_write << "Hello Filesystem!";
    outfile_write.close();

    // TODO: 获取文件大小并断言
    uintmax_t file_size = 0;
    file_size = fs::file_size(file_path);
    ASSERT(file_size > 0, "File size should be greater than 0");

    fs::path sub_dir = temp_dir / "subdir";
    fs::path nested_file = sub_dir / "nested.txt";
    // TODO: 使用路径拼接操作符 / 创建 nested_file 的路径
    std::string expected_nested_path_str = (temp_dir.string() + fs::path::preferred_separator + "subdir" + fs::path::preferred_separator + "nested.txt");
    // NOTICE：根据操作系统，分隔符可能是 \ 或 /
    ASSERT(nested_file.string() == expected_nested_path_str, "equal");// 这种直接比较可能因分隔符不同而失败
    ASSERT(nested_file.filename() == "nested.txt", "nested.txt should be the filename");
    ASSERT(nested_file.parent_path() == sub_dir, "subdir should be the parent path of nested.txt");

    // TODO: 创建 sub_dir 及其父目录（如果 temp_dir 不存在的话，但我们已经创建了）
    // HINT: 使用 fs::create_directories 确保所有层级的目录都被创建
    fs::create_directories(sub_dir);
    ASSERT(fs::exists(sub_dir), "subdir should exist");
    ASSERT(fs::is_directory(sub_dir), "subdir should be a directory");

    // TODO: 在 temp_dir 中再创建一个文件
    fs::path another_file = temp_dir / "another.log";
    std::ofstream another_outfile(another_file);
    another_outfile.close();

    int file_count = 0;
    int dir_count = 0;
    // TODO: 遍历 temp_dir 中的所有条目，统计文件和子目录的数量
    // HINT: 使用 fs::directory_iterator
    for (const auto& entry : fs::directory_iterator(temp_dir)) {
        if (entry.is_regular_file()) {
            file_count++;
        } else if (entry.is_directory()) {
            dir_count++;
        }
    }
    ASSERT(file_count == 2, "two files");// test_file.txt, another.log
    ASSERT(dir_count == 1, "one dir");   // subdir

    fs::path renamed_file_path = temp_dir / "renamed_test_file.txt";
    // TODO: 将 test_file.txt 重命名为 renamed_test_file.txt
    // HINT: 使用 fs::rename
    fs::rename(file_path, renamed_file_path);
    ASSERT(!fs::exists(file_path), "test_file.txt should not exist");
    ASSERT(fs::exists(renamed_file_path), "renamed_test_file.txt should exist");

    fs::path moved_file_path = sub_dir / "renamed_test_file.txt";
    // TODO: 将 renamed_test_file.txt 移动到 sub_dir 目录下
    // HINT: fs::rename 也可以用于移动文件
    fs::rename(renamed_file_path, moved_file_path);
    ASSERT(!fs::exists(renamed_file_path), "renamed_test_file.txt should not exist");
    ASSERT(fs::exists(moved_file_path), "renamed_test_file.txt should exist");

    // TODO: 删除 moved_file_path 文件
    // HINT: 使用 fs::remove
    fs::remove(moved_file_path);
    ASSERT(!fs::exists(moved_file_path), "renamed_test_file.txt should not exist");

    // TODO: 删除 temp_dir 及其所有内容
    // HINT: 使用 fs::remove_all
    fs::remove_all(temp_dir);
    ASSERT(!fs::exists(temp_dir), "temp_dir should not exist");

    return 0;
}