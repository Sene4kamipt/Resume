    #include <iostream>
    #include <vector>
    #include <algorithm>
     
    int main() {
        int amount_1, amount_2;
        std::cin >> amount_1 >> amount_2;
        int value;
        std::vector<int> seq_1;
        for (int i = 0; i < amount_1; ++i) {
            std::cin >> value;
            seq_1.push_back(value);
        }
        std::vector<int> seq_2;
        for (int i = 0; i < amount_2; ++i) {
            std::cin >> value;
            seq_2.push_back(value);
        }
        int sutable = 0;
        std::vector<std::vector<int>> len_of_seq(amount_1, std::vector<int>(amount_2, 0));
        for (int i = 0; i < amount_1; ++i) {
            sutable = 0;
            for (int j = 0; j < amount_2; ++j) {
                if (seq_1[i] == seq_2[j]) {
                    len_of_seq[i][j] = std::max(sutable + 1, (i != 0 ? len_of_seq[i - 1][j] : 0));
                }
                else {
                    if (i != 0) {
                        len_of_seq[i][j] = len_of_seq[i - 1][j];
                    }
                }
                if ((i != 0) && (seq_1[i] > seq_2[j]) && (len_of_seq[i - 1][j] > sutable)) {
                    sutable = len_of_seq[i - 1][j];
                }
            }
        }
     
        int answer = 0;
        for (int i = 0; i < amount_2; ++i) {
            if (answer < len_of_seq[amount_1 - 1][i]) {
                answer = len_of_seq[amount_1 - 1][i];
            }
        }
        std::cout << answer;
    }
