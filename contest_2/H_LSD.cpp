    #include <iostream>
    #include <vector>
     
    unsigned long long chisla1[300000];
    unsigned long long chisla2[300000];
     
    void LSD1(int stepen, long long N) {
    	unsigned long long Long_chisla[256] = {0};
    	for (long long i = 0; i < N; i++) {
    		Long_chisla[(chisla1[i] / ((long long)pow(256, stepen - 1))) % 256] += 1;
    		//for (long long j = 0; j < 256; ++j) {
    			//std::cout << Long_chisla[j];
    		//}
    		//std::cout << std::endl;
    	}
    	for (int i = 1; i < 256; i++) {
    		Long_chisla[i] += Long_chisla[i - 1];
    	}
    	for (long long i = N - 1; i > -1; --i) {
    		chisla2[Long_chisla[(chisla1[i] / (long long)pow(256, stepen - 1)) % 256] - 1] = chisla1[i];
    		//std::cout << (chisla1[i] / (long long)pow(256,stepen-1)) % 256 << std::endl;
    		Long_chisla[(chisla1[i] / (long long)pow(256, stepen - 1)) % 256] -= 1;
    		//for (long long i = 0; i < N; ++i) {
    			//std::cout << chisla2[i] << " ";
    		//}
    		//for (long long j = 0; j < 256; ++j) {
    			//std::cout << Long_chisla[j];
    		//}
    		//std::cout << std::endl;
    	}
    }
     
    void LSD2(int stepen, long long N) {
    	unsigned long long Long_chisla[256];
    	for (int i = 0; i < 256; i++) {
    		Long_chisla[i] = 0;
    	}
    	for (long long i = 0; i < N; i++) {
    		Long_chisla[(chisla2[i] / ((long long)pow(256, stepen - 1))) % 256] += 1;
    		//for (long long j = 0; j < 256; ++j) {
    			//std::cout << Long_chisla[j];
    		//}
    		//std::cout << std::endl;
    	}
    	for (int i = 1; i < 256; i++) {
    		Long_chisla[i] += Long_chisla[i - 1];
    	}
    	for (long long i = N - 1; i > -1; --i) {
    		chisla1[Long_chisla[(chisla2[i] / (long long)pow(256, stepen - 1)) % 256] - 1] = chisla2[i];
    		Long_chisla[(chisla2[i] / (long long)pow(256, stepen - 1)) % 256] -= 1;
    	}
    }
     
    int main() {
    	long long N;
    	std::cin >> N;
    	unsigned long long vedro;
    	for (long long i = 0; i < N; ++i) {
    		std::cin >> vedro;
    		chisla1[i] = vedro;
    	}
    	LSD1(1, N);
    	//for (long long i = 0; i < N; ++i) {
    		//std::cout << chisla2[i]<<" ";
    	//}
    	LSD2(2, N);
    	//for (long long i = 0; i < N; ++i) {
    		//std::cout << chisla1[i]<<" ";
    	//}
    	LSD1(3, N);
    	//for (long long i = 0; i < N; ++i) {
    		//std::cout << chisla2[i]<<" ";
    	//}
    	LSD2(4, N);
    	LSD1(5, N);
    	LSD2(6, N);
    	LSD1(7, N);
    	LSD2(8, N);
    	for (long long i = 0; i < N; ++i) {
    		std::cout << chisla1[i] << " ";
    	}
    }
