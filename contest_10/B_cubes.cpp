    #include <iostream>
    #include <vector>
    #include <algorithm>
     
    int main(){
        int64_t number_of_colors, number_of_cubes, color;
        std::cin>>number_of_cubes>>number_of_colors;
        std::vector<int64_t> palindrom_length(number_of_cubes+1);
        std::vector<int64_t> cubes(number_of_cubes);
        for (int64_t i=0; i<number_of_cubes; ++i){
            std::cin>>color;
            cubes[i]=color;
        }
        palindrom_length[0]=0;
        int64_t l=0; int64_t r =-1;
        for (int64_t i=1; i<number_of_cubes+1;++i){
            if (r-i>=0){
                palindrom_length[i] = std::min(r-i,palindrom_length[r+l-i]);
            }
            //std::cout<<2*i-r<<" "<<r+1<<" "<<'\n';
            while ((i - palindrom_length[i]>=0)&&(i+palindrom_length[i]<=number_of_cubes)&&(cubes[i - palindrom_length[i]-1]==cubes[i+palindrom_length[i]])){
                ++palindrom_length[i];
            }
            if (i+palindrom_length[i]>r){
                r=i+palindrom_length[i]; l=i-palindrom_length[i];
            }
            //std::cout<<r<<" "<<l<<" "<<i<<" "<<palindrom_length[i]<<'\n';
        }
        //for (int i=0;i<palindrom_length.size();++i){
          //  std::cout<<palindrom_length[i]<<" ";
        //}
        for(int64_t i =number_of_cubes;i>=0;--i){
            if (palindrom_length[i]==i){
                std::cout<<number_of_cubes-i<<" ";
            }
        }
    }
