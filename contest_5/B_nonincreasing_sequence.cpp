    #include <iostream>
    #include <vector>
    #include <cmath>
    #include <algorithm>
    #include <utility>
     
    long long infinity_minus = static_cast<long long>(-std::pow(2, 31) + 1);
     
    void getting_answer(std::vector<int>& history_of_elem, int& i, std::vector<long long> &least_number, std::vector<int> &history_of_seq) {
    	least_number[0] = history_of_seq[i];
    	int k = 1;
    	i = history_of_seq[i];
    	while (history_of_elem[i] != -1) {
    		least_number[k] = history_of_elem[i];
    		i = history_of_elem[i];
    		++k;
    	}
    	return;
    }
     
    void counting(int &n, long long &value, std::vector<long long> &least_number, int &best_variant, std::vector<int>& history_of_elem, std::vector<int>& history_of_seq) {
    	for (int i = 0; i < n; ++i) {
    		std::cin >> value;
    		int j = int(std::upper_bound(least_number.begin(), least_number.end(), -value) - least_number.begin());
    		if (least_number[j - 1] == value) {
    			--j;
    		}
    		if (least_number[j] == -infinity_minus) {
    			++best_variant;
    		}
    		least_number[j] = -value;
    		history_of_seq[j] = i + 1;
    		history_of_elem[i + 1] = history_of_seq[j - 1];
    	}
    }
     
    int main() {
    	std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    	int n;
    	long long value;
    	std::cin >> n;
    	std::vector<int> history_of_seq(static_cast<unsigned int>(n + 1), -1);
    	std::vector<int> history_of_elem(static_cast<unsigned int>(n + 1), -1);
    	std::vector<long long> least_number(n + 1, -infinity_minus);
    	least_number[0] = infinity_minus;
    	int best_variant = 0;
    	counting(n, value, least_number, best_variant, history_of_elem, history_of_seq);
    	int i = best_variant + 1;
    	std::cout << --i << '\n';
    	getting_answer(history_of_elem, i, least_number, history_of_seq);
    	for (int i = 0; i < best_variant; ++i) {
    		std::cout << least_number[best_variant - 1 - i] << " ";
    	}
    }
