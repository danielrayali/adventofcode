#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

int ProcessLine(const string& line) {
    int letters[26] = { 0 };
    int num_unique_letters = 0;
    for (int i = 0; i < 4; ++i) {
        const int where = line.at(i) - 'a';
        if (letters[where] == 0) {
            num_unique_letters++;
        }
        letters[where]++;
    }
    
    int index = 4;
    while (num_unique_letters < 4) {
        int where = line.at(index - 4) - 'a';
        letters[where]--;
        if (letters[where] == 0) {
            num_unique_letters--;
        }

        where = line.at(index) - 'a';
        if (letters[where] == 0) {
            num_unique_letters++;
        }
        letters[where]++;
        index++;
    }

    return index;
}

int main(int argc, char* argv[]) {
    const string file_path("input.txt");
    ifstream input(file_path);

    if (!input.is_open()) {
        cerr << "Could not open " << file_path << endl;
        return 1;
    }

    string line;
    getline(input, line);
    const int received = ProcessLine(line);
    cout << "Received " << received << endl;

    return 0;
}
