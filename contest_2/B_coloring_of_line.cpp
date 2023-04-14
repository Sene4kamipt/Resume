    #include <iostream>
    #include <vector>
    #include<fstream>
     
    using namespace std;
     
    void merge(vector<vector<long long>>& massiv, int l, int m, int r) {
        long long i = 0;
        long long j = 0;
        vector<vector<long long>> res(r - l);
        while ((i < m - l) && (j < r - m)) {
            if (massiv[i + l][0] <= massiv[m + j][0]) {
                res[i + j] = massiv[l + i];
                i += 1;
            }
            else {
                res[i + j] = massiv[m + j];
                j += 1;
            }
        }
        while (i < m - l) {
            res[i + j] = massiv[l + i];
            i += 1;
        }
        while (j < r - m) {
            res[i + j] = massiv[m + j];
            j += 1;
        }
        for (int k = 0; k < i + j; k++) {
            massiv[l + k] = res[k];
        }
    }
     
     
    void mergeSort(vector<vector<long long>>& a, int l, int r) {
        if (r - l <= 1) { return; }
        long long m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m, r);
        merge(a, l, m, r);
    }
     
     
    int main() {
        long long n;
        long long vedro1;
        long long vedro2;
        long long ans = 0;
        cin >> n;
        vector<vector<long long>> massiv;
        for (int i = 0; i < n; i++) {
            cin >> vedro1>>vedro2;
            massiv.push_back({ vedro1, 1 });
            massiv.push_back({ vedro2, 2 });
        }
        mergeSort(massiv, 0, 2*n);
        long long kol_vo_aktiv=0;
        for (long long i = 0; i < 2 * n; ++i) {
            if (kol_vo_aktiv == 1) {
                ans += massiv[i][0] - massiv[i -1][0];
                
            }
            if (massiv[i][1] == 1) {
                kol_vo_aktiv += 1;
            }
            else {
                kol_vo_aktiv -= 1;
            }
        }
        cout << ans;
    }
