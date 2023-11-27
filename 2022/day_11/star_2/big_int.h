#pragma once

#include <string>
#include <vector>
#include <sstream>

#include <iostream>
using namespace std;

class BigInt {
public:
    BigInt() = default;

    BigInt(const BigInt& lhs) {
        digits_ = lhs.digits_;
    }

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
        int factor = 0;
        for (int i = 0; i < rhs.digits_.size(); ++i) {
            products.push_back({});
            for (int k = 0; k < factor; ++k) {
                products.back().digits_.push_back(0);
            }

            int remainder = 0;
            for (int j = 0; j < digits_.size(); ++j) {
                const int sum = rhs.digits_.at(i) * digits_.at(j) + remainder;
                products.back().digits_.push_back(GetLowerDigit(sum));
                remainder = (sum > 9) ? (sum / 10) : 0;
            }

            if (remainder != 0) {
                products.back().digits_.push_back(remainder);
            }

            factor++;
        }

        BigInt result;
        for (const auto& iter : products) {
            result.Add(iter);
        }

        digits_ = std::move(result.digits_);
    }

    bool IsDivisibleBy(const int number) {
        if (number == 2) {
            return !(digits_[0] & 0x1);
        }
        if (number == 5) {
            return (digits_[0] == 0 || digits_[0] == 5);
        }

        BigInt parsed(number);
        return false;
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
