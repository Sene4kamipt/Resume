    #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <cmath>
    int main() {
        int number_of_phones, height;
        std::cin >> height >> number_of_phones;
        if (height > 1 && number_of_phones == 0) {
            std::cout << -1;
            return 0;
        }
        if (number_of_phones >= log2(height)) {
            std::cout << ceil(log2(height));
            return 0;
        }
        std::vector<std::vector<int>> number_of_throws(number_of_phones + 1, std::vector<int>(height + 1, 0));
        int mini = 0;
        int R_border, L_border, mid;
        for (int i = 2; i <= height; ++i) {
            for (int j = 1; j <= number_of_phones; ++j) {
                mini = 2000000000;
                L_border = 0;
                R_border = i - 1;
                mid = (L_border + R_border) / 2;
                if (j == 1) {
                    number_of_throws[j][i] = i - 1;
                }
                else {
                    while (R_border != L_border + 1 && R_border != L_border) {
                        if (number_of_throws[j][i - mid] >= number_of_throws[j - 1][mid]) {
                            L_border = mid;
                        }
                        else {
                            R_border = mid;
                        }
                        mid = (L_border + R_border) / 2;
                    }
                    number_of_throws[j][i] = 1+std::min(std::max(number_of_throws[j - 1][L_border], number_of_throws[j][i - L_border]), std::max(number_of_throws[j - 1][R_border], number_of_throws[j][i - R_border]));
                }
            }
        }
        std::cout << number_of_throws[number_of_phones][height];
    }
