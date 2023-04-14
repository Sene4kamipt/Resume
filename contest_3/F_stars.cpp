    #include <iostream>
    #include <vector>
     
    long long x, y, z;
     
    void Update(std::vector<std::vector<std::vector <long long>>>& zvezdy, long long posx, long long posy, long long posz, long long delta) {
        for (long long i = posx; i < x; i = (i | (i + 1))) {
            for (long long j = posy; j < y; j = (j | (j + 1))) {
                for (long long k = posz; k < z; k = (k | (k + 1))) {
                    zvezdy[i][j][k] += delta;
                }
            }
        }
    }
     
    long long GetPrefSum(std::vector<std::vector<std::vector<long long>>>& zvezdy, long long posx, long long posy, long long posz) {
        long long ans = 0;
        if ((posx < 0) | (posy < 0) | (posz < 0)) {
            return 0;
        }
        for (long long i = posx; i >=0; i = ((i & (i + 1))-1)) {
            for (long long j = posy; j >=0; j = ((j & (j + 1))-1)) {
                for (long long k = posz; k >=0; k = ((k & (k + 1))-1)) {
                    ans += zvezdy[i][j][k];
                    //std::cout << "i=" << i << "j=" << j << "k=" << k<<"ans="<<ans<<'\n';
                }
            }
        }
        return ans;
    }
    int main()
    {
        std::vector<std::vector<std::vector<long long>>> zvezdy;
        std::cin >> x;
        y = x;
        z = x;
        for (long long i = 0; i < x; ++i) {
            std::vector<std::vector<long long>> subvec1;
            for (long long j = 0; j < y; j++) {
                std::vector<long long> subvec2;
                for (long long k = 0; k < z; ++k) {
                    subvec2.push_back(0);
                }
                subvec1.push_back(subvec2);
            }
            zvezdy.push_back(subvec1);
        }
        int m;
        while (true) {
            std::cin >> m;
            if (m == 3) {
                break;
            }
            if (m == 1) {
                long long posx, posy, posz,delta;
                std::cin >> posx >> posy >> posz >> delta;
                Update(zvezdy, posx, posy, posz, delta);
            }
            if (m == 2) {
                long long posx1, posy1, posz1, posx2, posy2, posz2;
                std::cin >> posx2 >> posy2 >> posz2 >> posx1 >> posy1 >> posz1;
                std::cout << GetPrefSum(zvezdy, posx1, posy1, posz1) - GetPrefSum(zvezdy, posx2 - 1, posy1, posz1) - GetPrefSum(zvezdy, posx1, posy2 - 1, posz1) - GetPrefSum(zvezdy, posx1, posy1, posz2 - 1) +
                    GetPrefSum(zvezdy, posx2 - 1, posy2 - 1, posz1) + GetPrefSum(zvezdy, posx1, posy2 - 1, posz2 - 1) + GetPrefSum(zvezdy, posx2 - 1, posy1, posz2 - 1) - GetPrefSum(zvezdy, posx2 - 1, posy2 - 1, posz2 - 1)<<'\n';
            }
        }
    }


