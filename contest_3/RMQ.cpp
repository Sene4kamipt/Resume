    #include <vector>
    #include <iostream>
    #include <algorithm>
     
    void fastscan(long long& number)
     
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
    	long long N, M, vvch;
    	std::cin>>N;
    	std::cin>>M;
    	std::vector<std::vector<std::vector<long long>>> chisla;
    	chisla.push_back({});
    	for (long long i = 0; i < N; ++i) {
    		std::cin>>vvch;
    		chisla[0].push_back({vvch,i});
    	}
    	int K = 2;
    	int schet = 1;
    	while (K <= N) {
    		chisla.push_back({});
    		for (long long i = 0; i < N - K + 1; ++i) {
    			if (chisla[schet - 1][i][0] <= chisla[schet - 1][i + K / 2][0]) {
    				chisla[schet].push_back({ chisla[schet - 1][i][0],chisla[schet - 1][i][1] });
    			}
    			else {
    				chisla[schet].push_back({ chisla[schet - 1][i +K/2][0], chisla[schet - 1][i + K / 2][1]
    			});
    			}
    		}
    		K *= 2;
    		schet += 1;
    	}
    	long long* deg = new long long[2000001];
    	deg[0] = -1;
    	deg[1] = 0;
    	for (long long i = 2; i < 200001; ++i) {
    		deg[i] = deg[i - 1];
    		if ((i == pow(2, deg[i - 1]+1) == 1)) {
    			++deg[i];
    		}
    	}
    	//for (int i = 0; i < deg[N]+1; ++i) {
    //		for (int j = 0; j < N  - pow(2, i) + 1; j++) {
    //			std::cout << chisla[i][j][0] << " " << chisla[i][j][1] << "       ";
    //		}
    //		std::cout << '\n';
    //	}
    	//std::cout << chisla[3][0][3];
    	long long Left, Right;
    	for (long long i = 0; i < M; ++i) {
    		std::cin>>Left;
    		std::cin>>Right;
    		int step = deg[Right - Left + 1];
    		if (chisla[step][Left - 1][0] <= chisla[step][Right - pow(2, step)][0]){
    			//std::cout << "pizda";
    			long long index = chisla[step][Left - 1][1];
    			//std::cout << index<<std::endl;
    			long long deg_sleva = deg[index - Left + 1];
    			//std::cout << deg_sleva<<std::endl;
    			long long deg_sprava = deg[Right - index-1];
    			//std::cout << deg_sprava;
    			long long min_sleva = 9223372036854775;
    			long long min_sprava = 9223372036854775;
    			if (deg_sleva != -1) {
    				min_sleva = std::min(chisla[deg_sleva][Left - 1][0], chisla[deg_sleva][index - pow(2, deg_sleva)][0]);
    			}
    			if (deg_sprava != -1) {
    				min_sprava = std::min(chisla[deg_sprava][index + 1][0], chisla[deg_sprava][Right - pow(2, deg_sprava)][0]);
    			}
    			std::cout<<std::min(min_sleva,min_sprava)<<'\n';
    		}
    		else {
    			//std::cout << "xuy";
    			long long index = chisla[step][Right - pow(2, step)][1];
    			long long deg_sleva = deg[index - Left + 1];
    			long long deg_sprava = deg[Right - index-1];
    			long long min_sleva = 9223372036854775700;
    			long long min_sprava = 9223372036854775700;
    			if (deg_sleva != -1) {
    				min_sleva = std::min(chisla[deg_sleva][Left - 1][0], chisla[deg_sleva][index - pow(2, deg_sleva)][0]);
    			}
    			if (deg_sprava != -1) {
    				min_sprava = std::min(chisla[deg_sprava][index + 1][0], chisla[deg_sprava][Right - pow(2, deg_sprava)][0]);
    			}
    			std::cout << std::min(min_sleva, min_sprava)<<'\n';
    		}
    	}
    }
