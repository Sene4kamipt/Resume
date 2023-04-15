    #include <iostream>
    #include <vector>
    #include<math.h>
    #include <algorithm>
    std::vector<std::vector<long long>> multiplication(std::vector<std::vector<long long>>& matrix1, std::vector<std::vector<long long>>& matrix2, long long modul) {
        std::vector<std::vector<long long>> answer;
        for (int i = 0; i < matrix1.size(); ++i) {
            answer.push_back({});
            for (int j = 0; j < matrix2[0].size(); ++j) {
                answer[i].push_back(0);
                for (int k = 0; k < matrix2.size(); ++k) {
                    answer[i][j] = (answer[i][j] + matrix1[i][k] * matrix2[k][j]) % modul;
                }
            }
        }
        return answer;
    }
     
    int main()
    {
        int number_of_sections,high_border,prev_hight;
        long long modul = std::pow(10, 9) + 7;
        long long last_koordinate, left_border, right_border;
        std::cin >> number_of_sections >> last_koordinate;
        std::cin >> left_border >> right_border >> high_border;
        prev_hight = high_border;
        std::vector<std::vector<long long>> ans_matrix(high_border+1, std::vector<long long>(high_border+1,0));
        ans_matrix[0][0]=1;
        for (int i = 0; i < number_of_sections; ++i) {
            std::vector<std::vector<long long>>number_ways(high_border + 1, std::vector<long long>(high_border+1, 0));
            std::vector<std::vector<long long>>curr_ans(high_border + 1, std::vector<long long>(high_border + 1, 0));
            for (int i = 0; i < high_border + 1; ++i) {
                if (i != 0) {
                    number_ways[i][i-1]+=1;
                    curr_ans[i][i - 1] += 1;
                }
                number_ways[i][i] = 1;
                curr_ans[i][i] = 1;
                if (i != high_border) {
                    number_ways[i][i + 1] = 1;
                    curr_ans[i][i + 1] = 1;
                }
            }
            //for (int i = 0; i < high_border + 1; ++i) {
                //for (int j = 0; j < high_border + 1; ++j) {
                    //std::cout << number_ways[i][j] << "  ";
                //}
                //std::cout << '\n';
            //}
            std::string bit_dist;
            long long distance = std::min(right_border - left_border,last_koordinate-left_border);
            while (distance != 0) {
                if (distance % 2 == 0) {
                    bit_dist = "0" + bit_dist;
                }
                else {
                    bit_dist = "1" + bit_dist;
                }
                distance /= 2;
            }
            for (int i = 1; i < bit_dist.size(); ++i) {
                curr_ans = multiplication(curr_ans, curr_ans, modul);
                if (bit_dist[i] == '1') {
                    curr_ans= multiplication(number_ways, curr_ans, modul);
                }
            }
            //for (int i = 0; i < high_border + 1; ++i) {
              //  for (int j = 0; j < high_border + 1; ++j) {
                //    std::cout << curr_ans[i][j] << "  ";
                //}
                //std::cout << '\n';
            //}
            //std::cout << '\n';
            if (i != 0) {
                if (prev_hight < high_border) {
                    std::vector<std::vector<long long>> ans_matrix2(high_border + 1, std::vector<long long>(high_border + 1, 0));
                    for (int i = 0; i < prev_hight + 1; ++i) {
                        for (int j = 0; j < prev_hight + 1; ++j) {
                            ans_matrix2[i][j] = ans_matrix[i][j];
                        }
                    }
                    ans_matrix = multiplication(ans_matrix2, curr_ans, modul);
                }
                if (prev_hight > high_border) {
                    //std::wcout << "var";
                    std::vector<std::vector<long long>> ans_matrix2(high_border+ 1, std::vector<long long>(high_border + 1, 0));
                    for (int i = 0; i < high_border + 1; ++i) {
                        for (int j = 0; j < high_border + 1; ++j) {
                            ans_matrix2[i][j] = ans_matrix[i][j];
                        }
                    }
                    ans_matrix = multiplication(ans_matrix2, curr_ans, modul);
                }
                if (prev_hight == high_border) {
                    ans_matrix = multiplication(ans_matrix, curr_ans,modul);
                }
            }
            else {
                ans_matrix= multiplication(ans_matrix, curr_ans, modul);
            }
            prev_hight = high_border;
            if (i != number_of_sections - 1) {
                std::cin >> left_border >> right_border >> high_border;
            }
        }
        //for (int i = 0; i < high_border + 1; ++i) {
            //for (int j = 0; j < high_border + 1; ++j) {
                //std::cout << ans_matrix[i][j] << "  ";
            //}
            //std::cout << '\n';
        //}  
        std::cout << ans_matrix[0][0] << '\n'; 
    }
