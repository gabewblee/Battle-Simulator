#ifndef CONSTANTS
#define CONSTANTS

#include <vector>
#include <string>

enum TYPE {
    ROAD,
    SIDEWALK,
    PARK,
    BUILDING
};

enum ViewState {
    TITLE,
    FIELDONE,
    FIELDTWO,
    FIELDTHREE,
    FIELDFOUR
};

extern const std::vector<std::vector<int>> fieldOne;
extern const std::vector<std::vector<int>> fieldTwo;
extern const std::vector<std::vector<std::vector<int>>> fields;
extern const std::string bgImgPath;
extern const std::vector<std::string> texturePaths;

#endif