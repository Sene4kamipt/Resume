    #include <iostream>
    #include <string>
    #include <vector>
    #include <math.h>
     
    int64_t modul = 1000000007;
    int64_t hash_string(std::string& str, int64_t sz){
        int64_t hsh = 0;
        for (int64_t i=0;i<sz;++i){
            hsh=(hsh*28 + str[i]-'a')%modul;
        }
        return hsh;
    }
     
    int64_t powp(int64_t sz){
        int64_t ans=1;
        for (int64_t i=0; i<sz;++i){
            ans=(ans*28)%modul;
        }
        return ans;
    }
    int main(){
        std::string S, T;
        std::cin>>S>>T;
        int64_t popw = powp(T.size());
        if (S.size()<T.size()){
            return 0;
        }
        int64_t hash_T = hash_string(T, T.size());
        std::vector<int64_t> hashes_S(S.size());
        hashes_S[0] = S[0]-'a';
        for (int64_t i=1;i<S.size();++i){
            hashes_S[i] = (hashes_S[i-1]*28+ S[i]-'a')%modul;
        }
        if (hash_T == hashes_S[T.size()-1]){
            std::cout<<"0 ";
        }
        for (int64_t i = 0; i<S.size()-T.size(); ++i ){
            if(hash_T == (int64_t( (modul-hashes_S[i]) * popw) + hashes_S[i+T.size()] )%modul){
                std::cout<<i+1<<" ";
            }
        }
    }
