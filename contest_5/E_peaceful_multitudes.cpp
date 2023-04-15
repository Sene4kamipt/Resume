#include <iostream>
#include <vector>
 
int main()
{
    int n;
    std::cin >> n;
    std::vector < std::vector<int>> mult;
    for (int i = 0; i < n + 1; ++i) {
        mult.push_back({});
        for (int j = 0; j < n + 1; ++j) {
            mult[i].push_back(0);
        }
    }
    mult[0][0] = 1;
    for (int summ = 1; summ < n + 1; ++summ) {
        for (int number = 1; number<=summ; ++number) {
            for (int j = 0; j <= int(number / 2); ++j) {
                mult[summ][number] += mult[summ - number][j];
            }
        }
    }
    long long summ = 0;
 
    for (int i = 0; i < n + 1; ++i) {
        summ += mult[n][i];
    }
    std::cout << summ;
}
