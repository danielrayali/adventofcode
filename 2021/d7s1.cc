#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

using namespace std;

class CsvFileReader {
public:
    CsvFileReader(const string& path) : input_(path) {}

    int GetNextValue() {
        stringstream temp;
        input_.get(*temp.rdbuf(), ',');
        input_.get();
        return atoi(temp.str().c_str());
    }

    bool HasMore() const {
        return !input_.eof();
    }

private:
    ifstream input_;
};

int main(int argc, char* argv[]) {
    CsvFileReader reader("d7s1.txt");
    vector<int> values;
    int max = numeric_limits<int>::lowest();
    int min = numeric_limits<int>::max();
    while (reader.HasMore()) {
        int value = reader.GetNextValue();
        if (value > max) {
            max = value;
        }
        if (value < min) {
            min = value;
        }
        values.emplace_back(value);
    }

    vector<int> distances((max - min) + 1, 0);
    for (auto value : values) {
        for (size_t i = 0; i < distances.size(); ++i) {
            if (((value - i) > min) && ((value - i) < max)) {
                distances[value - i]++;
            }
        }
    }

    for (int i = 0; i < distances.size(); ++i) {
        cout << distances[i] << endl;
    }
    return 0;
}
