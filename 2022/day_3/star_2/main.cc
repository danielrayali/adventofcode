#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <sstream>

using namespace std;

int GetPriority(const string lines[3]) {
    // Reduce repeated letters into a single instance
    set<char> letters[3];
    for (int i = 0; i < 3; i++) {
        for (auto letter : lines[i]) {
            letters[i].insert(letter);
        }
    }

    // Add all appearances of letters across each set, use the only one that will appear 3 times
    map<char, int> counts;
    char common_letter = 'a';
    for (int i = 0; i < 3; i++) {
        for (auto letter : letters[i]) {
            counts[letter]++;
            if (counts[letter] == 3) {
                common_letter = letter;
                break;
            }
        }
    }

    // Map the letter to priority numbers
    if (islower(common_letter)) {
        return (common_letter - 'a' + 1);
    } else {
        return (common_letter - 'A' + 27);
    }
}

int main(int argc, char* argv[]) {
    const string file_path("input.txt");
    ifstream input(file_path);

    if (!input.is_open()) {
        cerr << "Could not open " << file_path << endl;
        return 1;
    }

    string lines[3];
    int priority = 0;
    while (getline(input, lines[0])) {
        getline(input, lines[1]);
        getline(input, lines[2]);
        priority += GetPriority(lines);
    }

    cout << "Priority: " << priority << endl;

    return 0;
}
