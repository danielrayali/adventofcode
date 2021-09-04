#include <iostream>
#include <map>
#include <list>
#include <fstream>
#include <string>

using namespace std;

class SparseCube {
public:
    struct Limits {
        int x_min = 0;
        int x_max = 0;
        int y_min = 0;
        int y_max = 0;
        int z_min = 0;
        int z_max = 0;
        int w_min = 0;
        int w_max = 0;
    };

    SparseCube() = default;

    ~SparseCube() = default;

    Limits GetLimits() const {
        return limits_;
    }

    int GetSize() const {
        return size_;
    }

    void Insert(int x, int y, int z, int w) {
        cube_[w][z][y].push_back(x);
        if (x < limits_.x_min) limits_.x_min = x;
        if (x > limits_.x_max) limits_.x_max = x;
        if (y < limits_.y_min) limits_.y_min = y;
        if (y > limits_.y_max) limits_.y_max = y;
        if (z < limits_.z_min) limits_.z_min = z;
        if (z > limits_.z_max) limits_.z_max = z;
        if (w < limits_.w_min) limits_.w_min = w;
        if (w > limits_.w_max) limits_.w_max = w;
        ++size_;
    }

    void Remove(int x, int y, int z, int w) {
        auto w_result = cube_.find(w);
        if (w_result == cube_.end()) {
            cerr << "Unexpected early return on w in Remove()" << endl;
            return;
        }

        auto z_result = w_result->second.find(z);
        if (z_result == w_result->second.end()) {
            cerr << "Unexpected early return on z in Remove()" << endl;
            return;
        }

        auto y_result = z_result->second.find(y);
        if (y_result == z_result->second.end()) {
            cerr << "Unexpected early return on y in Remove()" << endl;
            return;
        }

        for (auto iter = y_result->second.begin(); iter != y_result->second.end(); iter++) {
            if (*iter == x) {
                y_result->second.erase(iter);
                return;
            }
        }

        cerr << "Could not find data in Remove()" << endl;
    }

    bool Has(int x, int y, int z, int w) const {
        auto w_result = cube_.find(w);
        if (w_result == cube_.end()) return false;

        auto z_result = w_result->second.find(z);
        if (z_result == w_result->second.end()) return false;

        auto y_result = z_result->second.find(y);
        if (y_result == z_result->second.end()) return false;

        for (auto x_result : y_result->second) {
            if (x_result == x) return true;
        }

        return false;
    }

    void Print() const {
        for (int w = limits_.w_min; w <= limits_.w_max; ++w) {
            for (int z = limits_.z_min; z <= limits_.z_max; ++z) {
                cout << "z=" << z << ", " << "w=" << w << endl;
                for (int y = limits_.y_min; y <= limits_.y_max; ++y) {
                    for (int x = limits_.x_min; x <= limits_.x_max; ++x) {
                        if (this->Has(x, y, z, w)) {
                            cout << '#';
                        } else {
                            cout << '.';
                        }
                    }
                    cout << endl;
                }
                cout << endl;
            }
        }
    }

    SparseCube(const SparseCube& sparse_cube) {
        if (this != &sparse_cube) {
            cube_ = sparse_cube.cube_;
            limits_ = sparse_cube.limits_;
            size_ = sparse_cube.size_;
        }
    }

    SparseCube& operator=(const SparseCube& sparse_cube) {
        if (this != &sparse_cube) {
            cube_ = sparse_cube.cube_;
            limits_ = sparse_cube.limits_;
            size_ = sparse_cube.size_;
        }
        return *this;
    }

private:
    std::map<int, std::map<int, std::map<int, std::list<int>>>> cube_;
    Limits limits_;
    int size_ = 0;
};

class ConwayCubes {
public:
    ConwayCubes(const SparseCube& sparse_cube) : sparse_cube_(sparse_cube) {}

    ~ConwayCubes() = default;

    void Cycle(int count = 1) {
        for (int i = 0; i < count; ++i) {
            this->CycleOnce();
        }
    }

    SparseCube& GetSparseCube() {
        return sparse_cube_;
    }

private:
    SparseCube sparse_cube_;

    int CountActiveNeighbors(int x, int y, int z, int w) {
        int count = 0;
        for (int i = (x - 1); i < (x + 2); ++i) {
            for (int j = (y - 1); j < (y + 2); ++j) {
                for (int k = (z - 1); k < (z + 2); ++k) {
                    for (int l = (w - 1); l < (w + 2); ++l) {
                        if ((i == x) && (j == y) && (k == z) && (l == w)) {
                            continue;
                        }
                        if (sparse_cube_.Has(i, j, k, l)) {
                            count++;
                        }
                    }
                }
            }
        }
        return count;
    }

    void CycleOnce() {
        SparseCube::Limits limits = sparse_cube_.GetLimits();
        SparseCube new_cube;
        for (int w = (limits.w_min - 1); w <= (limits.w_max + 1); ++w) {
            for (int z = (limits.z_min - 1); z <= (limits.z_max + 1); ++z) {
                for (int y = (limits.y_min - 1); y <= (limits.y_max + 1); ++y) {
                    for (int x = (limits.x_min - 1); x <= (limits.x_max + 1); ++x) {
                        if (sparse_cube_.Has(x, y, z, w)) {
                            int active_neighbors = CountActiveNeighbors(x, y, z, w);
                            if ((active_neighbors == 2) || (active_neighbors == 3)) {
                                new_cube.Insert(x, y, z, w);
                            }
                        } else {
                            if (CountActiveNeighbors(x, y, z, w) == 3) {
                                new_cube.Insert(x, y, z, w);
                            }
                        }
                    }
                }
            }
        }
        sparse_cube_ = new_cube;
    }
};

int main(int argc, char* argv[]) {
    ifstream input("d17s1.txt");
    if (!input.is_open()) {
        cerr << "Could not open input.txt" << endl;
        return 1;
    }

    SparseCube sparse_cube;
    string line;
    int y = 0;
    while (getline(input, line)) {
        for (int x = 0; x < line.size(); ++x) {
            if (line[x] == '#') {
                sparse_cube.Insert(x, y, 0, 0);
            }
        }
        ++y;
    }

    ConwayCubes conway_cubes(sparse_cube);
    conway_cubes.Cycle(6);

    cout << "Number of cubes in the active state: ";
    cout << conway_cubes.GetSparseCube().GetSize() << endl;
    return 0;
}
