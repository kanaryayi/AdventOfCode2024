#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
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

    std::sort(firstVector.begin(), firstVector.end());
    std::sort(secondVector.begin(), secondVector.end());

    int total = 0;
    for (int i = 0; i < firstVector.size(); ++i) {
        total += std::abs(firstVector[i] - secondVector[i]);
    }

    std::cout << "Result of input file \""<< INPUT_FILE << "\" is: "<< total << std::endl;

    return 0;
}
