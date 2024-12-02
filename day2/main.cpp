#include <iostream>
#include <filesystem>
#include <format>
#include <fstream>
#include <ranges>
#include <vector>

#include "sage.hpp"

std::filesystem::path get_input_path(int argc, char *argv[]) {
    std::filesystem::path input_path("sample_input.txt");
    std::cout << argc << argv[0] << std::endl;
    if (argc == 2)
    {
        input_path = std::filesystem::path(argv[1]);
    }
    return input_path;
}

std::vector<std::vector<std::string>> read_input(const std::filesystem::path& path) {
    std::cout << std::format("Reading input from {}", path.string()) << std::endl;
    std::vector<std::vector<std::string>> reports;
    std::ifstream file(path);
    std::string str;

    while (std::getline(file, str))
    {
        const auto report = sage::string::utilities::split(str, std::string(" "));
        reports.emplace_back(report);
    }
    return reports;
}

namespace ranges::utils {
    template<std::integral T>
    bool is_positive(const T idx) {
        return idx >= 0;
    }

    template<std::integral T>
    bool is_negative(const T idx) {
        return idx < 0;
    }

    template<std::integral T>
    T abs(const T elem) {
        return std::abs(elem);
    }

    bool is_true(const bool elem) {
        return elem == true;
    }
}

void print_report_validation(const std::vector<std::string>& report, bool is_safe) {
    std::cout << "Report [";
    for (const auto& elem: report) {
        std::cout << elem;
        if (elem != report.back()) std::cout << ", ";
    }
    std::cout << "]: " << (is_safe ? "SAFE": "UNSAFE") << std::endl;
}

uint32_t convert_func(const std::string& str) {
    return std::stoi(str);
};

bool is_report_safe(const std::vector<std::string>& report) {
    auto direction = 0;
    auto is_level_jump_safe = [&direction](std::tuple<int32_t, int32_t> adj_pair) {
        auto [prev, next] = adj_pair;
        const bool is_the_same = prev == next;
        // Set the direction for the first time, if any of the next directions
        // are different then it is unsafe! We don't need to calculate this
        // everytime
        if (direction == 0) direction = (next - prev) / std::abs(next - prev);
        // Conditions to figure out whether this level jump is "safe"
        // - must match the initial direction
        // - cannot be more than 3 away
        return (!is_the_same) && (direction == 1 ? next > prev && next <= prev + 3 : next < prev && next >= prev - 3);
    };

    return std::ranges::all_of(report
        | std::ranges::views::transform(convert_func)
        | std::views::adjacent<2>
        | std::views::transform(is_level_jump_safe),
    ranges::utils::is_true);
};

int main(int argc, char *argv[]) {
    const std::filesystem::path input_path = get_input_path(argc, argv);
    std::vector<std::vector<std::string>> input = read_input(input_path);

    // PART 1
    int32_t num_safe_reports = 0;
    for (const auto& report: input) {
        const bool is_safe = is_report_safe(report);

        // Print report output
        // print_report_validation(report, is_safe);

        // Increment
        if (is_safe) {
            num_safe_reports++;
        }
    }
    std::cout << std::format("Found {} SAFE reports.", num_safe_reports) << std::endl;

    // PART 2
    int32_t num_safe_reports_adjusted = 0;
    for (const auto& report: input) {
        bool is_safe = is_report_safe(report);

        // If report isn't safe just run through every permutation with each level missing
        if (!is_safe) {
            for (auto i = 0; i < report.size(); i++) {
                auto adjusted_report = report;
                adjusted_report.erase(adjusted_report.begin() + i);
                if (is_report_safe(adjusted_report)) {
                    is_safe = true;
                }
            }
        }

        // Print report output
        // print_report_validation(report, is_safe);

        // Increment
        if (is_safe) {
            num_safe_reports_adjusted++;
        }
    }
    std::cout << std::format("Found {} SAFE reports (adjusted).", num_safe_reports_adjusted) << std::endl;

    return 0;
}
