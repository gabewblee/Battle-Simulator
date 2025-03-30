#include "BattleField.h"
#include <queue>
#include <set>
#include <map>

struct Node {
    int x;
    int y;
    int gVal;
    int hVal;

    Node() : x(-1), y(-1), gVal(0), hVal(0) {}
    Node(int x, int y, int gVal, int hVal) : x(x), y(y), gVal(gVal), hVal(hVal) {}

    bool operator>(const Node& other) const {
        return this->gVal + this->hVal > other.gVal + other.hVal;
    }

    bool operator<(const Node& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

int manhattanDistance(int fromX, int fromY, int toX, int toY) {
    return std::abs(fromX - toX) + std::abs(fromY - toY);
}

std::vector<std::pair<int, int>> reconstructPath(std::map<Node, Node> ancestors, Node curr) {
    /* In the path reconstruction below, we intentially append the elements to the end of the path array
    in order to reduce the overall time complexity from O(n^2) to O(n).
    */
    std::vector<std::pair<int, int> > path;
    while (!(curr.x == -1 && curr.y == -1)) {
        path.emplace_back(curr.x, curr.y);
        curr = ancestors[curr];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

bool satisfiesRequirements(Field * field, int x, int y) {
    // return true;
    if (field->inBounds(x, y)) {
        Tile tile = field->getTile(x, y);
        return tile.terrain != BUILDING && !tile.isOccupied();
    }
    return false;
}

std::vector<std::pair<int, int>> findShortestPath(Field * field, int fromX, int fromY, int toX, int toY) {
    // A* algorithm
    Node start(fromX, fromY, 0, manhattanDistance(fromX, fromY, toX, toY));
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> Frontier;
    Frontier.push(start);

    std::map<Node, Node> ancestors;
    ancestors[start] = Node();

    std::vector<std::pair<int, int> > validDirections = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

    std::set<Node> Closed;
    while (!Frontier.empty()) {
        Node curr = Frontier.top();
        Frontier.pop();

        if (!Closed.count(curr)) { // If curr has not been visited
            Closed.insert(curr);
            if (curr.x == toX && curr.y == toY) { // If curr is the goal node
                return reconstructPath(ancestors, curr);
            }

            for (auto [dx, dy] : validDirections) {
                int possibleX = curr.x + dx;
                int possibleY = curr.y + dy;
                if (satisfiesRequirements(field, possibleX, possibleY)) {
                    Tile thisTile = field->getTile(possibleX, possibleY);
                    float movementCost = thisTile.getMovementCost();
                    int gVal = curr.gVal + 1 + movementCost; // Perhaps un-admissible heuristic function! Must verify
                    int hVal = manhattanDistance(possibleX, possibleY, toX, toY);
                    Node neighbour(possibleX, possibleY, gVal, hVal);
                    
                    if (!Closed.count(neighbour)) {
                        Frontier.push(neighbour);
                        if (!ancestors.count(neighbour)) {
                            ancestors[neighbour] = curr;
                        }
                    }
                }
            }
        }
    }
    return {};
}