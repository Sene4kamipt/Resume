    #include <iostream>
    #include<vector>
    #include <algorithm>
     
    int main()
    {
        int number_of_villages, number_of_posts;
        std::cin >> number_of_villages >> number_of_posts;
        std::vector<int> villages;
        int value;
        for (int i = 0; i < number_of_villages; ++i) {
            std::cin >> value;
            villages.push_back(value);
        }
        std::vector<long long> pref_vill = { 0 };
        for (int i = 1; i < number_of_villages; ++i) {
            pref_vill.push_back(pref_vill[i - 1] + i * (villages[i] - villages[i - 1]));
        }
        std::vector<long long> pref_sums(number_of_villages,0);
        for (int i = number_of_villages - 2; i >= 0; --i) {
            pref_sums[i] = pref_sums[i + 1] + (number_of_villages-i-1) * (villages[i + 1] - villages[i]);
        }
        //for (int i = 0; i < number_of_villages; ++i) {
            //std::cout << pref_sums[i] << " ";
        //}
        //std::cout << std::endl << std::endl;
        //for (int i = 0; i < number_of_villages; ++i) {
           // std::cout << pref_vill[i] << " ";
        //}
        //std::cout << std::endl << std::endl;
        std::vector<std::vector<long long>> dist_between_vill;
        for (int i = 0; i < number_of_villages; ++i) {
            dist_between_vill.push_back({});
            for (int j = 0; j < number_of_villages; ++j) {
                if (i > j) {
                    dist_between_vill[i].push_back(dist_between_vill[j][i]);
                }
                if (i == j) {
                    dist_between_vill[i].push_back(0);
                }
                if (i < j)
                {
                    dist_between_vill[i].push_back(0);
                    for (int k = i + 1; k < j; ++k) {
                        dist_between_vill[i][j] += std::min(villages[k] - villages[i], villages[j] - villages[k]);
                    }
                }
            }
        }
        //for (int i = 0; i < number_of_villages; ++i) {
           // for (int j = 0; j < number_of_villages; ++j) {
                //std::cout << dist_between_vill[i][j] << " ";
            //}
            //std::cout << std::endl;
        //}
    //std::cout << std::endl;
        std::vector<std::vector<std::vector<long long>>> min_dist(number_of_villages, std::vector<std::vector<long long>>(number_of_posts, std::vector<long long>(2, 0)));
        for (int i = 0; i < number_of_villages; ++i) {
            for (int j = 0; j < number_of_posts; ++j) {
                if (i < j) {
                    min_dist[i][j][0] = 9223372036854775807;
                    min_dist[i][j][1] = -1;
                }
                if (i > j) {
                    if (j == 0) {
                        min_dist[i][j][0] = pref_vill[i];
                    }
                    else {
                        min_dist[i][j][0] = 9223372036854775807;
                        for (int k = j; k <= i; ++k) {
                            if (min_dist[i][j][0] > dist_between_vill[k][i] + min_dist[k][j - 1][0]) {
                                min_dist[i][j][0] =dist_between_vill[k][i] + min_dist[k][j - 1][0];
                                min_dist[i][j][1] = k;
                            }
                        }
                    }
                }
            }
        }
        //for (int i = 0; i < number_of_villages; ++i) {
            //for (int j = 0; j < number_of_posts; ++j) {
                //std::cout << min_dist[i][j][0] << " "<<min_dist[i][j][1]<<"   ";
            //}
            //std::cout << std::endl;
        //}
        long long answer = 9223372036854775807;
        int key = 0;
        for (int i = number_of_posts - 1; i < number_of_villages; ++i) {
            //std::cout << min_dist[i][number_of_posts - 1][0] + pref_sums[i] << " "<<answer<<" ";
            if (answer > min_dist[i][number_of_posts - 1][0] + pref_sums[i]) {
                key = i;
                //std::cout << "!";
                answer = min_dist[i][number_of_posts - 1][0] + pref_sums[i];
            }
        }
        std::cout << answer<<'\n';
        int num = number_of_posts;
        std::vector<int> ans;
        while (key!=0){
            ans.push_back(villages[key]);
            key = min_dist[key][--number_of_posts][1];
        }
        for (int i = 0; i < num; ++i) {
            std::cout << ans[num - 1 - i]<<" ";
        }
    }


