    #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <cassert>
    #include <fstream>
    #pragma GCC optimize("O3")
    #pragma GCC optimize("unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
     
    int bit(int number, int k) {
        return (number >> k) % 2;
    }
     
    int oldest(int number) {
        /*int ans = 0;
        int x = 1;
        if(number >= (x << 16)) {
            x <<= 16;
            ans += 16;
        }
        if(number >= (x << 8)) {
            x <<= 8;
            ans += 8;
        }
        if(number >= (x << 4)) {
            x <<= 4;
            ans += 4;
        }
        if(number >= (x << 2)) {
            x <<= 2;
            ans += 2;
        }
        if(number >= (x << 1)) {
            x <<= 1;
            ans += 1;
        }
        return ans;*/
        int t = 1 << 30;
        int ans = 30;
        while(number < t) {
            t >>= 1;
            --ans;
        }
        return ans;
     
    }
     
    std::string bit_num(int number, int n) {
        std::string ans = "";
        while(number > 0) {
            if(number % 2 == 0) {
                ans = ans + '0';
            } else {
                ans = ans + '1';
            }
            number /= 2;
        }
        while(ans.size() < n) {
            ans = ans + '0';
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
     
    int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
        std::cout.tie(NULL);
        // std::ifstream in("file.in");
        int n = 0;
        std::cin >> n;
        // in >> n;
        std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
        char ij_elem = 0;
        bool state = false;
        std::string line = "";
        for(int i = 0; i < n; ++i) {
            std::cin >> line;
            // in >> line;
            for(int j = 0; j < n; ++j) {
                matrix[i][j] = line[j] - '0';
                if(line[j] - '0' == 1) {
                    state = true;
                }
            }
        }
        if(n == 1) {
            std::cout << 2 << std::endl;
            return 0;
        }   
        if(!state) {
            std::cout << (n + 1) << std::endl;
            return 0;
        }
     
        std::vector<bool> clicks_in_first_part(1 << (n / 2), true);
        std::vector<int> clicks_in_second_part(1 << (n - n / 2), 1);
     
        int64_t index1 = 1;
        int64_t index2 = 1;
        while(index1 < (1 << n / 2)) {
            int oldest_bit = oldest(index1);
            int new_number = index1 ^ (1 << oldest_bit);
            if(new_number == 0) {
                clicks_in_first_part[index1] = true;
                ++index1;
                continue;
            }
            int oldest_bit2 = oldest(new_number);
            if(!clicks_in_first_part[(index1 ^ (1 << oldest_bit))] || !clicks_in_first_part[(index1 ^ (1 << oldest_bit2))] || matrix[n / 2 - 1 - oldest_bit][n / 2 - 1 - oldest_bit2] == 0) {
                clicks_in_first_part[index1] = false;
            }
            ++index1;
        }
     
     
        while(index2 < (1 << (n - n / 2))) {
            int oldest_bit = oldest(index2);
            int new_num = index2 ^ (1 << oldest_bit);
            if(new_num == 0) {
                clicks_in_second_part[index2] = 1;
                ++index2;
                continue;
            }
            int oldest_bit2 = oldest(new_num);
            if(clicks_in_second_part[index2 ^ (1 << oldest_bit)] == 0 || clicks_in_second_part[index2 ^ (1 << oldest_bit2)] == 0 || matrix[n - oldest_bit - 1][n - oldest_bit2 - 1] == 0) {
                clicks_in_second_part[index2] = 0;
            }
            ++index2;
        }   
     
     
        for(int i = 0; i < (n - n / 2); ++i) {
            for(int j = 0; j < (1 << (n - n / 2)); ++j) {
                if(!bit(j, i)) {
                    clicks_in_second_part[j + (1 << i)] = (clicks_in_second_part[j + (1 << i)] + clicks_in_second_part[j]);
                }
            }
     
        }
     
        std::vector<int> masks_in_two_for_one;
        int cur_mask = 0;
        for(int i = 0; i < n / 2; ++i) {
            cur_mask = 0;
            for(int j = n / 2; j < n; ++j) {
                if(matrix[i][j]) {
                    cur_mask |= (1 << (n - n / 2 - (j - n / 2)) - 1);
                }
            }
            masks_in_two_for_one.push_back(cur_mask);
        }
     
     
        std::vector<int> masks_one_two(1 << (n / 2));
        int64_t ans = 0;
        for(int i = 1; i < (1 << (n / 2)); ++i) {
            int oldest_bit = oldest(i);
            int new_num = i ^ (1 << oldest_bit);
            if(new_num == 0) {
                masks_one_two[i] = masks_in_two_for_one[n / 2 - oldest_bit - 1];
            } else {
                masks_one_two[i] = masks_in_two_for_one[n / 2 - 1 - oldest_bit] & masks_one_two[new_num];
            }
            if(i != 0 && clicks_in_first_part[i]) {
                ans += clicks_in_second_part[masks_one_two[i]];
            }
        }
        ans += (clicks_in_second_part[(1 << (n - n / 2)) - 1]);
        std::cout << ans << std::endl;
    }
