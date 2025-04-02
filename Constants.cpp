#include "Constants.h"

const std::vector<std::vector<int>> fieldOne = {
    {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
    {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
    {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

const std::vector<std::vector<int>> fieldTwo = {
    {0, 2, 3, 3, 0, 3, 3, 0, 3, 3, 2, 0},
    {0, 2, 3, 3, 0, 3, 3, 0, 3, 3, 2, 0},
    {0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 3, 3, 0, 3, 3, 0, 3, 3, 2, 0},
    {0, 2, 3, 3, 0, 3, 3, 0, 3, 3, 2, 0},
    {0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0}
};


const std::vector<std::vector<std::vector<int>>> fields = { fieldOne, fieldTwo };
const std::string bgImgPath = "Frontend/Background Images/";
const std::vector<std::string> texturePaths = {
    bgImgPath + "Road.png",     // ROAD = 0
    bgImgPath + "sidewalk.png", // SIDEWALK = 1
    bgImgPath + "park.png",     // PARK = 2
    bgImgPath + "Building.png"  // BUILDING = 3
};
