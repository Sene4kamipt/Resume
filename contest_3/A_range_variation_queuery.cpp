    #include <vector>
    #include <iostream>
    #include<algorithm>
     
    void build(std::vector<std::vector<long long>>& chisla, int v, int tl, int tr, std::vector<long long>& vvod) {
    	if (tl == tr){
    		chisla[v][0] = vvod[tl];
    		chisla[v][1] = vvod[tl];
    		chisla[v][2] = tl;
    		chisla[v][3] = tl;
    		}
    	else {
    		int tm = (tl + tr) / 2;
    		build(chisla, v * 2+1, tl, tm,vvod);
    		build(chisla, v * 2 + 2, tm + 1, tr,vvod);
    		chisla[v][0] = std::max(chisla[v * 2 + 2][0] , chisla[v * 2 + 1][0]);
    		chisla[v][1] = std::min(chisla[v * 2 + 2][1], chisla[v * 2 + 1][1]);
    		chisla[v][2] = tl;
    		chisla[v][3] = tr;
    	}
    }
     
    void update(long long v, long long tl, long long tr, long long x, long long delta, std::vector<std::vector<long long>>& chisla) {
    	if (tl == tr) {
    		chisla[v][0] += delta;
    		chisla[v][1] += delta;
    	}
    	else {
    		long long tm = (tl + tr) / 2;
    		if (x <= tm) {
    			update(v * 2 + 1, tl, tm, x, delta,chisla);
    		}
    		else {
    			update(v * 2 + 2, tm+1, tr, x, delta, chisla);
    		}
    		chisla[v][0] = std::max(chisla[v * 2 + 2][0], chisla[v * 2 + 1][0]);
    		chisla[v][1] = std::min(chisla[v * 2 + 2][1], chisla[v * 2 + 1][1]);
    	}
    }
     
    void raznost(long long v, long long tl, long long tr, long long l, long long r, long long& maxi, long long& mini, std::vector<std::vector<long long>>& chisla) {
    	if (l > r) {
    		return void();
    	}
    	//std::cout << chisla[v][0] <<' '<<chisla[v][1]<<std::endl;
    	if ((l == tl) && (r == tr)) {
    		maxi = std::max(maxi, chisla[v][0]);
    		mini = std::min(mini, chisla[v][1]);
    		return void();
    	}
    	long long tm = (tl + tr) / 2;
    	raznost(v * 2 + 1, tl, tm, l, std::min(r, tm), maxi, mini, chisla);
    	raznost(v * 2 + 2, tm + 1, tr, std::max(l, tm + 1), r,maxi,mini, chisla);
    }
     
    int main()
    {
    	std::vector <long long> vvod;
    	std::vector<std::vector<long long>> chisla;
    	for (long long n = 0; n < 131584; ++n) {
    		if (n < 100001) {
    			vvod.push_back(static_cast<long long>(std::pow(n, 2)) % 12345 + static_cast<long long>(std::pow(n, 3)) % 23456);
    		}
    		chisla.push_back({ -1,-1,-1,-1 });
    		chisla.push_back({ -1,-1,-1,-1 });
    	}
    	build(chisla, 0, 0, 100000, vvod);
    	long long K;
    	long long x, y;
    	long long maxi = -1000000;
    	long long mini = 1000000;
    	std::cin >> K;
    	for (long long k = 0; k < K; ++k) {
    		std::cin >> x >> y;
    		if (x > 0) {
    			raznost(0, 0, 100000, x, y, maxi, mini, chisla);
    			std::cout << maxi - mini << std::endl;
    			maxi = -10000000;
    			mini = 1000000;
    		}
    		else {
    			update(0, 0, 100000, abs(x), y - vvod[abs(x)],chisla);
    			vvod[abs(x)] = y;
    		}
    		//std::cout << vvod[2] << ' ' << vvod[3];
    	}
    }
