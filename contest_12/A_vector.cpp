    #include <iostream>
    #include <cmath>
    #include <iomanip>
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
        vector_geom(int x, int y): x(x), y(y){}
        double len(){
            return sqrt(x*x+y*y);
        }
        vector_geom operator +(const vector_geom& other){
            return vector_geom(x+other.x, y+other.y);
        }
    };
     
     
    int main(){
        int x1, x2, y1, y2;
        std::cin>>x1>>y1>>x2>>y2;
        vector_geom first(x2-x1, y2-y1);
        std::cin>>x1>>y1>>x2>>y2;
        vector_geom second(x2-x1, y2-y1);
        std::cout<<std::setprecision(7)<< first.len()<<" "<<second.len()<<'\n';
        std::cout<<std::setprecision(7)<<(first+second).x<<" "<<(first+second).y<<'\n';
        std::cout<<std::setprecision(7)<<first*second<<" "<<first/second<<'\n';
        if (((first/second)/2)>0){
            std::cout<<std::setprecision(7)<<((first/second)/2);
        }
        else{
            std::cout<<std::setprecision(7)<<(-1)*((first/second)/2);
        }
    }
