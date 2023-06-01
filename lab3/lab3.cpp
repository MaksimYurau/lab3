#include <iostream>
#include <string>
#include <stdexcept>

class LongInteger {
private:
    long long high;
    long long low;

public:
    LongInteger() : high(0), low(0) {}

    LongInteger(long long h, long long l) : high(h), low(l) {}

    LongInteger(const std::string& numberString) {
        try {
            if (numberString.length() > 9) {
                high = std::stoll(numberString.substr(0, numberString.length() - 9));
                low = std::stoll(numberString.substr(numberString.length() - 9));
            }
            else {
                high = 0;
                low = std::stoll(numberString);
            }
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
            high = 0;
            low = 0;
        }
    }

    bool operator > (const LongInteger& other) const {
        return (high > other.high) || (high == other.high && low > other.low);
    }

    bool operator < (const LongInteger& other) const {
        return (high < other.high) || (high == other.high && low < other.low);
    }

    bool operator >= (const LongInteger& other) const {
        return (*this > other) || (*this == other);
    }

    bool operator <= (const LongInteger& other) const {
        return (*this < other) || (*this == other);
    }

    bool operator == (const LongInteger& other) const {
        return high == other.high && low == other.low;
    }

    LongInteger operator + (const LongInteger& other) const {
        LongInteger result;
        result.low = low + other.low;
        result.high = high + other.high + (result.low / 1000000000);
        result.low %= 1000000000;
        return result;
    }

    LongInteger operator - (const LongInteger& other) const {
        LongInteger result;
        result.low = low - other.low;
        if (low < other.low)
            result.high = high - other.high - 1;
        else
            result.high = high - other.high;
        if (result.low < 0) {
            result.low += 1000000000;
            result.high--;
        }
        return result;
    }

    LongInteger operator * (const LongInteger& other) const {
        LongInteger result;
        result.high = high * other.high;
        result.low = low * other.low;
        result.high += low * other.high + high * other.low;
        result.high += result.low / 1000000000;
        result.low %= 1000000000;
        return result;
    }

    LongInteger operator / (const LongInteger& other) const {
        if (other == LongInteger())
            throw std::runtime_error("Деление на нуль");

        LongInteger result;
        LongInteger remainder = *this;
        LongInteger divisor = other;

        if (divisor > remainder)
            return LongInteger();

        LongInteger quotient;

        while (remainder >= divisor) {
            LongInteger tempDivisor = divisor;
            LongInteger tempQuotient(1, 0);

            while (tempDivisor * LongInteger(10, 0) <= remainder) {
                tempDivisor = tempDivisor * LongInteger(10, 0);
                tempQuotient = tempQuotient * LongInteger(10, 0);
            }

            while (tempDivisor <= remainder) {
                remainder = remainder - tempDivisor;
                quotient = quotient + tempQuotient;
            }
        }

        return quotient;
    }

    std::string toString() const {
        std::string result;
        if (high != 0)
            result = std::to_string(high);
        result += std::to_string(low);
        return result;
    }

    friend std::istream& operator >> (std::istream& is, LongInteger& number);
    friend std::ostream& operator << (std::ostream& os, const LongInteger& number);
};

std::istream& operator >> (std::istream& is, LongInteger& number) {
    std::string input;
    is >> input;
    number = LongInteger(input);
    return is;
}

std::ostream& operator << (std::ostream& os, const LongInteger& number) {
    os << number.toString();
    return os;
}

int main() {
    
}