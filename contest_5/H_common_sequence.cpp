    #include <iostream>
    #include <vector>
    #include <string>
    #include <algorithm>
     
    int main()
    {
        std::string str_1, str_2;
        std::cin >> str_1 >> str_2;
    	std::vector<std::vector<bool>> where_to_go_up;
    	std::vector<std::vector<bool>> where_to_go_left;
    	std::vector<short int> curr_seq;
    	std::vector<short int> prev_seq;
    	for (int i = 0; i < str_1.size(); ++i) {
    		where_to_go_up.push_back({});
    		where_to_go_left.push_back({});
    		for (int j = 0; j < str_2.size(); ++j) {
    			where_to_go_up[i].push_back(false);
    			where_to_go_left[i].push_back(false);
    		}
    	}
    	for (int i = 0; i < str_1.length(); ++i) {
    		for (int j = 0; j < str_2.length(); ++j) {
    			if ((j > 0 ? curr_seq[j - 1] : 0) > (i > 0 ? prev_seq[j] : 0)) {
    				where_to_go_left[i][j] = 1;
    				curr_seq.push_back(curr_seq[j - 1]);
    			}
    			else {
    				if (i > 0) {
    					where_to_go_up[i][j] = 1;
    					curr_seq.push_back(prev_seq[j]);
    				}
    				else {
    					where_to_go_up[i][j] = 0;
    					curr_seq.push_back(0);
    				}
    			}
    			if (str_1[i] == str_2[j]) {
    				if (curr_seq[j] < ((i != 0) && (j != 0) ? prev_seq[j - 1] + 1 : 1)) {
    					where_to_go_up[i][j] = 0;
    					where_to_go_left[i][j] = 0;
    					//std::cout << i << " " << j;
    					if ((i!= 0) && (j != 0)) {
    						curr_seq.pop_back();
    						curr_seq.push_back( prev_seq[j - 1] + 1);
    					}
    					else {
    						curr_seq.pop_back();
    						curr_seq.push_back(1);
    					}
    				}
    			}
    		}
    		prev_seq = {};
    		for (int j = 0; j < str_2.length(); ++j) {
    			prev_seq.push_back( curr_seq[j]);
    			//std::cout << curr_seq[j];
    		}
    		//std::cout << " ";
    		curr_seq={};
    	}
    	std::string ans="";
    	int k = str_1.length() - 1;
    	int q = str_2.length() - 1;
    	int i = prev_seq[q];
    	while (i>0) {
    		if ((where_to_go_up[k][q] == 0)&&(where_to_go_left[k][q]==0)) {
    			ans = str_1[k] + ans;
    			--k;
    			--i;
    			--q;
    		}
    		else {
    			if (where_to_go_left[k][q] == 1) {
    				--q;
    			}
    			else {
    				--k;
    			}
    		}
    	}
    	std::cout << ans;
     
    }
