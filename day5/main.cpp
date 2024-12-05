#include <iostream>
#include <filesystem>
#include <format>
#include <fstream>
#include <regex>

std::filesystem::path get_input_path(int argc, char *argv[]) {
    std::filesystem::path input_path("sample_input.txt");
    std::cout << argc << argv[0] << std::endl;
    if (argc == 2)
    {
        input_path = std::filesystem::path(argv[1]);
    }
    return input_path;
}

std::string read_input(const std::filesystem::path& path) {
    std::cout << std::format("Reading input from {}", path.string()) << std::endl;
    std::ifstream file(path);
    std::string line;
    std::string memory_str;
    while (std::getline(file, line)) {
      memory_str += line;
    }
    return memory_str;
}

int main(int argc, char *argv[]) {
    const std::filesystem::path input_path = get_input_path(argc, argv);
    const std::string input = read_input(input_path);

    return 0;
}
