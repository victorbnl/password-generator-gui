#include <cstdlib>
#include <array>
#include <vector>

#include "random.h"

int randomChoiceVectorInt(std::vector<int> choices) {
    return choices[std::rand() % choices.size()];
}
