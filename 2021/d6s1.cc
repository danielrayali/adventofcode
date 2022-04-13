#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void Cycle(vector<int>& values) {
    vector<int> new_values(values);
    for (int i = 0; i < values.size(); i++) {
        if (values[i] == 0) {
            new_values[i] = 6;
            new_values.push_back(8);
        } else {
            new_values[i] = values[i] - 1;
        }
    }
    values = new_values;
}

int main(int argc, char* argv[]) {
    ifstream input("d6s1.txt");
    int value = 0;
    vector<int> values;
    while (!input.eof()) {
        input >> value;
        char temp[2];
        input.read(temp, 1);
        cout << "Value: " << value << endl;
        values.emplace_back(value);
    }

    for (int i = 0; i < 80; ++i) {
        Cycle(values);
    }

    cout << "Count: " << values.size() << endl;
    return 0;
}
