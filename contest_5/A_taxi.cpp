    #include <vector>
    #include <iostream>
    #include <algorithm>
     
    struct Human {
    public:
    	bool gender;
    	std::string name;
    	int kilometers;
    };
     
    struct Curr_taxi
    {
    	std::vector<int> last_taxi;
    	long long summ_of_money;
    	int number_of_taxis;
    };
     
    bool comp(Human human1, Human human2) {
    	return human1.kilometers > human2.kilometers;
    }
     
     
     
    int main()
    {
    	Curr_taxi anti_taxi{ {},LLONG_MAX - 1000000000000,0 };
    	int number_man, number_woman;
    	std::cin >> number_man;
    	std::vector<Human> people;
    	std::string input_name;
    	int input_kilometers;
    	for (int i = 0; i < number_man; ++i) {
    		std::cin >> input_name >> input_kilometers;
    		people.push_back(Human{ 0, input_name, input_kilometers });
    	}
    	std::sort(people.begin(), people.end(), comp);
    	std::cin >> number_woman;
    	for (int i = 0; i < number_woman; ++i) {
    		std::cin >> input_name >> input_kilometers;
    		people.push_back(Human{ 1, input_name, input_kilometers });
    	}
    	std::sort(people.begin()+number_man, people.end(), comp);
    	std::vector<std::vector<Curr_taxi>> summs_of_taxis;
    	for (int i = 0; i < number_man + 1; ++i) {
    		summs_of_taxis.push_back({});
    		for (int j = 0; j < number_woman + 1; ++j) {
    			if (i == 0) {
    				summs_of_taxis[i].push_back(Curr_taxi{ {},0,0 });
    			}
    			else { summs_of_taxis[i].push_back(anti_taxi); }
    		}
    	}
    	for (int i = 0; i <= number_woman; ++i) {
    		for (int j = 1; j <= number_man; ++j) {
    			if (3 * j >= i) {
    				if (((j >= 2) || (i == 0)) && (summs_of_taxis[j][i].summ_of_money > summs_of_taxis[j - 1][i].summ_of_money + people[j - 1].kilometers)) {
    					summs_of_taxis[j][i].summ_of_money = summs_of_taxis[j - 1][i].summ_of_money + people[j - 1].kilometers;
    					summs_of_taxis[j][i].last_taxi = { j - 1 };
    					summs_of_taxis[j][i].number_of_taxis = summs_of_taxis[j - 1][i].number_of_taxis + 1;
    				}
    				if (((j >= 2) && (i > 1) || (i == 1)) && (summs_of_taxis[j][i].summ_of_money > summs_of_taxis[j - 1][i - 1].summ_of_money + std::max(people[number_man +i - 1].kilometers, people[j - 1].kilometers))) {
    					summs_of_taxis[j][i].summ_of_money = summs_of_taxis[j - 1][i - 1].summ_of_money + std::max(people[i - 1 + number_man].kilometers, people[j - 1].kilometers);
    					summs_of_taxis[j][i].last_taxi = { j - 1, i - 1+number_man };
    					summs_of_taxis[j][i].number_of_taxis = summs_of_taxis[j - 1][i - 1].number_of_taxis + 1;
    				}
    				if (((i > 2) && (j >= 2) || (i == 2)) && (summs_of_taxis[j][i].summ_of_money > summs_of_taxis[j - 1][i - 2].summ_of_money + std::max(people[i - 2+number_man].kilometers, people[j - 1].kilometers))) {
    					summs_of_taxis[j][i].summ_of_money = summs_of_taxis[j - 1][i - 2].summ_of_money + std::max(people[i - 2+number_man].kilometers, people[j - 1].kilometers);
    					summs_of_taxis[j][i].last_taxi = { j - 1,i - 1+number_man,i - 2+number_man };
    					summs_of_taxis[j][i].number_of_taxis = summs_of_taxis[j - 1][i - 2].number_of_taxis + 1;
    				}
    				if (((i > 3) && (j >= 2) || (i == 3)) && (summs_of_taxis[j][i].summ_of_money > summs_of_taxis[j - 1][i - 3].summ_of_money + std::max(people[i - 3+number_man].kilometers, people[j - 1].kilometers))) {
    					summs_of_taxis[j][i].summ_of_money = summs_of_taxis[j - 1][i - 3].summ_of_money + std::max(people[i - 3+number_man].kilometers, people[j - 1].kilometers);
    					summs_of_taxis[j][i].last_taxi = { j - 1,i - 1+number_man,i - 2+number_man,i - 3+number_man };
    					summs_of_taxis[j][i].number_of_taxis = summs_of_taxis[j - 1][i - 3].number_of_taxis + 1;
    				}
    				if (((j >= 3) || ((i == 0) && (j == 2))) && (summs_of_taxis[j][i].summ_of_money > summs_of_taxis[j - 2][i].summ_of_money + people[j - 2].kilometers)) {
    					summs_of_taxis[j][i].summ_of_money = summs_of_taxis[j - 2][i].summ_of_money + people[j - 2].kilometers;
    					summs_of_taxis[j][i].last_taxi = { j - 2,j - 1 };
    					summs_of_taxis[j][i].number_of_taxis = summs_of_taxis[j - 2][i].number_of_taxis + 1;
    				}
    				if (((i == 1) && (j == 2) || (i>=1)&&(j >= 3)) && (summs_of_taxis[j][i].summ_of_money > summs_of_taxis[j - 2][i - 1].summ_of_money + std::max(people[i - 1+number_man].kilometers, people[j - 2].kilometers))) {
    					summs_of_taxis[j][i].summ_of_money = summs_of_taxis[j - 2][i - 1].summ_of_money + std::max(people[i - 1+number_man].kilometers, people[j - 2].kilometers);
    					summs_of_taxis[j][i].last_taxi = { j - 2,j - 1,i - 1+number_man };
    					summs_of_taxis[j][i].number_of_taxis = summs_of_taxis[j - 2][i - 1].number_of_taxis + 1;
    				}
    				if (((i == 2) && (j == 2) || (i>=2)&&(j >= 3)) && (summs_of_taxis[j][i].summ_of_money > summs_of_taxis[j - 2][i - 2].summ_of_money + std::max(people[i - 2+number_man].kilometers, people[j - 2].kilometers))) {
    					summs_of_taxis[j][i].summ_of_money = summs_of_taxis[j - 2][i - 2].summ_of_money + std::max(people[i - 2+number_man].kilometers, people[j - 2].kilometers);
    					summs_of_taxis[j][i].last_taxi = { j - 2,j - 1,i - 2+number_man,i - 1+number_man };
    					summs_of_taxis[j][i].number_of_taxis = summs_of_taxis[j - 2][i - 2].number_of_taxis + 1;
    				}
    				if (((j >= 4) || ((i == 0) && (j == 3))) && (summs_of_taxis[j][i].summ_of_money > summs_of_taxis[j - 3][i].summ_of_money + people[j - 3].kilometers)) {
    					summs_of_taxis[j][i].summ_of_money = summs_of_taxis[j - 3][i].summ_of_money + people[j - 3].kilometers;
    					summs_of_taxis[j][i].last_taxi = { j - 2,j - 1,j - 3 };
    					summs_of_taxis[j][i].number_of_taxis = summs_of_taxis[j - 3][i].number_of_taxis + 1;
    				}
    				if (((i == 1) && (j == 3) || (i>=1)&&(j >= 4)) && (summs_of_taxis[j][i].summ_of_money > summs_of_taxis[j - 3][i - 1].summ_of_money + std::max(people[i - 1+number_man].kilometers, people[j - 3].kilometers))) {
    					summs_of_taxis[j][i].summ_of_money = summs_of_taxis[j - 3][i - 1].summ_of_money + std::max(people[i - 1+number_man].kilometers, people[j - 3].kilometers);
    					summs_of_taxis[j][i].last_taxi = { j - 2,j - 1,i - 1+number_man,j - 3 };
    					summs_of_taxis[j][i].number_of_taxis = summs_of_taxis[j - 3][i - 1].number_of_taxis + 1;
    				}
    				if (((j >= 5) || ((i == 0) && (j >= 4))) && (summs_of_taxis[j][i].summ_of_money > summs_of_taxis[j - 4][i].summ_of_money + people[j - 4].kilometers)) {
    					summs_of_taxis[j][i].summ_of_money = summs_of_taxis[j - 4][i].summ_of_money + people[j - 4].kilometers;
    					summs_of_taxis[j][i].last_taxi = { j - 2,j - 1,j - 3,j - 4 };
    					summs_of_taxis[j][i].number_of_taxis = summs_of_taxis[j - 4][i].number_of_taxis + 1;
    				}
    			}
    		}
    	}
    	//for (int i = 0; i <= number_man; ++i) {
    		//for (int j = 0; j <= number_woman; ++j) {
    			//std::cout << summs_of_taxis[i][j].summ_of_money<<" ";
    		//}
    		//std::cout << std::endl;
    	//}
    	std::cout << summs_of_taxis[number_man][number_woman].summ_of_money << '\n';
    	std::cout << summs_of_taxis[number_man][number_woman].number_of_taxis << '\n';
    	int i = 1;
    	int prev;
    	char n_man, n_wom;
    	while ((number_man > 0) || (number_woman > 0)) {
    		std::cout << "Taxi " << i << ":";
    		n_man = 0;
    		n_wom = 0;
    		for (int l = 0; l < summs_of_taxis[number_man][number_woman].last_taxi.size(); ++l) {
    			if (l < int(summs_of_taxis[number_man][number_woman].last_taxi.size()) - 2) {
    				std::cout << " " << people[summs_of_taxis[number_man][number_woman].last_taxi[l]].name << ",";
    				//std::cout << l << " " << summs_of_taxis[number_man][number_woman].last_taxi.size() - 2;
    			}
    			if (l == int(summs_of_taxis[number_man][number_woman].last_taxi.size()) - 2) {
    				std::cout << " " << people[summs_of_taxis[number_man][number_woman].last_taxi[l]].name << " and";
    			}
    			if (l == int(summs_of_taxis[number_man][number_woman].last_taxi.size()) - 1) {
    				std::cout << " " << people[summs_of_taxis[number_man][number_woman].last_taxi[l]].name << ".";
    			}
    			if (summs_of_taxis[number_man][number_woman].last_taxi[l]>=number_man)
    			{
    				n_wom += 1;
    			}
    			else {
    				n_man += 1;
    			}
    		}
    		std::cout << '\n';
    		i += 1;
    		prev = number_man;
    		number_man -=n_man;
    		number_woman -= n_wom;
    	}
    }
