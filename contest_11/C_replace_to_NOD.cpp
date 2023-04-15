    #include <iostream>
    #include <vector>
    #include <numeric>
     
    int main(){
        int n;
        std::cin>>n;
        std::vector<int> numbers(n);
        int flag_if_1 = false;
        for (int i=0;i<n;++i){
            std::cin>>numbers[i];
            if (numbers[i]==1){
                ++flag_if_1;
            }
        }
        if (flag_if_1){
            std::cout<<n-flag_if_1;
            return 0;
        }
        int prev_nod=0;
        bool flag = false;
        int answer=INT32_MAX;
        for (int i=0;i<n;++i){
            for (int j=i+1;j<n;++j){
                if (i==j-1){
                    prev_nod = std::gcd(numbers[i],numbers[j]);
                    if (prev_nod==1){
                        answer = std::min(answer, n);
                        flag = true;
                    }
                }
                else{
                    prev_nod = std::gcd(prev_nod, numbers[j]);
                    if (prev_nod==1){
                        answer = std::min(answer, j-i+n-1);
                        flag= true;
                    }
                }
            }
        }
        if (flag ==true){
            std::cout<<answer;
        }
        else{
            std::cout<<"-1";
        }
     
    }
