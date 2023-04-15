        #include <iostream>
        #include <iomanip>
        #include <cmath>
        #include <vector>
        #include<string>
        #include <algorithm>
        #include <limits>
        #include <unordered_map>
        
        struct vector_geom
        {
            double x;
            double y;
            double operator *(const vector_geom& other){
                return this->x*other.x+this->y*other.y;
            }
            double operator /(const vector_geom& other){
                return this->x*other.y - this->y*other.x;
            }
            vector_geom(long long x, long long y): x(x), y(y){}
            double len(){
                return sqrt(x*x+y*y);
            }
            vector_geom operator +(const vector_geom& other){
                return vector_geom(x+other.x, y+other.y);
            }
        };
        
        struct dot{
            long long x;
            long long y;
            dot():x(0), y(0){}
            dot(long long x, long long y): x(x), y(y){}
            dot(const dot& d): x(d.x), y(d.y){}
            bool operator==(const dot& other){
                return (x==other.x)&&(y==other.y);
            } 
        };
        
        int main(){
            long long number_angles;
            long long number_dots;
            long long a,b;
            std::cin>>number_angles>>number_dots;
            long double ans, huyans;
            std::vector<dot> tangle(number_angles); 
            for (long long i=0;i<number_angles;++i){
                std::cin>>a>>b;
                tangle[i] = dot(a,b);
            }
            for (long long i=0;i<number_dots;++i){
                bool flag=false;
                ans=0.0;
                std::cin>>a>>b;
                for (long long j=0;j<number_angles;++j){
                    if (tangle[j]==dot(a,b)){
                        std::cout<<"BOUNDARY"<<'\n';
                        flag=1;
                        continue;
                    }
                }
                if (flag){
                    continue;
                }
                for (long long j=0; j<number_angles-1;++j){
                    huyans=std::asin(((tangle[j].x-a)*(tangle[j+1].y-b)-(tangle[j].y-b)*(tangle[j+1].x-a))/(sqrt((tangle[j].x-a)*(tangle[j].x-a)+(tangle[j].y-b)*(tangle[j].y-b))*sqrt((tangle[j+1].x-a)*(tangle[j+1].x-a)+(tangle[j+1].y-b)*(tangle[j+1].y-b))));
                    if (((tangle[j].x-a)*(tangle[j+1].y-b)-(tangle[j].y-b)*(tangle[j+1].x-a))==0){
                        flag = true;
                    }
                    if(huyans>0){
                        if ((tangle[j].x-a)*(tangle[j+1].x-a)+(tangle[j].y-b)*(tangle[j+1].y-b)<0){
                            ans+=acos(-1.0)-huyans;
                        }
                        else{
                            ans+=huyans;
                        }
                    }
                    if (huyans<0){
                        if ((tangle[j].x-a)*(tangle[j+1].x-a)+(tangle[j].y-b)*(tangle[j+1].y-b)<0){
                            ans+=-acos(-1.0)-huyans;
                        }
                        else{
                            ans+=huyans;
                        }
                    }
                }
                huyans=std::asin(((tangle[number_angles-1].x-a)*(tangle[0].y-b)-(tangle[number_angles-1].y-b)*(tangle[0].x-a))/(sqrt(((tangle[number_angles-1].x-a)*(tangle[number_angles-1].x-a)+(tangle[number_angles-1].y-b)*(tangle[number_angles-1].y-b)))*sqrt((tangle[0].x-a)*(tangle[0].x-a)+(tangle[0].y-b)*(tangle[0].y-b))));
                if(huyans>0){
                    if ((tangle[tangle.size()-1].x-a)*(tangle[0].x-a)+(tangle[tangle.size()-1].y-b)*(tangle[0].y-b)<0){
                        ans+=acos(-1.0)-huyans;
                    }
                    else{
                        ans+=huyans;
                    }
                }
                if(huyans<0){
                    if ((tangle[tangle.size()-1].x-a)*(tangle[0].x-a)+(tangle[tangle.size()-1].y-b)*(tangle[0].y-b)<0){
                        ans+=-acos(-1.0)-huyans;
                    }
                    else{
                        ans+=huyans;
                    }
                }
                if ((ans>2)&&(ans<4)){
                    std::cout<<"BOUNDARY"<<'\n';
                    continue;
                }
                if ((ans<-2)&&(ans>-4)){
                    std::cout<<"BOUNDARY"<<'\n';
                    continue;
                }
                if ((ans>4)){
                    std::cout<<"INSIDE"<<'\n';
                    continue;
                }
                if ((ans<-4)){
                    std::cout<<"INSIDE"<<'\n';
                    continue;
                }
                if ((ans>-2)&&(ans<2)){
                    std::cout<<"OUTSIDE"<<'\n';
                    continue;
                }
            }
        }
