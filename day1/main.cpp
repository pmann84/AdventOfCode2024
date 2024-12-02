#include <sage.hpp>

#include <iostream>
#include <filesystem>
#include <fstream>
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

int32_t distance(const std::pair<uint32_t, uint32_t>& p)
{
    return std::abs(static_cast<int32_t>(p.first - p.second));
}

uint32_t accumulate_distance(uint32_t sum, const std::pair<uint32_t, uint32_t>& p)
{
    return sum + distance(p);
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
    std::vector<std::pair<uint32_t, uint32_t>> input;
    for (auto i = 0; i < a.size(); i++)
    {
        input.emplace_back(a[i], b[i]);
    }

    const auto total_dist = std::accumulate(input.begin(), input.end(), 0, accumulate_distance);
    std::cout << std::format("Total Distance = {}", total_dist) << std::endl;

    // PART 2
    uint32_t similarity = std::accumulate(a.begin(), a.end(), 0, [&b](uint32_t sum, const uint32_t& item)
    {
        const auto num_in_second_list = std::ranges::count(b.begin(), b.end(), item);
        return sum + item * num_in_second_list;
    });
    std::cout << std::format("Similarity Score = {}", similarity) << std::endl;
    return 0;
}
