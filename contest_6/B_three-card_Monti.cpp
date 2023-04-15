    #include <iostream>
    #include <vector>
    #include <string>
     
    std::vector<std::vector<long long>> multiplication(std::vector<std::vector<long long>> matrix1, std::vector<std::vector<long long>>& matrix2, long long modul) {
        std::vector<std::vector<long long>> answer;
        for (int i = 0; i < matrix1.size(); ++i) {
            answer.push_back({});
            for (int j = 0; j < matrix2[0].size(); ++j) {
                answer[i].push_back(0);
                for (int k = 0; k < matrix2.size(); ++k) {
                    answer[i][j] = (answer[i][j] + matrix1[i][k] * matrix2[k][j]+modul) % modul;
                }
            }
        }
        return answer;
    }
     
    long long pow_(long long x, long long degree,long long modul) {
        if (degree == 0) return 1;
        long long answer = pow_(x, degree / 2,modul);
        answer = (answer*answer)%modul;
        if (degree % 2)
            answer = (answer*x)%modul;
        return answer;
    }
     
    int main()
    {
        int k;
        std::cin >> k;
        bool nechet = true;
        long long input;
        long long degree = 2;
        long long modul = 1'000'000'007;
        for (int i = 0; i < k; ++i) {
            std::cin >> input;
            if (input % 2 == 0) {
                nechet = false;
            }
            degree = pow_(degree, input, modul);
        }
        std::vector<std::vector<long long>> jnf = { {(nechet ? -1 : 1),0}, {0,degree} };
        std::vector<std::vector<long long>> S = { {1000000006,2}, {1,1} };
        std::vector<std::vector<long long>> S_2 = { {666'666'671,666'666'672}, {333'333'336,333'333'336} };
        jnf = multiplication(S, jnf, modul);
        jnf = multiplication(jnf, S_2, modul);
        jnf = multiplication({{ 0, 1 }}, jnf, modul);
        input = (jnf[0][1] * 500'000'004) % modul;
        std::cout << input << "/" << (degree*500'000'004)%modul;
    }
