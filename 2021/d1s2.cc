#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream in("d1s1.txt");
    string line;
    vector<int> data;
    while (getline(in, line)) {
        data.push_back(atoi(line.c_str()));
    }

    int prev_idx = 0;
    int increases = 0;
    for (int i = 3; i < data.size(); ++i) {
        int left_sum = data.at(prev_idx) + data.at(prev_idx + 1) + data.at(prev_idx + 2);
        int right_sum = data.at(i - 2) + data.at(i - 1) + data.at(i);
        if (right_sum > left_sum) {
            increases++;
        }
        prev_idx++;
    }

    cout << "Number of increases: " << increases << endl;
    return 0;
}
