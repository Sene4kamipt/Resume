    #include <iostream>
    #include <vector>
     
    int main(){
        int n;
        std::cin>>n;
        ++n;
        std::vector<int> least_prime_dev(n);
        for (int i=0;i<n;++i){
            least_prime_dev[i]=i;
        }
        for (int i=2;i<n;++i){
            if (least_prime_dev[i]==i){
                for (int j=2;j*i<n;++j){
                    if (least_prime_dev[j*i]==j*i){
                        least_prime_dev[j*i]=i;
                    }
                }
            }
        }
        int64_t ans =0;
        for (int i=4;i<n;++i){
            if (least_prime_dev[i]!=i){
                ans+=least_prime_dev[i];
            }
        }
        std::cout<<ans;
    }
