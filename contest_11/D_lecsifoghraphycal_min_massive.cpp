        #include <iostream>
        #include <vector>
        #include <set>
         
        int main() {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(NULL);
            std::set<int> free_numbers;
            for (int i = 2; i <= 1500000; ++i) {
                free_numbers.insert(i);
            }
            int n;
            std::cin >> n;
            std::vector<int> input(n);
            std::vector<int> ans(n);
            std::vector<bool> used(1500000);
            for (int i = 0; i < n; ++i) {
                std::cin >> input[i];
            }
            std::vector<int> primes;
            std::vector<int> least_prime_dev(1500000);
            for (int i=0;i<1500000;++i){
                least_prime_dev[i]=i;
            }
            for (int i=2;i<1500000;++i){
                if (least_prime_dev[i]==i){
                    for (long long j=i;j*i<1500000;++j){
                        if (least_prime_dev[j*i]==j*i){
                            least_prime_dev[j*i]=i;
                        }
                    }
                }
            }
            int curr = input[0];
            ans[0] = input[0];
            while (curr!=1){
                if (used[least_prime_dev[curr]]==0){
                    for (int i = least_prime_dev[curr]; i<*(--free_numbers.end());i+=least_prime_dev[curr]){
                        free_numbers.erase(i);
                    }
                    used[least_prime_dev[curr]]=1;
                }
                curr/=least_prime_dev[curr];
            }
            for (int i=1;i<n;++i){
                if (free_numbers.count(input[i])){
                    ans[i]=input[i];
                    curr = input[i];
                    while (curr!=1){
                        if (used[least_prime_dev[curr]]==0){
                            for (int i = least_prime_dev[curr]; i<*(--free_numbers.end());i+=least_prime_dev[curr]){
                                free_numbers.erase(i);
                            }
                            used[least_prime_dev[curr]]=1;
                        }
                        curr/=least_prime_dev[curr];
                    }
                }
                else{
                    for (int new_val: free_numbers){
                        if (new_val>input[i]){
                            ans[i] = new_val;
                            curr = new_val;
                            while (curr!=1){
                                if (used[least_prime_dev[curr]]==0){
                                    for (int i = least_prime_dev[curr]; i<*(--free_numbers.end());i+=least_prime_dev[curr]){
                                        free_numbers.erase(i);
                                    }
                                    used[least_prime_dev[curr]]=1;
                                }
                                curr/=least_prime_dev[curr];
                            }
                            break;
                        }
                        
                    }
                    for (int k = i+1; k < n; ++k) {
                        ans[k] = *free_numbers.begin();
                        curr = ans[k];
                        while (curr!=1){
                            if (used[least_prime_dev[curr]]==0){
                                for (int i = least_prime_dev[curr]; i<*(--free_numbers.end());i+=least_prime_dev[curr]){
                                    free_numbers.erase(i);
                                }
                                used[least_prime_dev[curr]]=1;
                            }
                            curr/=least_prime_dev[curr];
                        }
                    }
                    break;
                }
            }
            for (int i=0;i<ans.size();++i){
                std::cout<<ans[i]<<" ";
            }
        }
