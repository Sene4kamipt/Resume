    #include <vector>
    #include <iostream>
    #include<algorithm>
     
    void build(std::vector<std::vector<long long>>& chisla, int v, int tl, int tr, std::vector<long long>& vvod) {
    	if (tl == tr) {
    		chisla[v][0] = vvod[tl];
    		chisla[v][1] = tl;
    		chisla[v][2] = tl;
    	}
    	else {
    		int tm = (tl + tr) / 2;
    		build(chisla, v * 2 + 1, tl, tm, vvod);
    		build(chisla, v * 2 + 2, tm + 1, tr, vvod);
    		chisla[v][0]=chisla[2*v+1][0]+chisla[v*2+2][0];
    		chisla[v][1] = tl;
    		chisla[v][2] = tr;
    	}
    }
     
    void update(long long v, long long tl, long long tr, long long x, long long delta, std::vector<std::vector<long long>>& chisla) {
    	if (tl == tr) {
    		chisla[v][0] += delta;
    	}
    	else {
    		long long tm = (tl + tr) / 2;
    		if (x <= tm) {
    			update(v * 2 + 1, tl, tm, x, delta, chisla);
    		}
    		else {
    			update(v * 2 + 2, tm + 1, tr, x, delta, chisla);
    		}
    		chisla[v][0] = chisla[2 * v + 1][0] + chisla[2 * v + 2][0];
    	}
    }
     
    long long GetSum(long long v, long long tl, long long tr, long long l, long long r, std::vector<std::vector<long long>>& chisla) {
    	if ((l == chisla[v][1]) && (r == chisla[v][2])) {
     
    		return chisla[v][0];
    	}
    	long long tm = (tl + tr) / 2;
    	long long ans = 0;
    	if (l <= tm) {
    		ans += GetSum(v * 2 + 1, tl, tm, l, std::min(r, tm), chisla);
    	}
    	if (r >= tm+1) {
    		ans+=GetSum(v * 2 + 2, tm + 1, tr, std::max(l, tm + 1), r,chisla);
    	}
    	return ans;
    }
     
     
    int main()
    {
    	std::vector <long long> vvod;
    	std::vector<std::vector<long long>> chisla;
    	int deg[100001];
    	deg[1] = 1;
    	for (int i = 2; i < 100001; ++i) {
    		deg[i] = deg[i - 1];
    		if ((i >pow(2, deg[i - 1]) == 1)) {
    			++deg[i];
    		}
    	}
    	long long vvch;
    	long long K;
    	std::cin >> K;
    	for (long long n = 0; n < K; ++n) {
    		std::cin >> vvch;
    		if (n % 2 == 1) {
    			vvch *= -1;
    		}
    		vvod.push_back(vvch);
    	}
    	//std::cout << pow(2, deg[K]);
    	for (long long n = 0; n < pow(2, deg[K]);++n){
    		chisla.push_back({ -1,-1,-1 });
    		chisla.push_back({ -1,-1,-1 });
    	}
    	build(chisla, 0, 0, K-1, vvod);
    	long long summ = 0;
    	long long N;
    	std::cin >> N;
    	long long x, y, z;
    	for (long long i = 0; i < N; ++i) {
    		std::cin >> x >> y >> z;
    		if (x == 0) {
    			if (y % 2 == 1) {
    				update(0, 0, K - 1, y-1, z - vvod[y-1], chisla);
    				vvod[y-1] = z;
    			}
    			else {
    				update(0, 0, K - 1, y-1, -(z + vvod[y-1]), chisla);
    				vvod[y-1] = -z;
    			}
    		}
    		else {
    			summ = GetSum(0, 0, K - 1, y-1, z-1, chisla);
    			if (y % 2 == 0) {
    				summ *= -1;
    			}
    			std::cout << summ<<std::endl;
    		}
    	}
    }
