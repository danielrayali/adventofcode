#include "big_int.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    BigInt left(9999);
    BigInt right(9999);

    left.Add(right);

    BigInt sum(9999 + 9999);
    if (sum != left) {
        cerr << "Addition error" << endl;
        return 1;
    }

    left.Parse(9999);
    right.Parse(9999);
    cout << "left: " << left.ToString() << endl;
    cout << "right: " << right.ToString() << endl;

    BigInt product(9999 * 9999);
    left.Multiply(right);
    cout << "product: " << left.ToString() << endl;
    if (product != left) {
        cerr << "Multiply error" << endl;
        return 1;
    }

    int number = 1123123250;
    left.Parse(number);
    
    cout << number << " is divisible by 5: " << left.IsDivisibleBy(5) << endl;
    cout << number << " is divisible by 2: " << left.IsDivisibleBy(2) << endl;
    cout << number << " is divisible by 3: " << left.IsDivisibleBy(3) << endl;

    return 0;
}
