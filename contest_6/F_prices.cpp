    #include<iostream>
    #include<vector>
    #include <algorithm>
     
    int main() {
        int number_of_shops, number_of_products;
        std::cin >> number_of_shops >> number_of_products;
     
        std::vector<std::vector<int>> shops(number_of_shops, std::vector<int>(number_of_products+1,0));
        int input;
        for (int i = 0; i < number_of_shops; ++i) {
            for (int j = 0; j < number_of_products + 1; ++j) {
                std::cin >> input;
                shops[i][j] = input;
            }
        }
        std::vector<std::vector<int>> prices_if_visit_last_shop(number_of_shops, std::vector<int>(1 << number_of_products, INT_MAX/2));
        std::vector<std::vector<int>> prices(number_of_shops, std::vector<int>(1 << number_of_products, INT_MAX/2));
     
        for (int i = 0; i < number_of_products; ++i) {
            for (int j = 0; j < number_of_shops; ++j) {
                prices_if_visit_last_shop[j][1 << i] = shops[j][i + 1] + shops[j][0];
                if (j == 0) {
                    prices[j][1 << i] = prices_if_visit_last_shop[j][1 << i];
                }
                else {
                    prices[j][1 << i] = std::min(prices_if_visit_last_shop[j][1 << i], prices[j - 1][1 << i]);
                }
            }
        }
     
        for (int shop = 0; shop < number_of_shops; ++shop) {
            for (int mask = 1; mask < (1 << number_of_products); ++mask) {
                for (int product = 0; product < number_of_products; ++product) {
                    if ((mask / (1 << product)) % 2 == 1) {
                        prices_if_visit_last_shop[shop][mask] = std::min(prices_if_visit_last_shop[shop][mask], prices_if_visit_last_shop[shop][mask ^ (1 << product)] + shops[shop][product + 1]);
                        if (shop != 0) {
                            prices_if_visit_last_shop[shop][mask] = std::min(prices_if_visit_last_shop[shop][mask], prices[shop - 1][mask ^ (1 << product)] + shops[shop][product + 1] + shops[shop][0]);
                        }
                    }
                }
                if (shop != 0) {
                    prices[shop][mask] = std::min(prices[shop - 1][mask],prices[shop][mask]);
                }
                prices[shop][mask] = std::min(prices[shop][mask], prices_if_visit_last_shop[shop][mask]);
            }
        }
        //for (int i = 0; i < number_of_shops; ++i) {
          //  for (int mask = 0; mask < (1 << number_of_products); ++mask) {
            //    std::cout << i << " " << mask << " " << prices_if_visit_last_shop[i][mask] << " " << prices[i][mask] << '\n';
            //}
        //}
        std::cout << prices[number_of_shops - 1][(1 << number_of_products) - 1];
    }
