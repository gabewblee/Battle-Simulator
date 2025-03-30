#ifndef BATTLEFIELD
#define BATTLEFIELD

#include "Fields.h"
#include "Tile.h"

class Field {
public:
    int fieldNumber;
    std::vector<std::vector<Tile> > field;

    Field(int fieldNumber) : fieldNumber(fieldNumber) {
        this->field = processField(fieldNumber);
    }

    std::vector<std::vector<Tile> > processField(int fieldNumber) {
        std::vector<std::vector<int> > selectField = fields[fieldNumber];
        std::vector<std::vector<Tile> > processedField;
        int n = selectField.size();
        for (int y = 0 ; y < n ; y++) {
            std::vector<Tile> row;
            for (int x = 0 ; x < n ; x++) {
                TYPE tileType = (TYPE) selectField[y][x];
                row.push_back(Tile(tileType));
            }
            processedField.push_back(row);
        }
        return processedField;
    }

    Tile getTile(int x, int y) {
        return this->field[y][x];
    }

    bool inBounds(int x, int y) {
        int n = this->field.size();
        return 0 <= x && x < n && 0 <= y && y < n;
    }
};

#endif