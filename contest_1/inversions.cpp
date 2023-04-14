    #include <iostream>
    #include <vector>
    #include<fstream>
     
    using namespace std;
     
     void merge(vector<long long> & massiv, int l, int m, int r, long long & ans){
        long long i = 0;
        long long j = 0;
        long long kol_vo_inv = 0;
        vector<int> res(r - l);
        while ((i < m - l) && (j < r - m)){
            if (massiv[i + l] <= massiv[m + j]) {
                res[i + j] = massiv[l + i];
                i+=1;
                ans += kol_vo_inv;
            }
            else{
                res[i + j] = massiv[m + j];
                j+=1;
                kol_vo_inv+=1;
            }
        }
        while (i < m - l){
            res[i + j] = massiv[l + i];
            i+=1;
            ans += kol_vo_inv;
        }
        while (j < r - m){
            res[i + j] = massiv[m + j];
            j+=1;
        }
        for (int k = 0; k < i + j; k++){
            massiv[l+k] = res[k];
        }
    }
     
     
    void mergeSort(vector<long long> & a, int l, int r, long long & ans){
        if (r - l <= 1){ return;}
        long long m = (l + r)/2;
        mergeSort(a, l, m, ans);
        mergeSort(a, m, r, ans);
        merge(a, l, m, r, ans);
    }
     
     
    int main() {
        ifstream fin("inverse.in");
        ofstream fout("inverse.out");
        long long n;
        long long vedro;
        long long ans = 0;
        fin >> n;
        vector<long long> massiv;
        for (int i = 0; i < n; i++){
            fin >> vedro;
            massiv.push_back(vedro);
        }
        mergeSort(massiv, 0, n, ans);
        fout << ans;
    }
