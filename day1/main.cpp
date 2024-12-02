#include <sage.hpp>

#include <iostream>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <vector>


std::pair<std::vector<uint32_t>, std::vector<uint32_t>> read_input(const std::filesystem::path& path) {
    std::cout << std::format("Reading input from {}", path.string()) << std::endl;
    std::vector<uint32_t> inputA, inputB;
    std::ifstream file(path);
    std::string str;
    while (std::getline(file, str))
    {
        const auto pair = sage::string::utilities::split(str, std::string("   "));
        inputA.push_back(std::stoi(pair[0]));
        inputB.push_back(std::stoi(pair[1]));
    }

    return std::make_pair(inputA, inputB);
}

template <typename T>
T distance(T a, T b)
{
    return std::abs(a-b);
}

int main(int argc, char *argv[]) {
    std::filesystem::path input_path("sample_input.txt");
    std::cout << argc << argv[0] << std::endl;
    if (argc == 2)
    {
        input_path = std::filesystem::path(argv[1]);
    }
    auto [a, b] = read_input(input_path);

    // PART 1
    // Sort vectors
    std::ranges::sort(a);
    std::ranges::sort(b);

    const auto total_dist = std::ranges::fold_left(
        std::ranges::views::zip_transform(
            distance<int32_t>,
            a,
            b
        ),
        0,
        std::plus());
    std::cout << std::format("Total Distance = {}", total_dist) << std::endl;

    // PART 2
    auto count_elems = [&b](const uint32_t& item)
    {
        return std::ranges::count(b.begin(), b.end(), item);
    };

    uint32_t similarity = std::ranges::fold_left(
        std::ranges::views::zip_transform(
            std::multiplies(),
            a,
            a | std::ranges::views::transform(count_elems)
        ),
        0,
        std::plus());
    std::cout << std::format("Similarity Score = {}", similarity) << std::endl;
    return 0;
}
