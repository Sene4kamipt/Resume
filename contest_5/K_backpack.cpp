    #include <iostream>
    #include <vector>
    int main()
    {
        int capasity;
        int number_of_golds;
        std::cin >> capasity >> number_of_golds;
        std::vector<bool>prev_summs(capasity + 1, false);
        std::vector<bool>curr_summs(capasity + 1, false);
        std::vector<long long>golds;
        int value;
        for (int i = 0; i < number_of_golds; ++i) {
            std::cin >> value;
            golds.push_back(value);
        }
        for (int i = 0; i < number_of_golds; ++i) {
            if (golds[i] <= capasity) {
                curr_summs[golds[i]] = true;
                for (int j = 1; j < capasity - golds[i] + 1; ++j) {
                    if (prev_summs[j]) {
                        curr_summs[j + golds[i]] = true;
                    }
                }
            }
            for (int j = 0; j < capasity + 1; ++j) {
                prev_summs[j] = curr_summs[j];
            }
            
        }
        int i = capasity;
        while (!prev_summs[i]&&(i>0)) {
            --i;
        }
        std::cout << ((i > 0) ? i : 0);
    }
