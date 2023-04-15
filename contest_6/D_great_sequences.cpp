    #include <iostream>
    #include <vector>
    #include <string>
    #include <math.h>
    std::vector<std::vector<long long>> multiplication(std::vector<std::vector<long long>>& matrix1, std::vector<std::vector<long long>>& matrix2, int modul) {
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
     
    bool to_2(long long number) {
        int ans = 0;
        while (number > 0) {
            if (number % 2 == 1) {
                ans += 1;
            }
            number /= 2;
        }
        if (ans % 3 == 0) {
            return true;
        }
        return false;
    }
     
    int main()
    {
        int n;
        long long input, lenght;
        std::cin >> n>> lenght;
        std::vector<long long> numbers;
        for (int i = 0; i < n; ++i) {
            std::cin >> input;
            numbers.push_back(input);
        }
        if (lenght == 1) {
            std::cout << n;
            return 0;
        }
        std::vector<std::vector<long long>> matrix(n, std::vector<long long>(n, 1));
        std::vector<std::vector<long long>> matrix_ans(n, std::vector<long long>(n, 1));
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                long long xorij = numbers[i] ^ numbers[j];
                if (!to_2(xorij)) {
                    matrix[i][j] = 0;
                    matrix[j][i] = 0;
                    matrix_ans[i][j] = 0;
                    matrix_ans[j][i] = 0;
                }
            }
        }
        //for (int i = 0; i < n; ++i) {
            //for (int j = 0; j < n; ++j) {
                //std::cout << matrix[i][j] << "  ";
            //}
            //std::cout << '\n';
        //}
        std::string bit_length;
        long long n_cp = lenght;
        --lenght;
        while (lenght != 0) {
            if (lenght % 2 == 0) {
                bit_length = "0" + bit_length;
            }
            else {
                bit_length = "1" + bit_length;
            }
            lenght /= 2;
        }
        long long modul = std::pow(10, 9) + 7;
        for (int i = 1; i < bit_length.size(); ++i) {
            matrix_ans = multiplication(matrix_ans, matrix_ans, modul);
            if (bit_length[i] == '1') {
                matrix_ans = multiplication(matrix, matrix_ans, modul);
            }
        }
        {long long ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ans = (ans + matrix_ans[i][j]) % modul;
            }
        }
        std::cout << ans << '\n'; }
     
    }
