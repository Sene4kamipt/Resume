    #include <iostream>
    #include<vector>
    #include<iomanip>
    #include "cmath"
     
     
    struct Lamp{
        int x;
        int y;
        long double angle;
        Lamp() = default;
        Lamp(int x, int y, int angle_grad): x(x), y(y){
            angle = angle_grad * std::numbers::pi / 180;
        }
    };
     
    bool iszero(long double d){
        if(d <= 1e-8){
            return true;
        }
        return false;
    }
     
    long double how_far(Lamp lamp, long double start, long double finish){
        //если старт - начало освещаемой зоны, то где конец?
        long double x = start - lamp.x;
        long double y = -lamp.y;
     
        long double dx = x * cosl(lamp.angle) - y * sinl(lamp.angle);
        long double dy = x * sinl(lamp.angle) + y * cosl(lamp.angle);
     
        if(dy >= 0.0){
            return finish;
        }
     
        dx /= dy;
        return lamp.x - lamp.y * dx;
    }
     
    int main() {
       int n,a,b,c;
       long double l, r;
       std::cin>>n>>l>>r;
       std::vector<Lamp> lamps(n);
       for(int i = 0; i < n; ++i){
           std::cin>>a>>b>>c;
           lamps[i] = Lamp(a,b,c);
       }
       std::vector<long double> dp(1<<n, l);
       long double maxpoint= l;
       dp[0] = l;
       for(int i = 0; i < 1<<n; ++i){
           int k = i;
           for(int j = 0; j < n; ++j){
               if (k % 2 != 0){
                   k /= 2;
                   continue;
               }
               dp[i + (1<<j)] = std::max(dp[i + (1<<j)], how_far(lamps[j], dp[i], r));
               maxpoint = std::max(maxpoint, dp[i + (1<<j)]);
               if(maxpoint >= r){
                   std::cout<<r - l;
                   return 0;
               }
               k /= 2;
           }
       }
       if(iszero(maxpoint - l)){
           std::cout<<0;
           return 0;
       }
       std::cout<<std::setprecision(8)<<maxpoint - l;
    }
