#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream in("d3s1.txt");
    string line;
    constexpr size_t width = 12;
    vector<int> counts(width, 0);
    while (getline(in, line)) {
        cout << line << endl;
        for (int i = 0; i < width; ++i) {
            if (line[i] == '0') {
                counts[i]--;
            } else if (line[i] == '1') {
                counts[i]++;
            }
        }
    }

    cout << "counts ";
    for (auto count : counts) {
        cout << count << " ";
    }
    cout << endl;

    bitset<width> gamma;
    for (int i = 0; i < width; ++i) {
        if (counts[i] > 0) {
            gamma[width - i - 1] = 1;
        } else if (counts[i] < 0) {
            gamma[width - i - 1] = 0;
        }
    }

    cout << "gamma " << gamma.to_ulong() << endl;

    bitset<width> epsilon = gamma;
    epsilon.flip();

    cout << "epsilon " << epsilon.to_ulong() << endl;

    cout << "combined " << gamma.to_ulong() * epsilon.to_ulong() << endl;

    return 0;
}
