#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <functional>

using namespace std;

struct Point {
    uint32_t x, y;

    size_t Hash() const {
        std::hash<uint64_t> point_hash;
        uint64_t temp1 = x;
        uint64_t temp2 = y;
        return point_hash(temp1 | (temp2 << 32));
    }
};

bool operator<(const Point& left, const Point& right) {
    return (left.Hash() < right.Hash());
}

struct Line {
    Point point_a;
    Point point_b;

    Line(Point&& point_a_, Point&& point_b_) : point_a(point_a_), point_b(point_b_) {}
};

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream input("d5s1.txt");
    std::vector<Line> lines;
    while (getline(input, line)) {
        size_t pos_x = line.find_first_of(",");
        uint32_t x_point_a = atoi(line.substr(0, pos_x).c_str());
        uint32_t pos_y = line.find_first_of(" -> ", pos_x);
        uint32_t y_point_a = atoi(line.substr(pos_x + 1, pos_y - (pos_x + 1)).c_str());

        pos_x = line.find_first_of(",", pos_y + 4);
        uint32_t x_point_b = atoi(line.substr(pos_y + 4, pos_x - (pos_y + 4)).c_str());
        uint32_t y_point_b = atoi(line.substr(pos_x + 1).c_str());

        lines.emplace_back(Point{x_point_a, y_point_a}, Point{x_point_b, y_point_b});
    }

    std::map<Point, int> counts;
    for (auto line : lines) {
        // Only horizontal or vertical lines
        if ((line.point_a.x != line.point_b.x) && (line.point_a.y != line.point_b.y)) {
            Point *start, *end;
            if (line.point_a.x < line.point_b.x) {
                start = &line.point_a;
                end = &line.point_b;
            } else {
                start = &line.point_b;
                end = &line.point_a;
            }
            if (start->y < end->y) {
                for (int i = 0; i <= (end->x - start->x); ++i) {
                    counts[Point{start->x + i, start->y + i}]++;
                }
            } else {
                for (int i = 0; i <= (end->x - start->x); ++i) {
                    counts[Point{start->x + i, start->y - i}]++;
                }
            }
        } else if (line.point_a.x == line.point_b.x) {
            if (line.point_a.y < line.point_b.y) {
                cout << line.point_a.y << " to " << line.point_b.y << endl;
                for (uint32_t i = line.point_a.y; i <= line.point_b.y; ++i) {
                    counts[Point{line.point_a.x, i}]++;
                }
            } else {
                cout << line.point_b.y << " to " << line.point_a.y << endl;
                for (uint32_t i = line.point_b.y; i <= line.point_a.y; ++i) {
                    counts[Point{line.point_a.x, i}]++;
                }
            }
        } else {
            if (line.point_a.x < line.point_b.x) {
                cout << line.point_a.x << " to " << line.point_b.x << endl;
                for (uint32_t i = line.point_a.x; i <= line.point_b.x; ++i) {
                    counts[Point{i, line.point_a.y}]++;
                }
            } else {
                cout << line.point_b.x << " to " << line.point_a.x << endl;
                for (uint32_t i = line.point_b.x; i <= line.point_a.x; ++i) {
                    counts[Point{i, line.point_a.y}]++;
                }
            }
        }
    }

    int total = 0;
    for (auto iter : counts) {
        if (iter.second > 1) {
            total++;
        }
    }

    cout << "Total overlapping elements: " << total << endl;
    return 0;
}
