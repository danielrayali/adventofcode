#pragma once

#include <string>
#include <vector>
#include <sstream>

#include <iostream>
using namespace std;

class BigInt {
public:
    BigInt() = default;

    BigInt(const int input) {
        this->Parse(input);
    }

    ~BigInt() = default;

    bool operator==(const BigInt& rhs) {
        if (digits_.size() != rhs.digits_.size()) {
            return false;
        }

        for (size_t i = 0; i < digits_.size(); ++i) {
            if (digits_[i] != rhs.digits_[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const BigInt& rhs) {
        return !(*this == rhs);
    }

    void Parse(const int input) {
        digits_.clear();
        std::string input_str = std::to_string(input);
        for (auto iter = input_str.rbegin(); iter != input_str.rend(); iter++) {
            digits_.push_back(*iter - '0');
        }
    }

    void Add(const BigInt& rhs) {
        int remainder = 0;
        for (int i = 0; i < rhs.digits_.size(); i++) {
            if (digits_.size() == i) {
                digits_.push_back(0);
            }
            const int sum = digits_[i] + rhs.digits_[i] + remainder;
            digits_[i] = GetLowerDigit(sum);
            remainder = (sum >= 10) ? 1 : 0;
        }
        if (remainder == 1) {
            digits_.push_back(1);
        }
    }

    void Multiply(const BigInt& rhs) {
        std::vector<BigInt> products;
        unsigned long long outter_factor = 1;
        for (int i = 0; i < rhs.digits_.size(); ++i) {
            unsigned long long inner_factor = 1;
            for (int j = 0; j < digits_.size(); ++j) {
                products.emplace_back(digits_.at(j) * rhs.digits_.at(i) * inner_factor * outter_factor);
                inner_factor *= 10;
            }
            outter_factor *= 10;
        }

        BigInt result;
        for (const auto& iter : products) {
            result.Add(iter);
        }

        digits_ = std::move(result.digits_);
    }

    std::string ToString() const {
        std::stringstream stream;
        for (auto iter = digits_.rbegin(); iter != digits_.rend(); iter++) {
            stream << *iter;
        }
        return stream.str();
    }

private:
    std::vector<long long> digits_;

    static long long GetLowerDigit(const long long number) {
        return (number % 10);
    }
};
