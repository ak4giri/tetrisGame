#include <vector>
#include "colors.h"

const Color  blue = {13, 64, 216, 255};
const Color  orange = {226, 116, 17, 255};
const Color  darkPurple = {112, 31, 126, 255};
const Color  white = {255, 255, 255, 255};
const Color  magenta = {255, 0, 255, 255};
const Color  yellow = {253, 249, 0, 255};
const Color  lime = {0, 158, 47, 255};
const Color  darkGrey = {110, 80, 80, 255};

std::vector<Color> GetCellColors(){
    return {darkGrey, blue, orange, darkPurple, white, magenta, yellow, lime};
};
