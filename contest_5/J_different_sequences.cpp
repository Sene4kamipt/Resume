#include <vector>
#include <iostream>
#include<cmath>
int main()
{
    long long n;
    std::vector <long long> values;
    std::vector <long long> last_in(1000001, -1);
    std::vector<long long> diff_seq = { 0 };
    long long value;
    std::cin >> n;
    if (n == 0) {
        std::cout << "0";
        return 0;
    }
    for (long long i = 0; i < n; ++i) {
        std::cin >> value;
        values.push_back(value);
    }
    long long answer = 2;
    last_in[values[0]] = 0;
    diff_seq[0] = 1;
    for (long long i = 1; i < n; ++i) {
        diff_seq.push_back((answer) % static_cast<long long>(pow(10, 9) + 7));
        answer *= 2;
        answer -= (last_in[values[i]] == -1 ? 0 : diff_seq[last_in[values[i]]]);
        answer += static_cast<long long>(pow(10, 9) + 7);
        answer %= static_cast<long long>(pow(10, 9) + 7);
        if (answer < 0) {
            diff_seq[i] += static_cast<long long>(pow(10, 9) + 7);
        }
        last_in[values[i]] = i;
    }
    std::cout << answer-1;
 
}
