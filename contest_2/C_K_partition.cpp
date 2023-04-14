    #include <vector>
    #include <iostream>
     
    void partition(long long &L_border,long long &R_border,std::vector<long long> &chisla, long long &partition_el,long long &Bol_border,long long &Ravn_border) {
    	Ravn_border = L_border;
    	Bol_border = L_border;
    	long long vedro_dlya_bol;
    	//std::cout << partition_el << std::endl;
    	long long vedro_dlya_ravn;
    	for (long long i = L_border; i < R_border+1; ++i) {
    		if (chisla[i] < partition_el) {
    				vedro_dlya_ravn = chisla[Ravn_border];
    				chisla[Ravn_border] = chisla[i];
    				if (Ravn_border == Bol_border) {
    					Ravn_border += 1;
    					Bol_border += 1;
    					chisla[i] = vedro_dlya_ravn;
    				}
    				else {
    					if (Bol_border != i) {
    						//std::cout << vedro_dlya_ravn << " " << Bol_border;
    						vedro_dlya_bol = chisla[Bol_border];
    						chisla[Bol_border] = vedro_dlya_ravn;
    						chisla[i] = vedro_dlya_bol;
    						Ravn_border += 1;
    						Bol_border += 1;
    					}
    					else {
    						chisla[Bol_border] = vedro_dlya_ravn;
    						Ravn_border += 1;
    						Bol_border += 1;
    					}
    			}
    		}
    		else {
    			if (chisla[i] == partition_el) {
    				vedro_dlya_bol = chisla[Bol_border];
    				chisla[Bol_border] = chisla[i];
    				chisla[i] = vedro_dlya_bol;
    				Bol_border += 1;
    			}
    		}
    		//for (int i = 0; i < chisla.size(); ++i) {
    			//std::cout << chisla[i] << " ";
    		//}
    		//std::cout << std::endl;
    	}
    }
     
    long long QuickSelect(std::vector<long long>& chisla, long long &L_border, long long &R_border, long long &K) {
    	long long Bol_border;
    	
    	//std::cout << L_border << " " << R_border<<std::endl;
    	long long Ravn_border;
    	if (L_border == R_border) {
    		return chisla[R_border];
    	}
    	long long partition_el = chisla[(L_border + R_border) / 2];
    	partition(L_border,R_border,chisla,partition_el,Bol_border,Ravn_border);
    	//for (int i = 0; i < chisla.size(); ++i) {
    		//std::cout << chisla[i] << " ";
    	//}
    	//std::cout << std::endl;
    	//std::cout << Bol_border << " " << Ravn_border << "!" << std::endl;
    	if (K < Ravn_border) {
    		R_border = Ravn_border-1;
    		return QuickSelect(chisla, L_border, R_border, K);
    	}
    	if (K < Bol_border) {
    		return chisla[Ravn_border];
    	}
    	L_border = Bol_border;
    	return QuickSelect(chisla, L_border, R_border, K);
    }
     
    int main()
    {
    	long long N;
    	long long K;
    	std::cin >> N >> K;
    	std::vector <long long> chisla;
    	long long dlya_vvoda;
    	long long L_border = 0;
    	long long R_border = N - 1;
    	for (long long i = 0; i < N; i++) {
    		std::cin >> dlya_vvoda;
    		chisla.push_back(dlya_vvoda);
    	}
    	std::cout << QuickSelect(chisla, L_border, R_border, K);
    }
     
