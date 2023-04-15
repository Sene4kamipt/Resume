    #include <iostream>
    int64_t modul = 1'000'000'007;
     
    int64_t custom_pow(int64_t down, int64_t degree){
        int64_t ans = 1;
        if (degree>0){
            if (degree%2==0){
                ans = custom_pow(down,degree/2);
                ans=(ans*ans)%modul;
            }
            else{
                ans = custom_pow(down, (degree-1)/2);
                ans=(ans*ans)%modul;
                ans=(ans*down)%modul;
            }
        }
        //std::cout<<degree<<" "<<ans<<'\n';
        return ans;
    }
    int main(){
        int64_t a, b, c, d;
        std::cin>>a>>b>>c>>d;
        int64_t ans = 0;
        ans = (a*d+modul*modul)%modul;
        ans=(ans+b*c+modul*modul)%modul;
        ans=(ans*custom_pow((b*d+modul*modul)%modul, modul-2))%modul;
        //std::cout<<custom_pow(b*d, modul-2)<<'\n';
        std::cout<<ans%modul;
    }
