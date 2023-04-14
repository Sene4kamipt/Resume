    #include <vector>
    #include <iostream>
    #include<algorithm>
    using namespace std;
    void fastscan(int& number)
     
    {
        bool negative = false;
        register int c;
        number = 0;
        c = getchar();
        for (; (c > 47 && c < 58); c = getchar())
            number = number * 10 + c - 48;
    }
    int main()
    {
     
        ios::sync_with_stdio(false);
        cin.tie(NULL);
        vector <vector <int> > Avector;
        vector <vector <int> > Bvector;
        vector <int> answer;
        int kol_A;
        int kol_B;
        int len;
        int element;
        fastscan(kol_A);
        fastscan(kol_B);
        fastscan(len);
        Avector.resize(kol_A);
        Bvector.resize(kol_B);
        for (int i = 0; i < kol_A; ++i) {
            for (int j = 0; j < len; ++j) {
                fastscan(element);
                Avector[i].push_back(element);
            }
        }
        for (int i = 0; i < kol_B; ++i) {
            for (int j = 0; j < len; ++j) {
                fastscan(element);
                Bvector[i].push_back(element);
            }
        }
        int i;
        int j;
        int q;
        fastscan(q);
        for (int ii = 0; ii < q; ii++) {
            int l = 0;
            int r = len - 1;
            int mid;
            fastscan(i);
            fastscan(j);
            i--;
            j--;
            while (l<r-1) {
                mid = (l + r) / 2;
                if ((Avector[i][mid] - Bvector[j][mid]) <= 0) {
                    l = mid;
     
                }
                else {
                    r = mid;
                };
            };
     
            if (max(Avector[i][l], Bvector[j][l]) < max(Avector[i][r], Bvector[j][r])) {
                answer.push_back(l);
            }
            else { answer.push_back(r); };
     
     
        };
        for (int ii = 0; ii < q; ii++) {
            printf("%d", answer[ii] + 1);
            printf ("\n");
        }
    }
