#include <iostream>
#include "cmath"
#include<vector>
 
class Dot{
public:
    int64_t x;
    int64_t y;
    Dot(){
        x = 0;
        y = 0;
    }
    Dot(int64_t x, int64_t y): x(x), y(y) {};
};
bool operator==(const Dot& first, const Dot& second) {
    return (first.x == second.x) && (first.y == second.y);
}
bool operator<(const Dot& first, const Dot& second){
    if(first.x < second.x){
        return true;
    }
    if(first.x == second.x && first.y <= second.y){
        return true;
    }
    return false;
}
class Segment{
public:
    Dot a;
    Dot b;
    Segment() = default;
    Segment(Dot a, Dot b): a(a), b(b) {};
};
class Line{
public:
    int64_t a;
    int64_t b;
    int64_t c;
    Line(){
        a = 0;
        b = 0;
        c = 0;
    }
    Line(int64_t a, int64_t b, int64_t c): a(a), b(b), c(c){};
};
 
Line make_line(const Segment& s){
    int64_t A, B, C;
    A = s.a.y - s.b.y;
    B = s.b.x - s.a.x;
    C = s.a.x * s.b.y - s.b.x * s.a.y;
    if(B < 0){
        A *= -1;
        B *= -1;
        C *= -1;
    }
    if(B == 0 && A > 0){
        A *= -1;
        C *= -1;
    }
    return {A, B, C};
}
 
int64_t dot_line_mult(Line line, Dot dot){
    return line.a * dot.x + line.b * dot.y + line.c;
}
 
Dot operator-(const Dot& first, const Dot& second) {
    return {first.x - second.x,   first.y - second.y};
}
Dot operator+(const Dot& first, const Dot& second){
    return {first.x + second.x, first.y + second.y};
}
double len(Dot& d){
    return sqrt(d.x * d.x + d.y * d.y);
}
double vect(Dot first, Dot second){
    return first.x * second.y - first.y * second.x;
}
double scal(Dot first, Dot second){
    return first.x * second.x + first.y * second.y;
}
 
int find_the_most_left_and_down(std::vector<Dot>& points){
    Dot answer_point = points[0];
    int answer_index = 0;
    for(int i = 1; i < points.size(); ++i){
        if(points[i].x < answer_point.x ||
            points[i].x == answer_point.x && points[i].y < answer_point.y){
            answer_point = points[i];
            answer_index = i;
        }
    }
    return answer_index;
}
 
std::vector<Dot> Minkovsky_sum(std::vector<Dot>& first, std::vector<Dot>& second){
    int n1 = first.size();
    int n2 = second.size();
    int cur1 = find_the_most_left_and_down(first);
    int cur2 = find_the_most_left_and_down(second);
    int start1 = cur1, start2 = cur2;
    std::vector<Dot> answer;
    answer.push_back(first[cur1] + second[cur2]);
    while(true){
        int a1 = cur1, b1 = (cur1 + 1) %  n1;
        int a2 = cur2, b2 = (cur2 + 1) % n2;
        Dot side1 = first[b1] - first[a1];
        Dot side2 = second[b2] - second[a2];
        if(vect(side1, side2) >= 0){
            answer.push_back(answer[answer.size() - 1] + side1);
            cur1 = b1;
        } else {
            answer.push_back(answer[answer.size() - 1] + side2);
            cur2 = b2;
        }
//        if((cur1 == start1) && (cur2 == start2)){
//            break;
//        }
          if(answer[answer.size() - 1] == answer[0]){
              answer.pop_back();
              break;
          }
    }
    return answer;
}
 
bool dot_inside(std::vector<Dot>& polygon, Dot dot){
    //бинпоиском находим между какими лучами она лежит
    //точки в порядке обхода против часовой стрелки
    //нулевая точка - самая левая и нижняя
    int n = polygon.size();
    //сначала проверяем что точка вообще в угле n-1 0 1
    Dot vectup = polygon[n-1] - polygon[0];
    Dot vectdown = polygon[1] - polygon[0];
    Dot curvect = dot - polygon[0];
 
    if(vect(curvect, vectup) < 0){
        return false;
    }
    if(vect(curvect, vectdown) > 0){
        return false;
    }
 
    //теперь точка точно лежит в нужном большом угле
    //ищем в каком маленьком угле она лежит
 
    int l = 1, r = n-1;
    while(r - l > 1){
        int m = (r + l) / 2;
        Dot midvect = polygon[m] - polygon[0];
        if(vect(curvect, midvect) >= 0){
            r = m;
        } else {
            l = m;
        }
    }
     //точка в угле r 0 l где r = l + 1
     Dot side1 = polygon[r] - polygon[l];
     Dot side2 = polygon[0] - polygon[l];
     Dot to_check = dot - polygon[l];
 
     if(vect(to_check, side1) > 0){
         return false;
     }
    if(vect(to_check, side2) < 0){
        return false;
    }
 
     return true;
}
 
int main() {
    int size1, size2, size3;
 
    std::cin>>size1;
    std::vector<Dot> points1 (size1);
    for(int i = 0; i < size1; ++i){
        std::cin>>points1[i].x>>points1[i].y;
    }
 
    std::cin>>size2;
    std::vector<Dot> points2 (size2);
    for(int i = 0; i < size2; ++i){
        std::cin>>points2[i].x>>points2[i].y;
    }
 
    std::cin>>size3;
    std::vector<Dot> points3 (size3);
    for(int i = 0; i < size3; ++i){
        std::cin>>points3[i].x>>points3[i].y;
    }
 
    std::vector<Dot> points1and2 = Minkovsky_sum(points1, points2);
    std::vector<Dot> sum = Minkovsky_sum(points1and2, points3);
 
    //убираем точки которые подряд идут на одной прямой
    std::vector<Dot> sum_correct;
    sum_correct.push_back(sum[0]);
    sum_correct.push_back(sum[1]);
    int cur_size = 2;
    for(int i = 2; i < sum.size(); ++i){
        Dot side1 = sum[i-1] - sum[i-2];
        Dot side2 = sum[i] - sum[i-1];
        if(vect(side1, side2) == 0){
            sum_correct.pop_back();
        }
        sum_correct.push_back(sum[i]);
    }
    Dot side1 = sum[sum.size() - 1] - sum[sum.size() - 2];
    Dot side2 = sum[0] - sum[sum.size() - 1];
    if(vect(side1, side2) == 0){
        sum_correct.pop_back();
    }
 
//    for(int i = 0; i < sum_correct.size(); ++i){
//        std::cout<<sum_correct[i].x<<' '<<sum_correct[i].y<<'\n';
//    }
 
    int churches_num;
    std::cin>>churches_num;
    Dot church;
    for(int i = 0; i < churches_num; ++i){
        std::cin>>church.x>>church.y;
        church.x *= 3;
        church.y *= 3;
        if(dot_inside(sum_correct, church)){
            std::cout<<"YES"<<'\n';
        } else {
            std::cout<<"NO"<<'\n';
        }
    }
 
