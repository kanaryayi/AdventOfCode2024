#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

constexpr auto INPUT_FILE{ "input.txt" };
constexpr auto DELIMETER{ ' ' };
constexpr auto MAX_DIFF{ 3 };

void
getVector(std::vector<int>& inputVector, std::string& line)
{
    size_t i{ 0 };
    auto end = line.find(DELIMETER, i);
    try {
        while (end != line.npos) {
            auto numString = line.substr(i, end - i);
            inputVector.push_back(std::stoi(numString));
            i = end + 1;
            end = line.find(DELIMETER, i);
        }
        auto numString = line.substr(i, line.size() - i);
        inputVector.push_back(std::stoi(numString));
        i = 0;
    } catch (std::invalid_argument& e) {
    }
}

bool
getSafe(std::vector<int>& inputVector,
        std::function<bool(int, int)>&& comp,
        int diff)
{
    auto prev{ inputVector[0] };
    bool res{ true };
    for (int i = 1; i < inputVector.size(); ++i) {
        res &= comp(prev, inputVector[i]);
        res &= std::abs(prev - inputVector[i]) <= 3;
        prev = inputVector[i];
    }
    return res;
}
int
main(int argc, char* argv[])
{
    std::ifstream file{ INPUT_FILE };
    std::string line;
    size_t i{ 0 };

    int safeReports{ 0 };
    while (std::getline(file, line)) {
        std::vector<int> inputVector;
        getVector(inputVector, line);
        std::function<bool(int, int)> comp;

        if (inputVector.empty()) {
            continue;
        } else if (inputVector[0] > inputVector[1]) { // Increasing
            if (getSafe(inputVector, std::greater<int>(), MAX_DIFF)) {
                ++safeReports;
            }
        } else if (inputVector[0] < inputVector[1]) { // Decreasing
            if (getSafe(inputVector, std::less<int>(), MAX_DIFF)) {
                ++safeReports;
            }
        }
    }
    std::cout << std::endl << safeReports << std::endl;

    return 0;
}
