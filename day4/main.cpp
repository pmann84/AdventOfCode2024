#include <iostream>
#include <filesystem>
#include <format>
#include <fstream>
#include <regex>

#include <sage.hpp>

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
    std::vector<std::vector<std::string>> word_grid;
    std::ifstream file(path);
    std::string str;

    while (std::getline(file, str))
    {
        std::vector<std::string> row;
        for (int i = 0; i < str.size(); i++) {
            row.push_back(str.substr(i, 1));
        }
        word_grid.emplace_back(row);
    }
    return word_grid;
}

struct direction {
    int32_t x;
    int32_t y;
};

int32_t find_word_in_grid(const std::vector<std::vector<std::string>>& grid, const std::string& word_to_find) {
    const std::vector<direction> directions = {
        {-1, -1},
        {0, -1},
        {1, -1},
        {-1, 0},
        {0, 0},
        {1, 0},
        {-1, 1},
        {0, 1},
        {1, 1}
    };

    auto word_count = 0;
    for (auto i = 0; i < grid.size(); i++) {
        for (auto j = 0; j < grid[i].size(); j++) {
            // Early exit, only test from letters that the word starts with
            if (grid[i][j] != word_to_find.substr(0, 1)) continue;

            // Try each of 8 different directions looking for the word
            for (auto [x, y] : directions) {
                bool found = true;
                for (auto l = 0; l < word_to_find.size(); l++) {
                    if (l > 0 && !found) continue;
                    const auto x_i = i + x * l;
                    const auto y_i = j + y * l;
                    if (x_i >= 0 && x_i < grid[i].size() && y_i >= 0 && y_i < grid.size()) {
                        if (grid[x_i][y_i] != word_to_find.substr(l, 1)) {
                            found = false;
                        }
                    } else {
                        found = false;
                    }
                }
                if (found) word_count++;
            }
        }
    }
    return word_count;
}

int32_t find_x_words_in_grid(const std::vector<std::vector<std::string>>& grid, const std::string& word_to_find) {
    if (word_to_find.size() % 2 == 0) {
        std::cout << "Incorrect word length, must be odd length." << std::endl;
        return 0;
    }

    const std::vector<direction> directions = {
        {-1, -1},
        {1, -1},
        {-1, 1},
        {1, 1}
    };
    const auto half_word_length = (word_to_find.size() - 1)/ 2;
    const auto center_point = word_to_find.substr(half_word_length, 1);
    auto x_count = 0;

    for (auto i = half_word_length; i < grid.size() - half_word_length; i++) {
        for (auto j = half_word_length; j < grid[i].size() - half_word_length; j++) {
            // Early exit, only test from letters that the word starts with
            if (grid[i][j] != center_point) continue;

            auto found_count = 0;
            // Try each of diagonal directions looking for the word
            for (auto [x, y] : directions) {
                bool found = true;
                for (auto l = -static_cast<int32_t>(half_word_length); l <= static_cast<int32_t>(half_word_length); l++) {
                    if (l > -static_cast<int32_t>(half_word_length) && !found) continue;
                    const auto x_i = i + x * l;
                    const auto y_i = j + y * l;
                    if (x_i >= 0 && x_i < grid[i].size() && y_i >= 0 && y_i < grid.size()) {
                        if (grid[x_i][y_i] != word_to_find.substr(l + half_word_length, 1)) {
                            found = false;
                        }
                    } else {
                        found = false;
                    }
                }
                if (found) found_count++;
            }
            if (found_count == 2) x_count++;
        }
    }
    return x_count;
}


int main(int argc, char *argv[]) {
    const std::filesystem::path input_path = get_input_path(argc, argv);
    const std::vector<std::vector<std::string>> input = read_input(input_path);

    // PART 1
    const std::string word_to_find("XMAS");
    const auto word_count = find_word_in_grid(input, word_to_find);
    std::cout << std::format("Found {} instances of the word {} in grid of size {}x{}", word_count, word_to_find, input.size(), input[0].size())<< std::endl;

    // PART 2
    const std::string x_word_to_find("MAS");
    const auto x_count = find_x_words_in_grid(input, x_word_to_find);
    std::cout << std::format("Found {} x-instances of the word {} in grid of size {}x{}", x_count, x_word_to_find, input.size(), input[0].size())<< std::endl;

    return 0;
}
