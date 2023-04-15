    #include <iostream>
    #include "cmath"
    #include<vector>
     
    int64_t MODULO = 1'000'000'007;
     
    class Dot{
    public:
         double x;
         double y;
        Dot(){
            x = 0;
            y = 0;
        }
        Dot(double x, double y): x(x), y(y) {};
        bool operator==(Dot other) const{
            return (x == other.x && y == other.y);
        }
        bool operator!=(Dot other) const{
            return x != other.x || y != other.y;
        }
    };
     
    class Segment{
    public:
        Dot a;
        Dot b;
        Segment() = default;
        Segment(Dot a, Dot b): a(a), b(b) {};
    };
     
    class Line{
    public:
         double a;
         double b;
         double c;
        Line() = default;
        Line(double a, double b, double c): a(a), b(b), c(c){};
    };
     
    bool operator<(const Dot& first, const Dot& second){
        if(first.x < second.x){
            return true;
        }
        if((first.x == second.x) && (first.y < second.y)){
            return true;
        }
        return false;
    }
     
    Dot operator-(const Dot& first, const Dot& second) {
        return {second.x - first.x, second.y - first.y};
    }
     
    bool dot_in_segment(Dot& a, Dot & b, Dot& x){
        //возможно совпадает с концами
        if (x.x < std::min(a.x , b.x) || x.x > std::max(a.x, b.x)){
            return false;
        }
        if (x.y < std::min(a.y , b.y) || x.y > std::max(a.y, b.y)){
            return false;
        }
        Dot p = a - x;
        Dot q = b - x;
        if(p.x * q.y - p.y * q.x == 0){
            return true;
        } else {
            return false;
        }
    }
    bool dot_in_segment_internal(Dot dot, Segment segment){
        if(!dot_in_segment(segment.a, segment.b, dot)){
            return false;
        }
        if(segment.a == dot || segment.b == dot){
            return false;
        }
        return true;
    }
     
    Line make_line(const Segment& s){
         double A, B, C;
        A = s.a.y - s.b.y;
        B = s.b.x - s.a.x;
        C = s.a.x * s.b.y - s.b.x * s.a.y;
        return {A, B, C};
    }
     
    long double vect(Dot first, Dot second){
        return first.x * second.y - first.y * second.x;
    }
    long double scal(Dot first, Dot second){
        return first.x * second.x + first.y * second.y;
    }
      double dot_line_mult(Line line, Dot dot){
        return line.a * dot.x + line.b * dot.y + line.c;
    }
     
    bool segment_intersect(Segment& first, Segment& second){
        //пересекаются ли отрезки
        //пересечение по общей вершине не считается
        //но если вершина лежит на отрезке но не совпадает с его концом то считается
     
        //сначала проверки на то что вершина одного из отрезков лежит внутри другого отрезка
        if(dot_in_segment_internal(first.a, second) ||
                dot_in_segment_internal(first.b, second) ||
                dot_in_segment_internal(second.a, first) ||
                dot_in_segment_internal(second.b, first)){
            return true;
        }
     
        //теперь осталось проверить пересекаются ли по внутренности
        //для этого достаточно проверить что вершины одного отрезка лежат по разные стороны
        //от прямой на которой лежит другой отрезок
        //и это должно быть верно для обоих отрезков
        Line line1 = make_line(first);
        Line line2 = make_line(second);
         double mult_1_1 = dot_line_mult(line1, second.a);
         double mult_1_2 = dot_line_mult(line1, second.b);
         double mult_2_1 = dot_line_mult(line2, first.a);
         double mult_2_2 = dot_line_mult(line2, first.b);
        if(mult_1_1 * mult_1_2 >= 0){
            return false;
        }
        if(mult_2_1 * mult_2_2 >= 0) {
            return false;
        }
        return true;
    }
     
    bool is_diagonal(int n, std::vector<Dot>& points, std::vector<Segment>& sides, int first, int second){
        //если этот отрезок пересекается с какой то стороной многоугольника то это не диагональ
        //кроме случая когда у них общая вершина
        //для этого как раз есть функция
     
        //отдельно проверим не является ли это стороной
        if(first == 1 && second == n || first == n && second == 1 || first == second - 1 || first == second + 1){
            return true;
        }
        for (int k = 1; k <= n; ++k){
            Segment cur_seg = Segment(points[first], points[second]);
            if(segment_intersect(sides[k], cur_seg)){
                return false;
            }
        }
        //теперь эта диагональ не пересекает стороны значит либо полностью лежит внутри
        //либо полностью лежит снаружи
        //достаточно проверить что ее середина лежит внутри многоугольника, такую задачу мы уже решали
     
        long double angle_sum = 0;
        Dot a, b;
        double x = (points[first].x + points[second].x) / 2;
        double y = (points[first].y + points[second].y) / 2;
        Dot cur(x, y);
        for (int j = 2; j <= n; ++j){
            a = cur - Dot(points[j-1].x, points[j-1].y);
            b = cur - Dot(points[j].x, points[j].y);
            angle_sum += atan2l(vect(a, b), scal(a, b));
        }
        a = cur - Dot(points[n].x, points[n].y);
        b = cur - Dot(points[1].x, points[1].y);
        angle_sum += atan2l(vect(a, b), scal(a, b));
        if(std::fabs(angle_sum) < std::numbers::pi){
            return false;
        } else {
            return true;
        }
     
    }
     
    int main() {
        //всё в 1-индексации
         int n;
        std::cin>>n;
        std::vector<Dot> points (n + 1);
        std::vector<Segment> sides(n+1);
        for(int  i = 1; i <= n; ++i){
            std::cin>>points[i].x>>points[i].y;
    //        points[i].x *= 2;
    //        points[i].y *= 2;
        }
        for(int  i = 1; i < n; ++i){
            sides[i] = Segment(points[i], points[i + 1]);
        }
        sides[n] = Segment(points[n], points[1]);
     
        std::vector<std::vector<bool>> diags(n+ 1, std::vector<bool>(n+1));
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= n; ++j){
                diags[i][j] = is_diagonal(n, points, sides, std::min(i, j), std::max(i, j));
            }
        }
     
        std::vector<std::vector <int64_t>> dp (n + 1, std::vector<int64_t> (n+1, 0));
        for(int len = 0; len < n; ++len){
            for(int i = 1; i + len <= n; ++i){
                if(len == 0 || len == 1){
                    dp[i][i + len] = 1;
                    continue;
                }
                dp[i][i + len] = 0;
                if(!diags[i][i + len]){
                    continue;
                }
                for(int k = 1; k < len; ++k){
                    dp[i][i + len] += (dp[i][i + k] * dp[i + k][i + len] % MODULO);
                    dp[i][i + len] %= MODULO;
                }
            }
        }
        std::cout<<dp[1][n] % MODULO;
    }
