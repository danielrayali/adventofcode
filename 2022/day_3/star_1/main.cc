#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>

using namespace std;

int GetPriority(const string line) {
    // Build sets of characters per line
    const size_t half_index = line.size() / 2;
    set<char> left_chars, right_chars;
    for (size_t i = 0; i < half_index; ++i) {
        left_chars.insert(line[i]);
        right_chars.insert(line[i + half_index]);
    }

    // Calculate the intersection of each set (hopefully STL is efficient!)
    vector<char> intersections;
    set_intersection(left_chars.begin(), left_chars.end(), right_chars.begin(), right_chars.end(), back_inserter(intersections));
    if (intersections.size() != 1) {
        throw runtime_error("Did not detect a single, shared character: " + line);
    }

    // Apply mapping to priority numbers
    if (islower(intersections[0])) {
        return (intersections[0] - 'a' + 1);
    } else {
        return (intersections[0] - 'A' + 27);
    }
}

int main(int argc, char* argv[]) {
    const string file_path("input.txt");
    ifstream input(file_path);

    if (!input.is_open()) {
        cerr << "Could not open " << file_path << endl;
        return 1;
    }

    string line;
    int priority = 0;
    while (getline(input, line)) {
        priority += GetPriority(line);
    }

    cout << "Priority: " << priority << endl;

    return 0;
}
