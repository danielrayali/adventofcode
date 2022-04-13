#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void Cycle(vector<long long>& values) {
    long long temp_count = values[0];
    for (int i = 0; i < 9; ++i) {
        values[i] = values[i + 1];
    }
    values[8] = temp_count;
    values[6] += temp_count;
}

int main(int argc, char* argv[]) {
    ifstream input("d6s1.txt");
    int value = 0;
    vector<long long> values(9, 0);
    while (!input.eof()) {
        input >> value;
        char temp[2];
        input.read(temp, 1);
        cout << "Value: " << value << endl;
        values[value]++;
    }

    for (int i = 0; i < 256; ++i) {
        Cycle(values);
    }

    long long count = 0;
    for (auto value : values) {
        count += value;
    }
    cout << "Count: " << count << endl;
    return 0;
}
