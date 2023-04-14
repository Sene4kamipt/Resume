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
     
    void build(std::vector<std::vector<long long>>& chisla, int v, int tl, int tr, std::vector<long long>& vvod) {
    	if (tl == tr) {
    		chisla[v][0] = vvod[tl];
    		chisla[v][1] = tl;
    		chisla[v][2] = tl;
    		chisla[v][3] = -1;
    	}
    	else {
    		int tm = (tl + tr) / 2;
    		build(chisla, v * 2 + 1, tl, tm, vvod);
    		build(chisla, v * 2 + 2, tm + 1, tr, vvod);
    		chisla[v][0] = std::min(chisla[v * 2 + 2][0], chisla[v * 2 + 1][0]);
    		chisla[v][1] = tl;
    		chisla[v][2] = tr;
    		chisla[v][3] = -1;
    	}
    }
     
    void push(long long v, std::vector<std::vector<long long>>& chisla) {
    	if (chisla[v][3] == -1) {
    		return;
    	}
    	long long x = chisla[v][3];
    	chisla[2 * v + 1][0] = x;
    	chisla[2 * v + 2][0] = x;
    	chisla[2 * v + 1][3] = x;
    	chisla[2 * v + 2][3] = x;
    	chisla[v][3] = -1;
    }
     
    void Assign(long long v, long long Left, long long Right, long long x, std::vector<std::vector<long long>>& chisla) {
    	if ((chisla[v][1] == Left) && (chisla[v][2] == Right)) {
    		chisla[v][3] = x;
    		chisla[v][0] = x;
    		return;
    	}
    	push(v, chisla);
    	long long tm = (chisla[v][1] + chisla[v][2]) / 2;
    	if (Left <= tm) {
    		Assign(2 * v + 1, Left, std::min(Right, tm), x, chisla);
    	}
    	if (Right > tm) {
    		Assign(2 * v + 2, std::max(Left, tm + 1), Right, x, chisla);
    	}
    	chisla[v][0] = std::min(chisla[2 * v + 1][0], chisla[2 * v + 2][0]);
    }
     
    void maxi(long long& ans, std::vector<std::vector<long long>>& chisla, long long v, long long Left, long long Right) {
    	//std::cout << v <<" "<< Left <<" "<<Right;
    	if ((chisla[v][1] == Left) && (chisla[v][2] == Right)) {
    		ans=std::min(ans,chisla[v][0]);
    		//std::cout << chisla[v][0];
    		return;
    	}
    	long long tm = (chisla[v][1] + chisla[v][2]) / 2;
    	push(v, chisla);
    	if (Left <= tm) {
    		maxi(ans, chisla, 2 * v + 1, Left, std::min(Right, tm));
    	}
    	if (Right > tm) {
    		maxi(ans, chisla, 2 * v + 2, std::max(Left, tm+1), Right);
    	}
    }
     
    int main() {
    	std::ios_base::sync_with_stdio(false);
    	std::cin.tie(NULL);
    	long long N;
    	fastscan(N);
    	std::vector <long long> vvod;
    	std::vector<std::vector<long long>> chisla;
    	long long vvch;
    	for (long long l = 0; l < N; ++l) {
    		fastscan(vvch);
    		vvod.push_back(vvch);
    		fastscan(vvch);
    		vvod[l]+=(vvch);
    		fastscan(vvch);
    		vvod[l] += (vvch);
    	}
    	int step = 0;
    	while (N > pow(2, step)) {
    		step += 1;
    	}
    	for (long long i = 0; i < pow(2, step); ++i) {
    		chisla.push_back({ -1,-1,-1,-1 });
    		chisla.push_back({ -1,-1,-1,-1 });
    	}
    	build(chisla, 0, 0, N - 1, vvod);
    	long long M;
    	fastscan(M);
    	long long c, d, e, f, r, g, b;
    	std::vector<long long>answer;
    	for (long long i = 0; i < M; ++i) {
    		fastscan(c);
    		fastscan(d);
    		fastscan(r);
    		fastscan(g);
    		fastscan(b);
    		Assign(0, c, d, r + g + b, chisla);
     
    		//for (int j = 0; j < 16; ++j) {
    			//std::cout << chisla[j][0] << " " << chisla[j][1] << " " << chisla[j][2] << " " << chisla[j][3] << '\n';
    		//}
    		fastscan(e);
    		fastscan(f);
    		long long ans = 100000000;
    		maxi(ans, chisla, 0, e, f);
    		answer.push_back(ans);
    	}
    	for (long long i = 0; i < answer.size(); ++i) {
    		std::cout << answer[i] <<" ";
    	}
    }


