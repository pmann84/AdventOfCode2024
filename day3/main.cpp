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
    constexpr bool enable_conditional_parsing = true;

    // PART 1 & 2
    const std::regex mul_regex("do[n't]*\\(\\)|mul\\(([0-9]+),([0-9]+)\\)");
    std::smatch all_matches;

    auto total = 0;
    auto num_instructions = 0;
    std::string::const_iterator search_start( input.cbegin() );
    auto use_next_instruction = true;
    while(std::regex_search( search_start, input.cend(), all_matches, mul_regex))
    {
        const auto instruction = all_matches[0].str();
        if (instruction.starts_with("do")) {
            std::cout << std::format("Found instruction {}", instruction) << std::endl;
            if (instruction == "don't()") {
                use_next_instruction = false;
            } else if (instruction == "do()") {
                use_next_instruction = true;
            }
        } else {
            if (!enable_conditional_parsing || (enable_conditional_parsing &&  use_next_instruction)) {
                const auto first_operand = std::stoi(all_matches[1].str());
                const auto second_operand = std::stoi(all_matches[2].str());
                std::cout << std::format("Found instruction {}: adding {}x{} to total", instruction, first_operand, second_operand) << std::endl;

                total += first_operand * second_operand;
            }
        }
        num_instructions++;
        search_start = all_matches.suffix().first;
    }
    std::cout << std::format("For {} instructions total = {}", num_instructions, total) << std::endl;

    return 0;
}
