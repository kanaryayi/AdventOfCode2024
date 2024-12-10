#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

constexpr auto INPUT_FILE{ "input.txt" };
constexpr auto DELIMETER{ ' ' };
constexpr auto MAX_DIFF{ 3 };

void
getVector(std::vector<int>& inputVector, const std::string& line)
{
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, DELIMETER)) {
        try {
            inputVector.push_back(std::stoi(token));
        } catch (const std::invalid_argument&) {
            // Handle invalid input
        }
    }
}
bool
getSafe(std::vector<int>& inputVector, int diff)
{

    int size = inputVector.size();
    std::vector<int> diffVector(size - 1);
    int safeLevelingInc{ 0 };
    int safeLevelingDec{ 0 };
    bool usedJoker{false};

    // Calc diff and hold increasing and decreasing order count
    for (int i = 1; i < size; ++i) {
        int levellingDiff{ inputVector[i - 1] - inputVector[i] };
        if (levellingDiff > 0) {
            ++safeLevelingDec;
        } else {
            ++safeLevelingInc;
        }
        diffVector[i-1] = levellingDiff;
    }

    // If increasing and decreasing order not fixable early exit
    if(std::max(safeLevelingDec, safeLevelingInc) < size - (MAX_DIFF - 1)){
        return false;
    }

    // Try potential combinations (A-C) and (B-D) in example (A-B-C-D) in case (B-C) pair violates.
    bool isInc = safeLevelingInc < safeLevelingDec;
    for (int i = 0; i < size -1; ++i) {
        int levellingDiffAbs{std::abs(diffVector[i])};
        if(MAX_DIFF < levellingDiffAbs || 0 == levellingDiffAbs || ((isInc && diffVector[i] < 0) || (!isInc && diffVector[i] > 0))){
            if(usedJoker){
                return false;
            }
            bool prevPos = false;
            bool nextPos = false;
            if(i == 0){
                int nextDiff = diffVector[i+1];
                int curDiff = diffVector[i];

                int nextPosDiff{curDiff + nextDiff};
                int nextPosDiffAbs{std::abs(nextPosDiff)};
                prevPos = true;
                if( MAX_DIFF >= nextPosDiffAbs && 0 != nextPosDiffAbs && (safeLevelingDec > safeLevelingInc == nextPosDiff > 0) ){
                    nextPos = true;
                    diffVector[i+1] = nextPosDiff;
                }
            }
            else if (i == size - 2){
                int prevDiff = diffVector[i-1];
                int curDiff = diffVector[i];
                int prevPosDiff{prevDiff + curDiff};
                int prevPosDiffAbs{std::abs(prevPosDiff)};
                nextPos = true;
                if( MAX_DIFF >= prevPosDiffAbs && 0 != prevPosDiffAbs && (prevPosDiff > 0 == safeLevelingDec > safeLevelingInc) ){
                    prevPos = true;
                    diffVector[i-1] = prevPosDiff;
                }
            }
            else{
                int prevDiff = diffVector[i-1];
                int nextDiff = diffVector[i+1];
                int curDiff = diffVector[i];

                int nextPosDiff{curDiff + nextDiff};
                int nextPosDiffAbs{std::abs(nextPosDiff)};

                int prevPosDiff{prevDiff + curDiff};
                int prevPosDiffAbs{std::abs(prevPosDiff)};

                if( MAX_DIFF >= nextPosDiffAbs && 0 != nextPosDiffAbs && (safeLevelingDec > safeLevelingInc == nextPosDiff > 0) ){
                    nextPos = true;
                    diffVector[i+1] = nextPosDiff;
                }

                if( MAX_DIFF >= prevPosDiffAbs && 0 != prevPosDiffAbs && (prevPosDiff > 0 ==  safeLevelingDec > safeLevelingInc) ){
                    prevPos = true;
                    diffVector[i-1] = prevPosDiff;
                }

            }

            if(!prevPos && !nextPos){
                return false;
            }

            usedJoker = true;
        }
    }

    return true;
}

int
main(int argc, char* argv[])
{
    std::ifstream file{ INPUT_FILE };
    std::string line;
    size_t i = 0;

    int safeReports{ 0 };

    while (std::getline(file, line)) {
        std::vector<int> inputVector;
        getVector(inputVector, line);

        if (inputVector.empty()) {
            continue;
        } else {
            bool res = getSafe(inputVector, MAX_DIFF);
            if (res) {
                ++safeReports;
            }
        }
    }

    std::cout << safeReports << std::endl;

    return 0;
}
