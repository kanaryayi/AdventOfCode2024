#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

constexpr auto INPUT_FILE{ "input.txt" };
constexpr auto NUMBER_DELIMETER{ ' ' };
constexpr auto DELIMETER_OFFSET{ 2 };

void
generateVectorsFromFile(std::ifstream& file,
                        std::vector<int>& firstVector,
                        std::vector<int>& secondVector)
{
    std::string firstIntStr, secondIntStr;

    while (std::getline(file, firstIntStr, NUMBER_DELIMETER)) {
        std::getline(file, secondIntStr);
        secondIntStr = secondIntStr.substr(
          DELIMETER_OFFSET, secondIntStr.size() - DELIMETER_OFFSET);
        try {
            firstVector.push_back(std::stoi(firstIntStr));
            secondVector.push_back(std::stoi(secondIntStr));
        } catch (std::invalid_argument& e) {
            break;
        }
    }
}

int
main(int argc, char* argv[])
{
    std::vector<int> firstVector, secondVector;

    {
        std::ifstream file{ INPUT_FILE };
        generateVectorsFromFile(file, firstVector, secondVector);
    }

    std::unordered_set<int> unique{ firstVector.begin(), firstVector.end() };
    std::unordered_map<int, int> freqs;

    for (auto el : secondVector) {
        ++freqs[el];
    }

    int total = 0;

    std::for_each(unique.begin(), unique.end(), [&total, &freqs](auto el) {
        total += el * freqs[el];
    });

    std::cout << "Result of input file \"" << INPUT_FILE << "\" is: " << total
              << std::endl;

    return 0;
}
