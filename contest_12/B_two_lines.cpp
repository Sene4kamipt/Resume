    #include <iostream>
    #include <iomanip>
    #include <cmath>
    struct line
    {
        long double a;
        long double b;
        long double c;
        std::pair<long double, long double> cross(const line& other){
            std::pair<long double, long double> ans;
            long double det = a*other.b - other.a*b;
            long double det1 = -c*other.b+b*other.c;
            long double det2 = -a*other.c+c*other.a;
            ans.first = det1/det;
            ans.second = det2/det;
            return ans;
        }
        line(int a, int b, int c):a(a), b(b), c(c){}
    };
     
    int main(){
        int a, b, c;
        std::cin>>a>>b>>c;
        line first(a,b,c);
        std::cin>>a>>b>>c;
        line second(a,b,c);
        std::cout<<std::setprecision(7)<<-(first.b==0?-first.b:first.b)<<" "<<first.a<<'\n';
        std::cout<<std::setprecision(7)<<-(second.b==0?-second.b:second.b)<<" "<<second.a<<'\n';
        if (first.a*second.b == first.b*second.a){
            if (first.b!=0){
                if ((second.c+second.a+second.b*(-first.c-first.a)/first.b)/(second.a*second.a+second.b*second.b)>0){
                    std::cout<<std::setprecision(7)<<(second.c+second.a+second.b*(-first.c-first.a)/first.b)/sqrt(second.a*second.a+second.b*second.b);
                }
                else{
                    std::cout<<std::setprecision(7)<<-(second.c+second.a+second.b*(-first.c-first.a)/first.b)/sqrt(second.a*second.a+second.b*second.b);
                }
            }
            else{
                if((second.c+second.a*(-first.c)/first.a)/(second.a*second.a+second.b+second.b)>0){
                    std::cout<<std::setprecision(7)<<(second.c+second.a*(-first.c)/first.a)/sqrt(second.a*second.a+second.b+second.b);
                }
                else{
                    std::cout<<std::setprecision(7)<<-(second.c+second.a*(-first.c)/first.a)/sqrt(second.a*second.a+second.b+second.b);
                }
            }
        }
        else{
            std::pair<long double, long double> ans = first.cross(second);
            std::cout<<std::setprecision(7)<<ans.first<<" "<<ans.second<<'\n';
        }
    }


