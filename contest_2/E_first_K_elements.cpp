    #include <iostream>
    #include <vector>
    #include <string>
    #include <algorithm>
     
    void swap(long long& a, long long& b) {
        long long vedro;
        vedro = a;
        a = b;
        b = vedro;
    }
     
    void SiftDown(long long nomer, std::vector <std::vector<long long>>& kucha, std::vector <long long>& ssylki) {
        long long v;
        while (nomer * 2 + 1 < kucha.size()) {
            v = nomer * 2 + 1;
            if ((v + 1 < kucha.size()) && (kucha[v + 1][0] < kucha[v][0])) {
                v += 1;
            }
            if (kucha[nomer][0] > kucha[v][0]) {
                swap(kucha[nomer][0], kucha[v][0]);
                swap(kucha[nomer][1], kucha[v][1]);
                swap(ssylki[kucha[nomer][1]], ssylki[kucha[v][1]]);
                nomer = v;
            }
            else {
                break;
            }
        }
    }
     
    void ExtractMin(std::vector <std::vector<long long>>& kucha, std::vector <long long>& ssylki) {
        swap(kucha[0][0], kucha[kucha.size() - 1][0]);
        swap(kucha[0][1], kucha[kucha.size() - 1][1]);
        swap(ssylki[kucha[0][1]], ssylki[kucha[kucha.size() - 1][1]]);
        kucha.pop_back();
        if (kucha.size() != 0) {
            SiftDown(0, kucha, ssylki);
        }
    }
     
    void SiftUp(long long nomer, std::vector <std::vector<long long>>& kucha, std::vector <long long>& ssylki) {
        long long v;
        while (nomer != 0) {
            if ((nomer % 2 != 0) && (kucha[nomer][0] < kucha[nomer / 2][0])) {
                swap(kucha[nomer][0], kucha[nomer / 2][0]);
                swap(kucha[nomer][1], kucha[nomer / 2][1]);
                swap(ssylki[kucha[nomer][1]], ssylki[kucha[nomer / 2][1]]);
                nomer /= 2;
            }
            else {
                if ((nomer % 2 == 0) && (kucha[nomer] < kucha[nomer / 2 - 1])) {
                    swap(kucha[nomer][0], kucha[nomer / 2 - 1][0]);
                    swap(kucha[nomer][1], kucha[nomer / 2 - 1][1]);
                    swap(ssylki[kucha[nomer][1]], ssylki[kucha[nomer / 2 - 1][1]]);
                    nomer = nomer / 2 - 1;
                }
                else {
                    break;
                }
            }
        }
    }
    int main()
    {
        std::vector <long long> ssylki;
        std::vector <std::vector<long long>> kucha;
        std::vector <long long> otvet;
        long long N;
        long long K;
        std::cin >> N >> K;
        long long a, x, y;
        long long proshlperem;
        long long modul = pow(2, 30);
        std::cin >> a >> x >> y;
        proshlperem = (-1) * ((a * x + y) % modul);
        kucha.push_back({ proshlperem, 0 });
        ssylki.push_back(kucha.size() - 1);
        SiftUp(kucha.size() - 1, kucha, ssylki);
        for (long long i = 0; i < N - 1; i++) {
            proshlperem = (-1) * ((x * abs(proshlperem) + y) % modul);
            if ((kucha.size() > K-1)&&(kucha[0][0]<proshlperem)) {
                kucha[0][0] = proshlperem;
                SiftDown(0, kucha, ssylki);
            }
            if (kucha.size()<=K-1){
                kucha.push_back({ proshlperem,i + 1 });
                ssylki.push_back( i + 1);
                SiftUp(i + 1, kucha, ssylki);
            }
            //for (long long j = 0; j < kucha.size(); ++j) {
            //    std::cout << kucha[j][0]<<" ";
            //}
            //std::cout << std::endl;
     
        }
        for (long long i = kucha.size() - 1; i > -1; i -= 1) {
            otvet.push_back(kucha[0][0]);
            ExtractMin(kucha, ssylki);
        }
        for (long long i = otvet.size() - 1; i > -1; i -= 1) {
            std::cout << otvet[i] * (-1) << " ";
        }
    }
