#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream in("d3s1.txt");
    string line;
    constexpr size_t width = 5;
    vector<int> counts(width, 0);
    vector<string> input;
    while (getline(in, line)) {
        cout << line << endl;
        input.push_back(line);
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

    // TODO(dali) Must determine most common bit _per round_
    vector<string> oxygen_rating = input;
    for (int digit_count = 0; digit_count < width; ++digit_count) {
        for (auto iter = oxygen_rating.begin(); iter != oxygen_rating.end();) {
            if ((counts[digit_count] >= 0) && ((*iter)[digit_count] == '0')) {
                cout << "Removing " << *iter << endl;
                iter = oxygen_rating.erase(iter);
                continue;
            }
            if ((counts[digit_count] < 0) && ((*iter)[digit_count] == '1')) {
                cout << "Removing " << *iter << endl;
                iter = oxygen_rating.erase(iter);
                continue;
            }
            ++iter;
            if (oxygen_rating.size() == 1) {
                break;
            }
        }

        if (oxygen_rating.size() == 1) {
            break;
        }
    }

    if (oxygen_rating.size() != 1) {
        cerr << "Did not get a single oxygen rating" << endl;
        return 1;
    }

    cout << "oxygen rating " << *oxygen_rating.begin() << " (" << bitset<5>(*oxygen_rating.begin()).to_ulong() << ")" << endl;

    vector<string> co2_rating = input;
    for (auto iter = co2_rating.begin(); iter != co2_rating.end(); ++iter) {
        int digit_count = 0;
        for (auto digit : *iter) {
            if ((counts[digit_count] < 0) && (digit == '0')) {
                iter = co2_rating.erase(iter);
                iter--;
                break;
            }
            if ((counts[digit_count] >= 0) && (digit == '1')) {
                iter = co2_rating.erase(iter);
                iter--;
                break;
            }
            digit_count++;
        }

        if (co2_rating.size() == 1) {
            break;
        }
    }

    if (co2_rating.size() != 1) {
        cerr << "Did not get a single oxygen rating" << endl;
        return 1;
    }

    cout << "co2 rating " << *co2_rating.begin() << " (" << bitset<5>(*co2_rating.begin()).to_ulong() << ")" << endl;

    cout << "combined " << bitset<5>(*oxygen_rating.begin()).to_ulong() * bitset<5>(*co2_rating.begin()).to_ulong() << endl;

    return 0;
}
