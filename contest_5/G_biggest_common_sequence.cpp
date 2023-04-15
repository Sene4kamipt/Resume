    #include <iostream>
    #include <vector>
    #include <algorithm>
    int main()
    {
    	int lengt_1, lengt_2;
    	std::cin >> lengt_1;
    	std::vector<int>vector_1;
    	std::vector<int>vector_2;
    	int value;
    	for (int i = 0; i < lengt_1; ++i) {
    		std::cin >> value;
    		vector_1.push_back(value);
    	}
    	std::cin >> lengt_2;
    	for (int i = 0; i < lengt_2; ++i) {
    		std::cin >> value;
    		vector_2.push_back(value);
    	}
    	std::vector<std::vector<int>> seq;
    	for (int i = 0; i < lengt_1; ++i) {
    		seq.push_back({});
    		for (int j = 0; j < lengt_2; ++j) {
    			seq[i].push_back(0);
    		}
    	}
    	for (int i = 0; i < lengt_1; ++i) {
    		for (int j = 0; j < lengt_2; ++j) {
    			seq[i][j] = std::max((j > 0 ? seq[i][j - 1] : 0), (i > 0 ? seq[i - 1][j] : 0));
    			if (vector_1[i] == vector_2[j]) {
    				seq[i][j] = std::max(seq[i][j], ((i!=0)&&(j!=0)?seq[i - 1][j - 1] + 1:1));
    			}
    		}
    	}
    	std::cout << seq[lengt_1-1][lengt_2-1];
    }
