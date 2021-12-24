#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream in("d3s1.txt");
    string line;
    constexpr size_t width = 12;
    vector<string> input;
    while (getline(in, line)) {
        cout << line << endl;
        input.push_back(line);
    }

    vector<string> oxygen_inputs = input;
    for (int i = 0; i < width; ++i) {
        int count = 0;
        for (auto iter : oxygen_inputs) {
            if (iter[i] == '0') {
                count--;
            } else {
                count++;
            }
        }
        auto iter = oxygen_inputs.begin();
        while (iter != oxygen_inputs.end()) {
            if ((count < 0) && ((*iter)[i] == '1')) {
                iter = oxygen_inputs.erase(iter);
            } else if ((count >= 0) && ((*iter)[i] == '0')) {
                iter = oxygen_inputs.erase(iter);
            } else {
                iter++;
            }
            if (oxygen_inputs.size() == 1) {
                break;
            }
        }
        if (oxygen_inputs.size() == 1) {
            break;
        }
    }

    if (oxygen_inputs.size() != 1) {
        cerr << "Did not find only one oxygen generator rating value" << endl;
        return 1;
    }

    cout << "oxygen generator rating: " << *oxygen_inputs.begin() << endl;

    vector<string> co2_inputs = input;
    for (int i = 0; i < width; ++i) {
        int count = 0;
        for (auto iter : co2_inputs) {
            if (iter[i] == '0') {
                count--;
            } else {
                count++;
            }
        }
        auto iter = co2_inputs.begin();
        while (iter != co2_inputs.end()) {
            if ((count >= 0) && ((*iter)[i] == '1')) {
                iter = co2_inputs.erase(iter);
            } else if ((count < 0) && ((*iter)[i] == '0')) {
                iter = co2_inputs.erase(iter);
            } else {
                iter++;
            }
            if (co2_inputs.size() == 1) {
                break;
            }
        }
        if (co2_inputs.size() == 1) {
            break;
        }
    }

    if (co2_inputs.size() != 1) {
        cerr << "Did not find only one co2 scrubber rating value" << endl;
        return 1;
    }

    cout << "co2 scrubber rating: " << *co2_inputs.begin() << endl;

    cout << "combined: " << bitset<width>(*oxygen_inputs.begin()).to_ulong() *
                            bitset<width>(*co2_inputs.begin()).to_ulong() << endl;

    return 0;
}
