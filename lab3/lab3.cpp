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
};

int main() {
    
}