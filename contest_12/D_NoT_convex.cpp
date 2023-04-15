    #include <iostream>
     
    int64_t vec_product(int64_t x1, int64_t y1, int64_t x2, int64_t y2){
        return x1*y2-y1*x2;
    }
    int main(){
        int64_t n;
        std::cin>>n;
        if (n==3){
            for (int64_t i=0;i<6;++i){
                //std::cin>>n;
            }
            std::cout<<"YES";
            return 0;
        }
        std::pair<int64_t, int64_t> prev_prev_dot;
        std::pair<int64_t, int64_t> prev_dot;
        std::pair<int64_t, int64_t> curr_dot;
        std::pair<int64_t, int64_t> starting_dot;
        std::pair<int64_t, int64_t> after_starting_dot;
        std::cin>>prev_prev_dot.first>>prev_prev_dot.second;
        std::cin>>prev_dot.first>>prev_dot.second;
        std::cin>>curr_dot.first>>curr_dot.second;
        bool sign1 = vec_product(prev_dot.first-prev_prev_dot.first, prev_dot.second-prev_prev_dot.second, curr_dot.first-prev_prev_dot.first, curr_dot.second-prev_prev_dot.second)>=0;
        bool sign2 = vec_product(prev_dot.first-prev_prev_dot.first, prev_dot.second-prev_prev_dot.second, curr_dot.first-prev_prev_dot.first, curr_dot.second-prev_prev_dot.second)<=0;
        starting_dot=prev_prev_dot;
        after_starting_dot = prev_dot;
        prev_prev_dot=prev_dot;
        prev_dot=curr_dot;
        for(int64_t i=0; i<n-3;++i){
            std::cin>>curr_dot.first>>curr_dot.second;
            if (sign1==sign2){
                sign1 = vec_product(prev_dot.first-prev_prev_dot.first, prev_dot.second-prev_prev_dot.second, curr_dot.first-prev_prev_dot.first, curr_dot.second-prev_prev_dot.second)>=0;
                sign2 = vec_product(prev_dot.first-prev_prev_dot.first, prev_dot.second-prev_prev_dot.second, curr_dot.first-prev_prev_dot.first, curr_dot.second-prev_prev_dot.second)<=0;
            }
            if ((sign1==1)&&(sign2==0)){
                if ((vec_product(prev_dot.first-prev_prev_dot.first, prev_dot.second-prev_prev_dot.second, curr_dot.first-prev_prev_dot.first, curr_dot.second-prev_prev_dot.second)<0)){
                    std::cout<<"NO";
                    return 0;
                }
            }
            else{
                if ((sign1==0)&&(sign2==1)){
                    if ((vec_product(prev_dot.first-prev_prev_dot.first, prev_dot.second-prev_prev_dot.second, curr_dot.first-prev_prev_dot.first, curr_dot.second-prev_prev_dot.second)>0)){
                        std::cout<<"NO";
                        return 0;
                    }
                }
            }
            prev_prev_dot=prev_dot;
            prev_dot=curr_dot;
        }
        curr_dot=starting_dot;
        if (sign1==sign2){
            sign1 = vec_product(prev_dot.first-prev_prev_dot.first, prev_dot.second-prev_prev_dot.second, curr_dot.first-prev_prev_dot.first, curr_dot.second-prev_prev_dot.second)>=0;
            sign2 = vec_product(prev_dot.first-prev_prev_dot.first, prev_dot.second-prev_prev_dot.second, curr_dot.first-prev_prev_dot.first, curr_dot.second-prev_prev_dot.second)<=0;
        }
        if ((sign1==1)&&(sign2==0)){
            if ((sign1!=vec_product(prev_dot.first-prev_prev_dot.first, prev_dot.second-prev_prev_dot.second, curr_dot.first-prev_prev_dot.first, curr_dot.second-prev_prev_dot.second)>=0)){
                std::cout<<"NO";
                return 0;
            }
        }
        else{
            if ((sign1==0)&&(sign2==1)){
                if ((sign2!=vec_product(prev_dot.first-prev_prev_dot.first, prev_dot.second-prev_prev_dot.second, curr_dot.first-prev_prev_dot.first, curr_dot.second-prev_prev_dot.second)<=0)){
                    std::cout<<"NO";
                    return 0;
                }
            }
        }
        prev_prev_dot=prev_dot;
        prev_dot=curr_dot;
        curr_dot=after_starting_dot;
        if (sign1==sign2){
            sign1 = vec_product(prev_dot.first-prev_prev_dot.first, prev_dot.second-prev_prev_dot.second, curr_dot.first-prev_prev_dot.first, curr_dot.second-prev_prev_dot.second)>=0;
            sign2 = vec_product(prev_dot.first-prev_prev_dot.first, prev_dot.second-prev_prev_dot.second, curr_dot.first-prev_prev_dot.first, curr_dot.second-prev_prev_dot.second)<=0;
        }
        if ((sign1==1)&&(sign2==0)){
            if ((vec_product(prev_dot.first-prev_prev_dot.first, prev_dot.second-prev_prev_dot.second, curr_dot.first-prev_prev_dot.first, curr_dot.second-prev_prev_dot.second)<0)){
                std::cout<<"NO";
                return 0;
            }
        }
        else{
            if ((sign1==0)&&(sign2==1)){
                if ((vec_product(prev_dot.first-prev_prev_dot.first, prev_dot.second-prev_prev_dot.second, curr_dot.first-prev_prev_dot.first, curr_dot.second-prev_prev_dot.second)>0)){
                    std::cout<<"NO";
                    return 0;
                }
            }
        }
        if (sign1==1&&sign2==1){
            std::cout<<"NO";
            return 0;
        }
        std::cout<<"YES";
    }
