    #include <vector>
    #include <iostream>
    #include<algorithm>
     
    void fastscan(long long& number)
     
    {
    	bool negative = false;
    	register int c;
    	number = 0;
    	c = getchar();
    	for (; (c > 47 && c < 58); c = getchar())
    		number = number * 10 + c - 48;
    }
    long long n;
    long long index;
     
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
    		chisla[v][0] = std::max(chisla[v * 2 + 2][0], chisla[v * 2 + 1][0]);
    		chisla[v][1] = tl;
    		chisla[v][2] = tr;
    	}
    }
     
    void update(long long v, long long x, long long delta, std::vector<std::vector<long long>>& chisla) {
    	if (chisla[v][1] == chisla[v][2]) {
    		chisla[v][0] += delta;
    	}
    	else {
    		long long tm = (chisla[v][1] + chisla[v][2]) / 2;
    		if (x <= tm) {
    			update(v * 2 + 1, x, delta, chisla);
    		}
    		else {
    			update(v * 2 + 2, x, delta, chisla);
    		}
    		chisla[v][0] = std::max(chisla[v * 2 + 2][0], chisla[v * 2 + 1][0]);
    	}
    }
     
    void Getmax(long long v,long long l, long long r, long long& maxi, std::vector<std::vector<long long>>& chisla) {
    	//std::cout << "Getmax " << v << " " << l << " " << r<<std::endl;
    	if (l > r) {
    		return void();
    	}
    	if ((l == chisla[v][1]) && (r == chisla[v][2])) {
    		maxi = std::max(maxi, chisla[v][0]);
    		return void();
    	}
    	long long tm = (chisla[v][1]+chisla[v][2]) / 2;
    	Getmax(v * 2 + 1, l, std::min(r, tm), maxi, chisla);
    	Getmax(v * 2 + 2, std::max(l, tm + 1), r, maxi, chisla);
    	return void();
    }
     
     
    long long Get(long long v, std::vector<std::vector<long long>>& chisla, long long& index_left, long long& index_right, long long& chislo) {
    	long long ans = -2;
    	long long maxi = 0;
    	//std::cout << v << " " << index_left << " " << index_right;
    	if ((chisla[v][1] == chisla[v][2])&&(chisla[v][0]>=chislo)) {
    		return chisla[v][1];
    	}
    	if ((chisla[v][1] == chisla[v][2]) && (chisla[v][0] != chislo)) {
    		return -2;
    	}
    	Getmax(v, index_left, index_right, maxi, chisla);
    	if (maxi < chislo) {
    		return -2;
    	}
     
    	long long tm = (chisla[v][1]+chisla[v][2]) / 2;
    	if (chisla[2 * v + 1][2] >= index) {
    		ans = Get(2 * v + 1, chisla, index_left, tm, chislo);
    	}
    	tm += 1;
    	if (ans == -2) {
    		ans = Get(2 * v + 2, chisla, tm, index_right, chislo);
    	}
    	return ans;
    }
     
     
     
    int main()
    {
    	std::ios_base::sync_with_stdio(false);
    	std::cin.tie(NULL);
    	std::vector <long long> vvod;
    	std::vector<std::vector<long long>> chisla;
    	long long* m=new long long(0);
    	long long* vvch=new long long(0);
    	fastscan(n);
    	fastscan(*m);
    	//long long* deg = new long long[200001];
    	//deg[1] = 1;
    	//for (long long i = 2; i < 200001; ++i) {
    	//	deg[i] = deg[i - 1];
    	//	if ((i > pow(2, deg[i - 1]) == 1)) {
    	//		++deg[i];
    	//	}
    	//}
    	int step = 0;
    	while (*m > pow(2, step)) {
    		step+=1;
    	}
    	for (long long l = 0; l < n; ++l) {
    		fastscan(*vvch);
    		vvod.push_back(*vvch);
    	}
    	for (long long i = 0; i < pow(2, step); ++i) {
    		chisla.push_back({ -1,-1,-1 });
    		chisla.push_back({ -1,-1,-1 });
    	}
    	build(chisla, 0, 0, n-1, vvod);
    	long long* maxi = new long long(0);
    	//for (int i = 0; i < chisla.size(); ++i) {
    	//	std::cout << chisla[i][0] << " " << chisla[i][1] << " " << chisla[i][2]<<std::endl;
    	//}
    	n -= 1;
    	//Getmax(0, 0, n - 1, 2, 2, maxi, chisla);
    	//std::cout << maxi;
    	long long* x = new long long(0);
    	long long* y = new long long(0);
    	long long* z = new long long(0);
    	//delete[] deg;
    	for (long long q = 0; q < *m; ++q) {
    		fastscan(*x);
    		fastscan(*y);
    		fastscan(*z);
    		if (*x == 1) {
    			if (*z > chisla[0][0]) {
    				std::cout << "-1"<<std::endl;
    			}
    			else {
    				*y -= 1;
    				index = *y;
    				*vvch = Get(0,chisla,*y,n,*z);
    				std::cout << *vvch + 1 << '\n';
    			}
    		}
    		else {
    			update(0, *y - 1, *z - vvod[*y - 1], chisla);
    			vvod[*y - 1] = *z;
    			
    			//for (int i = 0; i < chisla.size(); ++i) {
    				//std::cout << chisla[i][0] << " " << chisla[i][1] << " " << chisla[i][2] << std::endl;
    			//}
    		}
    	}
    }
