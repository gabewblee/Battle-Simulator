#include "Battlefield.h"
#include "Fields.h"
#include <queue>
#include <set>
#include <map>

Field::Field(int fieldNumber) : fieldNumber(fieldNumber) { this->field = this->processField(fieldNumber); }

std::vector<std::vector<Tile>> Field::processField(int fieldNumber) {
    std::vector<std::vector<int>> selectField = fields[fieldNumber];
    std::vector<std::vector<Tile>> processedField;
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

Tile Field::getTile(int x, int y) {
    return this->field[y][x];
}

bool Field::inBounds(int x, int y) {
    int n = this->field.size();
    return 0 <= x && x < n && 0 <= y && y < n;
}

int Field::manhattanDistance(int fromX, int fromY, int toX, int toY) {
    return std::abs(fromX - toX) + std::abs(fromY - toY);
}

std::vector<std::pair<int, int>> Field::reconstructPath(std::map<Node, Node> ancestors, Node curr) {
    /* In the path reconstruction below, we intentially append the elements to the end of the path array
    in order to reduce the overall time complexity from O(n^2) to O(n).
    */
    std::vector<std::pair<int, int>> path;
    while (!curr.isInvalid()) {
        path.emplace_back(curr.x, curr.y);
        curr = ancestors[curr];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

bool Field::satisfiesRequirements(int x, int y) {
    if (!inBounds(x, y)) {
        return false;
    } else {
        Tile tile = this->getTile(x, y);
        if (!tile.traversible()) return false;
        if (tile.isOccupied()) return false;
        return true;
    }
}

std::vector<std::pair<int, int>> Field::findShortestPath(int fromX, int fromY, int toX, int toY) {
    Node start(fromX, fromY, 0, manhattanDistance(fromX, fromY, toX, toY));
    std::priority_queue<Node, std::vector<Node>, PriorityComparator> Frontier;
    Frontier.push(start);

    std::map<Node, Node> ancestors;
    ancestors[start] = Node::invalidNode();

    std::vector<std::pair<int, int>> validDirections = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    std::set<Node> Closed;

    while (!Frontier.empty()) {
        Node curr = Frontier.top();
        Frontier.pop();

        if (!Closed.count(curr)) {
            Closed.insert(curr);
            if (curr.x == toX && curr.y == toY) {
                return reconstructPath(ancestors, curr);
            }

            for (auto [dx, dy] : validDirections) {
                int possibleX = curr.x + dx;
                int possibleY = curr.y + dy;
                if (satisfiesRequirements(possibleX, possibleY)) {
                    Tile thisTile = this->getTile(possibleX, possibleY);
                    float movementCost = thisTile.getMovementCost();
                    int gVal = curr.gVal + 1 + movementCost;
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