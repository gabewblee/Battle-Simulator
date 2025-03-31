#ifndef BATTLEFIELD
#define BATTLEFIELD

#include "Fields.h"
#include "Tile.h"
#include <queue>
#include <set>
#include <map>

struct Node {
    int x;
    int y;
    int gVal;
    int hVal;

    Node(int x = -1, int y = -1, int gVal = -1, int hVal = -1) : x(x), y(y), gVal(gVal), hVal(hVal) {}

    static Node invalidNode() { return Node(-1, -1, 0, 0); }

    bool isInvalid() const { return this->x == -1 && this->y == -1; }

    bool operator==(const Node& other) const { return this->x == other.x && this->y == other.y; }
    
    bool operator<(const Node& other) const {
        if (this->x != other.x) return x < other.x;
        else return this->y < other.y;
    }
    
    bool operator>(const Node& other) const {
        if (this->x != other.x) return this->x > other.x;
        else return this->y > other.y;
    }
};

struct PriorityComparator {
    bool operator()(const Node& curr, const Node& other) const { return curr.gVal + curr.hVal > other.gVal + other.hVal; }
};

class Field {
public:
    int fieldNumber;
    std::vector<std::vector<Tile>> field;

    Field(int fieldNumber);

    std::vector<std::vector<Tile>> processField(int fieldNumber);
    Tile getTile(int x, int y);
    bool inBounds(int x, int y);
    int manhattanDistance(int fromX, int fromY, int toX, int toY);
    std::vector<std::pair<int, int>> reconstructPath(std::map<Node, Node> ancestors, Node curr);
    bool satisfiesRequirements(int x, int y);
    std::vector<std::pair<int, int>> findShortestPath(int fromX, int fromY, int toX, int toY);
};

#endif