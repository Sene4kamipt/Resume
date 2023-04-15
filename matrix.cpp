#include<iostream>
#include<string>
#include<vector>

const int64_t BASE = 1000000000;

class BigInteger {
private:
    std::vector<int64_t> number;
    bool sign;
    size_t size;

    friend bool operator<(const BigInteger &first, const BigInteger &second);

public:
    BigInteger();
    BigInteger(const std::string& str);
    BigInteger(const BigInteger& other);
    BigInteger(const int& n);
    ~BigInteger();
    void swap(BigInteger& other);
    BigInteger& operator=(const BigInteger& other);
    BigInteger operator-();
    BigInteger& operator+=(const BigInteger& other);
    BigInteger& operator-=(const BigInteger& other);
    BigInteger& operator/=(const BigInteger& other);
    BigInteger& operator*=(const BigInteger& other);
    BigInteger& operator%=(const BigInteger& other);
    BigInteger& operator++();
    BigInteger operator++(int);
    BigInteger& operator--();
    BigInteger operator--(int);
    std::string toString() const;
    explicit operator bool() const;
    //строгие сравнения по модулю
    bool if_greater_module(const BigInteger& first, const BigInteger& second);
    bool if_smaller_module(const BigInteger& first, const BigInteger& second);
    bool getsign() const{
        return sign;
    }
    bool is_even() const{
        return number[0] % 2 == 0;
    }
    //быстрые деление и умножение на 2
    void div_2();
    void mult_2();
};

bool operator>=(const BigInteger& first, const BigInteger& second);
bool operator>(const BigInteger& first, const BigInteger& second);
bool operator<=(const BigInteger& first, const BigInteger& second);
bool operator==(const BigInteger& first, const BigInteger& second);
bool operator!=(const BigInteger& first, const BigInteger& second);
BigInteger operator+(const BigInteger& first, const BigInteger& second);
BigInteger operator-(const BigInteger& first, const BigInteger& second);
BigInteger operator/(const BigInteger& first, const BigInteger& second);
BigInteger operator*(const BigInteger& first, const BigInteger& second);
BigInteger operator%(const BigInteger& first, const BigInteger& second);
std::ostream& operator<<(std::ostream& out, const BigInteger& current);
std::istream& operator>>(std::istream& in, BigInteger& current);

BigInteger::BigInteger() {
    number = {0};
    size = 1;
    sign = true;
}

BigInteger::BigInteger(const int& n) {
    size = 0;
    number = {};
    int64_t copy = n;
    if (copy >= 0) {
        sign = true;
    } else {
        sign = false;
        copy = -copy;
    }
    do {
        number.push_back(copy % BASE);
        ++size;
        copy /= BASE;
    } while (copy > 0) ;
}

BigInteger::BigInteger(const std::string& str) {
    number = {};
    size = str.size();
    sign = true;
    size_t first_position = 0;
    if (str[0] == '-') {
        sign = false;
        first_position = 1;
        --size;
    }
    size_t remainder = size % 9;
    size /= 9;
    // по 9 цифр добавлять надо
    //size_t current_size = size;
    for (size_t i = 1; i <= size; ++i) { // по целым девяткам
        int64_t current_digit = 0;
        for (int j = 0; j < 9; ++j) {
            current_digit *= 10;
            current_digit += (str[str.length() - 9 * i + j] - '0');
        }
        number.push_back(current_digit);
    }
    if (remainder != 0) {
        int64_t current_digit = 0;
        for (size_t j = 0; j < remainder; ++j) {
            current_digit *= 10;
            current_digit += (str[first_position + j] - '0');
        }
        number.push_back(current_digit);
    }
    size = number.size();
}

BigInteger::BigInteger(const BigInteger& other) {
    number = {};
    for (size_t i = 0; i < other.size; ++i) {
        number.push_back(other.number[i]);
    }
    size = other.size;
    sign = other.sign;
}

BigInteger::~BigInteger() {
    number.clear();
}

void BigInteger::swap(BigInteger& other) {
    std::swap(sign, other.sign);
    std::swap(size, other.size);
    std::swap(number, other.number);
}

BigInteger& BigInteger::operator=(const BigInteger& other) {
    BigInteger copy(other);
    copy.swap(*this);
    return *this;
}

BigInteger BigInteger::operator-() {
    BigInteger copy(*this);
    if (number[size - 1] == 0 ) {
        return copy;
    }
    copy.sign = !copy.sign;
    return copy;
}

BigInteger& BigInteger::operator++() {
    *this += 1;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger copy(*this);
    *this += 1;
    return copy;
}

BigInteger& BigInteger::operator--() {
    *this -= 1;
    return *this;
}
BigInteger BigInteger::operator--(int) {
    BigInteger copy(*this);
    *this -= 1;
    return copy;
}

std::string int_to_string(const int64_t& other, bool with_zeros) {
    int64_t copy = other;
    std::string reversed_answer = {};
    do {
        reversed_answer.push_back(copy % 10 + '0');
        copy /= 10;
    } while (copy > 0);
    std::string answer = {};
    if (with_zeros) {
        while (reversed_answer.size() < 9) {
            reversed_answer.push_back('0');
        }
    }
    for (size_t i = 0; i < reversed_answer.length(); ++i) {
        answer.push_back(reversed_answer[reversed_answer.length() - 1 - i]);
    }
    return answer;
}

std::string BigInteger::toString() const {
    std::string answer = {};
    if (!sign) {
        answer.push_back('-');
    }
    for (size_t i = 0; i < size; ++i) {
        answer+=(int_to_string(number[size - 1 - i], i!=0));
    }
    return answer;
}

BigInteger::operator bool() const {
    return number[size - 1] != 0;
}

bool BigInteger::if_smaller_module(const BigInteger& first, const BigInteger& second) {
    if (first.sign) {
        return first < second;
    } else {
        return second < first;
    }
}

bool BigInteger::if_greater_module(const BigInteger& first, const BigInteger& second) {
    if (first.sign) {
        return first > second;
    } else {
        return second > first;
    }
}

BigInteger& BigInteger::operator+=(const BigInteger& other) {
    //сложение чисел разных знаков это вычитание чисел одного знака
    if (sign != other.sign) {
        sign = !sign;
        *this -= other;
        if (*this) {
            sign = !sign;
        }
        return *this;
    }
    // по сути складываем модули, a sign остается
    size_t cur_position = 0;
    int64_t is_plus = 0;
    int64_t cur_sum = 0;
    while (cur_position < other.size) {
        if (cur_position >= size) {
            number.push_back(0);
            ++size;
        }
        cur_sum = number[cur_position] + other.number[cur_position] + is_plus;
        number[cur_position] = cur_sum % BASE;
        is_plus = cur_sum / BASE;
        ++cur_position;
    }
    while (is_plus != 0) {
        if (cur_position == size) {
            number.push_back(0);
            ++size;
        }
        number[cur_position] += 1;
        is_plus = number[cur_position] / BASE;
        number[cur_position] %= BASE;
        ++cur_position;
    }
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
    // вычитание с разными знаками это сложение
    if (sign != other.sign) {
        sign = !sign;
        *this += other;
        sign = !sign;
        return *this;
    }
    if (if_greater_module(*this, other) || *this == other) {
        // если первое по модулю больше или равно, то вычитаем модули, а знак сохраняется
        size_t cur_position = 0;
        while (cur_position < other.size) {
            if (number[cur_position] >= other.number[cur_position]) {
                number[cur_position] -= other.number[cur_position];
                ++cur_position;
                continue;
            }
            number[cur_position] = BASE + number[cur_position] - other.number[cur_position];
            --number[cur_position + 1];
            ++cur_position;
        }
        while (number[cur_position] == -1) {
            number[cur_position] = BASE - 1;
            --number[cur_position + 1];
            ++cur_position;
        }
        //удаляем ведущие нули
        while (size > 0 && number[size - 1] == 0) {
            number.pop_back();
            --size;
        }
        //если ответ 0, то получилось пустое число
        if (size == 0) {
            number = {0};
            size = 1;
            sign = true;
        }
        return *this;
    }
    // теперь если *this по модулю меньше чем other то вычитаем из модуля other модуль *this
    // и меняем знак
    while (size < other.size) {
        number.push_back(0);
        ++size;
    }
    size_t cur_position = 0;
    while (cur_position < size) {
        if (other.number[cur_position] >= number[cur_position]) {
            number[cur_position] = other.number[cur_position] - number[cur_position];
            ++cur_position;
            continue;
        }
        number[cur_position] = BASE + other.number[cur_position] - number[cur_position];
        ++number[cur_position + 1];
        ++cur_position;
    }
    --cur_position;
    while (size > 0 && number[size - 1] == 0) {
        number.pop_back();
        --size;
    }
    sign = !sign;
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
    if (!*this || !other) {
        number.clear();
        number = {0};
        size = 1;
        sign = true;
        return *this;
    }
    for (size_t i = 0; i < other.size - 1; ++i) {
        number.push_back(0);
    }
    size_t total_size = size + other.size - 1;
    for (size_t i = 0; i < total_size ; ++i) {
        size_t index_sum = total_size - 1 - i; // сумма индексов
        int64_t sum = 0;
        for (size_t j = std::min(index_sum, size - 1); j + other.size > std::max(other.size - 1, index_sum); --j) {
            int64_t cur_sum = number[j] * other.number[index_sum - j];
            if (i == 0) {
                sum += cur_sum;
            } else {
                sum += cur_sum % BASE;
                number[index_sum + 1] += cur_sum / BASE;
            }
        }
        number[index_sum] = sum;
    }
    for (size_t i = 0; i < total_size; ++i) {
        if (number[i]>=BASE && i == total_size - 1) {
            ++total_size;
            number.push_back(0);
        }
        number[i+1] += number[i]/BASE;
        number[i] %= BASE;
    }
    size = total_size;
    sign = (sign == other.sign);
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& other) {
    //деление в столбик
    bool answer_sign = (sign == other.sign);
    //делим модули
    if (!answer_sign) {
        sign = other.sign;
    }
    if (if_smaller_module(*this, other)) {
        number =  {0};
        size = 1;
        sign = true;
        return *this;
    }
    std::vector<int64_t> answer;
    BigInteger cur_number = 0; //текущий остаток
    cur_number.sign = other.sign;
    size_t cur_position = size; //последняя добавленная цифра
    while (cur_position > 0) {// пока не все цифры (блоки) списали
        //если остаток еще меньше other, то дописываем новую цифру
        while (if_smaller_module(cur_number, other) && cur_position > 0) {
            cur_number *= BASE;
            cur_number.sign = other.sign;
            if (cur_number.sign) {
                cur_number += number[cur_position - 1];
            } else {
                cur_number -= number[cur_position - 1];
            }
            --cur_position;
            answer.push_back(0);
        }
        if (cur_position == 0 && if_smaller_module(cur_number, other)) {
            break;
        }
        answer.pop_back(); // один лишний ноль написали
        //новый блок ищем бинпоиском
        cur_number.sign = other.sign;
        int64_t left_border = 1; // включая
        int64_t right_border = BASE; // не включая
        //найти пocледнее число такое что other умножить на него будет меньше или равно cur_number
        while (right_border - left_border > 1) {
            int64_t middle = (left_border + right_border) / 2;
            if (if_greater_module(middle * other, cur_number)) {
                right_border = middle;
            } else {
                left_border = middle;
            }
        }
        //left_border - наш ответ
        answer.push_back(left_border);
        cur_number -= (left_border * other);
        cur_number.sign = other.sign;
    }
    BigInteger result = 0;
    for (size_t i = 0; i < answer.size(); ++i) {
        result *= BASE;
        result += answer[i];
    }
    swap(result);
    sign = answer_sign;
    answer.clear();
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& other) {
    BigInteger copy(*this);
    copy /= other;
    copy *= other;
    *this -= copy;
    return *this;
}

void BigInteger::div_2() {
    int64_t remainder = 0;
    int64_t cur_digit = 0;
    for (size_t i = size; i > 0; --i) {
        cur_digit = number[i - 1] + remainder * BASE;
        number[i - 1] = (cur_digit / 2);
        remainder = (cur_digit % 2);
    }
    while (size > 1 && number[size - 1] == 0) {
        number.pop_back();
        --size;
    }
    if (size == 1 && number[0] == 0) {
        sign = true;
    }
}

void BigInteger::mult_2() {
    int64_t remainder = 0;
    int64_t cur_digit = 0;
    for (size_t i = 0; i < size || remainder; ++i) {
        if (i == size) {
            number.push_back(0);
        }
        cur_digit = remainder + number[i] * 2;
        number[i] = cur_digit % BASE;
        remainder = cur_digit / BASE;
    }
    if (size == 1 && number[0] == 0) {
        sign = true;
    }
}

BigInteger operator+(const BigInteger& first, const BigInteger& second) {
    BigInteger copy = first;
    copy += second;
    return copy;
}

BigInteger operator-(const BigInteger& first, const BigInteger& second) {
    BigInteger copy = first;
    copy -= second;
    return copy;
}

BigInteger operator*(const BigInteger& first, const BigInteger& second) {
    BigInteger copy = first;
    copy *= second;
    return copy;
}

BigInteger operator/(const BigInteger& first, const BigInteger& second) {
    BigInteger copy = first;
    copy /= second;
    return copy;
}

BigInteger operator%(const BigInteger& first, const BigInteger& second) {
    BigInteger copy = first;
    copy %= second;
    return copy;
}

BigInteger gcd(const BigInteger& first_num, const BigInteger& second_num) {
    BigInteger first = first_num;
    BigInteger second = second_num;
    BigInteger answer = 1;
    while (first != 0 && second != 0) {
        bool first_even = first.is_even();
        bool second_even = second.is_even();
        if (first_even && second_even) {
            first.div_2();
            second.div_2();
            answer.mult_2();
            continue;
        }
        if (first_even) {
            first.div_2();
            continue;
        }
        if (second_even) {
            second.div_2();
            continue;
        }
        if (first < second) {
            first.swap(second);
        }
        first -= second;
    }
    if (first == 0) {
        return second * answer;
    } else {
        return first * answer;
    }
}

bool operator<(const BigInteger& first, const BigInteger& second) {
    if (first.sign != second.sign) {
        return first.sign < second.sign;
    }
    if (first.size != second.size) {
        if (first.sign) {
            return first.size < second.size;
        } else {
            return first.size > second.size;
        }
    }
    size_t cur_position = 0;
    while (cur_position < first.size) {
        if (first.number[first.size - 1 - cur_position] !=
            second.number[second.size - 1 - cur_position]) {
            if (first.sign) {
                return first.number[first.size - 1 - cur_position] <
                       second.number[second.size - 1 - cur_position];
            } else {
                return first.number[first.size - 1 - cur_position] >
                       second.number[second.size - 1 - cur_position];
            }
        }
        ++cur_position;
    }
    return false;
}

bool operator>(const BigInteger& first, const BigInteger& second) {
    return second < first;
}
bool operator==(const BigInteger& first, const BigInteger& second ) {
    return (!(first < second)) && (!(second < first));
}
bool operator!=(const BigInteger& first, const BigInteger& second ) {
    return !(first == second);
}
bool operator>=(const BigInteger& first, const BigInteger& second ) {
    return !(first < second);
}
bool operator<=(const BigInteger& first, const BigInteger& second ) {
    return !(first > second);
}

std::ostream& operator<<(std::ostream& out, const BigInteger& current) {
    std::string str = current.toString();
    out << str;
    return out;
}

std::istream& operator>>(std::istream& in, BigInteger& current) {
    std::string str;
    in >> str;
    BigInteger copy(str);
    current.swap(copy);
    return in;
}

class Rational{
private:
    BigInteger nominator = 0; // целое
    BigInteger denominator = 1; // натуральное
    friend bool operator< (const Rational& first, const Rational& second);

public:
    Rational();
    Rational(const int& a, const int& b);
    Rational(const BigInteger& a, const BigInteger& b);
    Rational(const int& n);
    Rational(const BigInteger& other);
    Rational(const Rational& other);
    Rational(const std::string& str);
    void make_simple(); // приводит к несократимому виду
    Rational& operator+=(const Rational& other);
    Rational& operator-=(const Rational& other);
    Rational& operator*=(const Rational& other);
    Rational& operator/=(const Rational& other);
    Rational& operator-();
    std::string asDecimal(size_t precision = 0);
    explicit operator double();
    std::string toString() const;
    void swap(Rational& other) {
        std::swap(nominator, other.nominator);
        std::swap(denominator, other.denominator);
    }
};

Rational operator+(const Rational& first, const Rational& second);
Rational operator-(const Rational& first, const Rational& second);
Rational operator*(const Rational& first, const Rational& second);
Rational operator/(const Rational& first, const Rational& second);
bool operator<(const Rational& first, const Rational& second);
bool operator==(const Rational& first, const Rational& second);
bool operator<=(const Rational& first, const Rational& second);
bool operator>(const Rational& first, const Rational& second);
bool operator!=(const Rational& first, const Rational& second);
bool operator>=(const Rational& first, const Rational& second);

Rational::Rational() {
    nominator = 0;
    denominator = 1;
}

Rational::Rational(const int& a, const int& b) {
    nominator = a;
    denominator = b;
    make_simple();
}

Rational::Rational(const BigInteger& a, const BigInteger& b) {
    nominator = a;
    denominator = b;
    make_simple();
}

Rational::Rational(const int& n) {
    nominator = n;
    denominator = 1;
}

Rational::Rational(const BigInteger& bigint) {
    nominator = bigint;
    denominator = 1;
}

Rational::Rational(const Rational& other) {
    nominator = other.nominator;
    denominator = other.denominator;
}

Rational::Rational(const std::string& str) {
    std::string integer_part;
    std::string decimal_part;
    size_t pos = 0;
    BigInteger size = 1;
    while(pos != str.size() && str[pos] != '.') {
        integer_part.push_back(str[pos]);
        ++pos;
    }
    ++pos;
    while(pos < str.size()) {
        decimal_part.push_back(str[pos]);
        size *= 10;
        ++pos;
    }
    BigInteger first(integer_part);
    BigInteger second;
    Rational answer;
    if(decimal_part.empty()) {
        nominator = first;
        denominator = 1;
        return;
    }
    second = BigInteger(decimal_part);
    nominator = first * size + second;
    denominator = size;
    make_simple();
}

void Rational::make_simple() {
    if (nominator == 0) {
        denominator = 1;
        return;
    }
    bool answer_sign = (nominator.getsign() == denominator.getsign());
    if (nominator < 0) {
        nominator = -nominator;
    }
    if (denominator < 0) {
        denominator = -denominator;
    }
    BigInteger GCD = gcd(nominator,denominator);
    nominator /= GCD;
    denominator /= GCD;
    if (!answer_sign) {
        nominator = -nominator;
    }
}

Rational& Rational::operator+=(const Rational& other) {
    nominator = nominator * other.denominator + denominator * other.nominator;
    denominator *= other.denominator;
    make_simple();
    return *this;
}

Rational& Rational::operator-=(const Rational& other) {
    nominator = nominator * other.denominator - denominator * other.nominator;
    denominator *= other.denominator;
    make_simple();
    return *this;
}

Rational& Rational::operator*=(const Rational& other) {
    nominator *= other.nominator;
    denominator *= other.denominator;
    make_simple();
    return *this;
}

Rational& Rational::operator/=(const Rational& other) {
    nominator *= other.denominator;
    denominator *= other.nominator;
    make_simple();
    return *this;
}

Rational& Rational::operator-() {
    nominator = -nominator;
    return *this;
}

std::string Rational::asDecimal(size_t precision) {
    BigInteger nom_copy (nominator);
    //nom_copy.make_positive();
    if (nom_copy < 0) {
        nom_copy = -nom_copy;
    }
    std::string integer_part = (nom_copy / denominator).toString();
    std::string dec = "1";
    for (size_t i = 0; i < precision; ++i) {
        dec.push_back('0');
    }
    BigInteger to_mult(dec);
    nom_copy *= to_mult; // умножаем на 10^precision
    nom_copy /= denominator;
    std::string quotient = nom_copy.toString();
    std::string fractional_part = "";
    for (size_t i = quotient.size(); i < quotient.size() + precision; ++i) {
        if (i < precision) {
            fractional_part.push_back('0');
        } else {
            fractional_part.push_back(quotient[i - precision]);
        }
    }
    if (precision != 0) {
        fractional_part = "." + fractional_part;
    }
    if (!nominator.getsign()) {
        integer_part= "-" + integer_part;
    }
    std::string answer = integer_part + fractional_part;
    return answer;
}

Rational::operator double() {
    make_simple();
    std::string answer = asDecimal(20);
    return std::stod(&answer[0]);
}

std::string Rational::toString() const{
    if (denominator == 1) {
        return nominator.toString();
    }
    return nominator.toString() + "/" + denominator.toString();
}

Rational operator+(const Rational& first, const Rational& second) {
    Rational copy(first);
    copy += second;
    return copy;
}

Rational operator-(const Rational& first, const Rational& second) {
    Rational copy(first);
    copy -= second;
    return copy;
}

Rational operator*(const Rational& first, const Rational& second) {
    Rational copy(first);
    copy *= second;
    return copy;
}

Rational operator/(const Rational& first, const Rational& second) {
    Rational copy(first);
    copy /= second;
    return copy;
}

bool operator<(const Rational& first, const Rational& second) {
    return first.nominator * second.denominator < first.denominator * second.nominator;
}
bool operator==(const Rational& first, const Rational& second) {
    return !(first < second || second < first);
}
bool operator<=(const Rational& first, const Rational& second) {
    return first < second || first == second;
}
bool operator>(const Rational& first, const Rational& second) {
    return !(first <= second);
}
bool operator!=(const Rational& first, const Rational& second) {
    return !(first == second);
}
bool operator>=(const Rational& first, const Rational& second) {
    return !(first < second);
}

std::ostream& operator<<(std::ostream& out, const Rational& n) {
    std::string str = n.toString();
    out<<str;
    return out;
}

std::istream& operator>> (std::istream& in, Rational& n) {
    std::string str;
    in>>str;
    Rational copy(str);
    n.swap(copy);
    return in;
}


template<size_t N, size_t K>
struct is_prime_helper{
    static const bool value = (N < K * K) || ((N % K != 0) && (is_prime_helper<N, K + 1>::value));
};
template<size_t N>
struct is_prime_helper<N, N>{
    static const bool value = true;
};
template<size_t N>
struct is_prime_helper<N, 1>{
    static const bool value = true;
};

template<size_t N>
struct is_prime{
    static const bool value = is_prime_helper<N, 2>::value;
};

size_t fast_power(size_t number, size_t power, size_t modulo) {
    if(power == 0) {
        return 1;
    }
    if(power % 2 == 0) {
        return fast_power(number, power/2, modulo) * fast_power(number, power/2, modulo) % modulo;
    }
    return number * fast_power(number, power/2, modulo) * fast_power(number, power/2, modulo) % modulo;
}




template<size_t N>
class Residue{
private:
    size_t value;
public:
    Residue(const int& number) {
        size_t copy;
        if (number >= 0) {
            copy = static_cast<int>(number);
            value = copy % N;
        } else {
            copy = static_cast<int>(-number);
            value = N - copy % N;
        }
    }

    Residue() {
        value = 0;
    }

    explicit operator int() const {
        return static_cast<int>(value);
    }

    size_t get_value() const {
        return value;
    }

    Residue& operator+=(const Residue& other) {
        value += other.value;
        value %= N;
        return *this;
    }

    Residue& operator-=(const Residue& other) {
        if(value < other.value) {
            value += N;
        }
        value -= other.value;
        return *this;
    }

    Residue& operator*=(const Residue& other) {
        value *= other.value;
        value %= N;
        return *this;
    }

    Residue& operator/=(const Residue& other) {
        static_assert(is_prime<N>::value, "prime modulo division only");
        value = value * fast_power(other.value, N - 2, N);
        value %= N;
        return *this;
    }
};

template<size_t N>
Residue<N> operator+(const Residue<N>& first, const Residue<N>& second) {
    Residue<N> copy = first;
    copy += second;
    return copy;
}

template<size_t N>
std::ostream& operator<< (std::ostream& out, const Residue<N>& number) {
    out << number.get_value();
    return out;
}

template<size_t N>
Residue<N> operator-(const Residue<N>& first, const Residue<N>& second) {
    Residue<N> copy = first;
    copy -= second;
    return copy;
}

template<size_t N>
Residue<N> operator*(const Residue<N>& first, const Residue<N>& second) {
    Residue<N> copy = first;
    copy *= second;
    return copy;
}

template<size_t N>
Residue<N> operator/(const Residue<N>& first, const Residue<N>& second) {
    Residue<N> copy = first;
    copy /= second;
    return copy;
}

template<size_t N>
bool operator==(const Residue<N>& first, const Residue<N>& second) {
    if(first.get_value() == second.get_value()) {
        return true;
    }
    return false;
}

template<size_t N>
bool operator!=(const Residue<N>& first, const Residue<N>& second) {
    return !(first == second);
}




template<size_t M, size_t N, typename Field = Rational>
class Matrix{
private:
    std::vector<std::vector<Field>> matrix;
public:
    Matrix(const std::initializer_list<const std::initializer_list<Field>>& table) {
        std::vector<Field> row;
        matrix = {};
        for (const auto& first : table) {
            for (const auto& second : first) {
                row.push_back(Field(second));
            }
            matrix.push_back(row);
            row.clear();
        }
    }
    Matrix() {
        std::vector<Field> row;
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                row.push_back(Field(0));
            }
            matrix.push_back(row);
            row.clear();
        }
        if (N == M) {
            for (size_t i = 0; i < N; ++i) {
                matrix[i][i] = 1;
            }
        }
    }

    Matrix(const Matrix<M, N, Field>& n) {
        matrix = n.matrix;
    }

    void swap (Matrix<M, N, Field>& other) {
        matrix.swap(other.matrix);
    }

    Matrix<M, N, Field>& operator=(const Matrix<M, N, Field>& n) {
        Matrix copy(n);
        copy.swap(*this);
        return *this;
    }

    Matrix<M, N, Field>& operator+=(const Matrix<M,N,Field>& other) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                matrix[i][j] += other.matrix[i][j];
            }
        }
        return *this;
    }

    Matrix<M, N, Field>& operator-=(const Matrix<M, N, Field>& other) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                matrix[i][j] -= other.matrix[i][j];
            }
        }
        return *this;
    }

    Matrix<M, N, Field>& operator*=(const Field& number) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                matrix[i][j]*=number;
            }
        }
        return *this;
    }

    Matrix<M, N, Field>& operator*=(const Matrix<M, N, Field>& other) {
        static_assert(M == N);
        *this = *this * other;
        return *this;
    }

    const std::vector<Field>& operator[](size_t index) const {
        return matrix[index];
    }
    std::vector<Field>& operator[](size_t index) {
        return matrix[index];
    }

    Matrix<N, M, Field> transposed() const{
        Matrix<N, M, Field> answer;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                answer[i][j] = matrix[j][i];
            }
        }
        return answer;
    }

    Field trace() const {
        Field answer = Field(0);
        for(size_t i = 0; i < std::min(M, N); ++i) {
            answer += matrix[i][i];
        }
        return answer;
    }

    std::pair<bool, size_t> to_normal() { //приводит матрицу к нормальному виду
        bool swap_sign_needed = false;
        size_t number_of_steps = 0;
        std::pair<size_t, size_t> position = std::make_pair(0,0);
        while(position.first < M && position.second < N) {
            if(matrix[position.first][position.second] == Field(0)) {
                for (size_t j = position.first + 1; j < M; ++j) {
                    if (matrix[j][position.second] != Field(0)) {
                        std::swap(matrix[position.first], matrix[j]);
                        if((position.first - j) % 2 != 0) {
                            swap_sign_needed = !swap_sign_needed;
                        }
                        break;
                    }
                }
                if (matrix[position.first][position.second] == Field(0)) {
                    ++position.second;
                    continue;
                }
            }
            ++number_of_steps;
            Field delta;
            for(size_t j = position.first + 1; j < M; ++j) {
                if(matrix[j][position.second] == Field(0)) {
                    continue;
                }
                delta = matrix[j][position.second] / matrix[position.first][position.second];
                for (size_t k = 0; k < N; ++k) {
                    matrix[j][k] -= matrix[position.first][k] * delta;
                }
            }
            for(size_t j = 0; j < position.first; ++j) {
                if(matrix[j][position.second] == Field(0)) {
                    continue;
                }
                delta = matrix[j][position.second] / matrix[position.first][position.second];
                for (size_t k = 0; k < N; ++k) {
                    matrix[j][k] -= matrix[position.first][k] * delta;
                }
            }
            ++position.first;
            ++position.second;
        }
        return std::make_pair(swap_sign_needed, number_of_steps);
    }

    Field det() const {
        static_assert(N == M);
        Matrix<M, N, Field> copy = *this;
        std::pair<bool, size_t> answer = copy.to_normal();
        Field mult = Field(1);
        for (size_t i = 0; i < N; ++i) {
            mult *= copy[i][i];
        }
        if (answer.first) {
            mult *= Field(-1);
        }
        return mult;
    }

    size_t rank() const {
        Matrix<M,N,Field> copy = *this;
        std::pair<bool, size_t> answer = copy.to_normal();
        return answer.second;
    }

    Matrix<M, N, Field> inverted() const {
        static_assert(N == M);
        Matrix<N, 2 * N ,Field> copy;
        for (size_t i = 0; i < N; ++i) {
            for(size_t j = 0; j < N; ++j) {
                copy[i][j] = matrix[i][j];
                copy[i][N + j] = 0;
            }
        }
        for (size_t i = 0; i < N; ++i) {
            copy[i][N + i] = 1;
        }
        copy.to_normal();
        Field koef;
        for(size_t i = 0; i < N; ++i) {
            koef = copy[i][i];
            for (size_t j = 0 ; j < 2 * N; ++j) {
                copy[i][j] /= koef;
            }
        }
        Matrix<M, N, Field> result;
        for (size_t i = 0; i < N; ++i) {
            for(size_t j = 0; j < N; ++j) {
                result[i][j] = copy[i][N + j];
            }
        }
        return result;
    }

    void invert() {
        Matrix<M,N,Field> copy = *this;
        *this = copy.inverted();
    }

    std::vector<Field> getRow(size_t number) const {
        return matrix[number];
    }

    std::vector<Field> getColumn(size_t number) const {
        std::vector<Field> answer (M);
        for (size_t i = 0; i < M; ++i) {
            answer[i] = matrix[i][number];
        }
        return answer;
    }
};

template<size_t M, size_t N, typename Field>
bool operator==(const Matrix<M,N,Field>& first, const Matrix<M,N,Field>& second) {
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (first[i][j] != second[i][j]) {
                return false;
            }
        }
    }
    return true;
}

template<size_t M, size_t N, typename Field>
bool operator!=(const Matrix<M,N,Field>& first, const Matrix<M,N,Field>& second) {
    return !(first == second);
}

template<size_t M, size_t N, size_t K, typename Field>
Matrix<M, K, Field> operator*(const Matrix<M, N, Field>& first, const Matrix<N,K,Field>& second) {
    Matrix<M, K, Field> answer;
    Field sum = Field(0);
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < K; ++j) {
            sum = Field(0);
            for (size_t r = 0; r < N; ++r) {
                sum += first[i][r] * second[r][j];
            }
            answer[i][j] = sum;
        }
    }
    return answer;
}

template<size_t M, size_t N, typename Field>
Matrix<M, N, Field> operator+(const Matrix<M, N, Field>& first, const Matrix<M, N, Field>& second) {
    Matrix<M, N, Field> copy = first;
    copy += second;
    return copy;
}

template<size_t M, size_t N, typename Field>
Matrix<M, N, Field> operator-(const Matrix<M, N, Field>& first, const Matrix<M, N, Field>& second) {
    Matrix<M, N, Field> copy = first;
    copy -= second;
    return copy;
}

template<size_t M, size_t N, typename Field>
Matrix<M, N, Field> operator*(const Matrix<M, N, Field>& current, const Field& number) {
    Matrix<M, N, Field> copy = current;
    copy *= number;
    return copy;
}

template<size_t M, size_t N, typename Field>
Matrix<M, N, Field> operator*(const Field& number, const Matrix<M, N, Field>& current) {
    Matrix<M, N, Field> copy = current;
    copy *= number;
    return copy;
}

template<size_t N, typename Field = Rational>
class SquareMatrix : public Matrix<N, N, Field> {
public:
    SquareMatrix<N, Field>() : Matrix<N, N, Field>() {};
    SquareMatrix<N, Field>(const std::initializer_list<const std::initializer_list<Field>>& table) :
            Matrix<N, N, Field>(table) {};
};
