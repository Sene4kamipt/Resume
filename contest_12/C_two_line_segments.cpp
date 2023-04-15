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
            int i =0;
            long double det = a*other.b - other.a*b;
            if (det==0){
                throw i;
            }
            long double det1 = -c*other.b+b*other.c;
            long double det2 = -a*other.c+c*other.a;
            ans.first = det1/det;
            ans.second = det2/det;
            return ans;
        }
        line(int a, int b, int c):a(a), b(b), c(c){}
    };
     
    bool check_dot(std::pair<long double, long double> ans, int x1, int y1, int x2, int y2){
        if ((ans.first<=x1)&&(ans.first>=x2)&&(ans.second<=y1)&&(ans.second>=y2)){
            return 1;
        }
        if ((ans.first>=x1)&&(ans.first<=x2)&&(ans.second>=y1)&&(ans.second<=y2)){
            return 1;
        }
        if ((ans.first>=x1)&&(ans.first<=x2)&&(ans.second<=y1)&&(ans.second>=y2)){
            return 1;
        }
        if ((ans.first<=x1)&&(ans.first>=x2)&&(ans.second>=y1)&&(ans.second<=y2)){
            return 1;
        }
        return 0;
    }
     
    int main(){
        int a1,b1,c1,d1;
        std::cin>>a1>>b1>>c1>>d1;
        line first(d1-b1,a1-c1, c1*b1-d1*a1);
        int a,b,c,d;
        std::cin>>a>>b>>c>>d;
        line second(d-b,a-c, c*b-d*a);
        try{
            std::pair<long double, long double> ans = first.cross(second);
            if (check_dot(ans, a1,b1,c1,d1)&&check_dot(ans,a,b,c,d)){
                std::cout<<"YES";
                return 0;
            }
            else{
                std::cout<<"NO";
                return 0;
            }
        }
        catch(...){
            if (first.a*second.c == first.c*second.a){
                if ((check_dot(std::pair<long double, long double>(a1,b1),a,b,c,d))||(check_dot(std::pair<long double, long double>(c1,d1),a,b,c,d))){
                    std::cout<<"YES";
                    return 0;
                }
                if ((check_dot(std::pair<long double, long double>(a,b),a1,b1,c1,d1))||(check_dot(std::pair<long double, long double>(c,d),a1,b1,c1,d1))){
                    std::cout<<"YES";
                    return 0;
                }
                else{
                    std::cout<<"NO";
                    return 0;
                }
            }
            else{
                std::cout<<"NO";
                return 0;
            }
        }
    }
