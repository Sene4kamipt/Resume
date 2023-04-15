    #include <iostream>
    #include <iomanip>
    #include <cmath>
    #include <vector>
    #include<string>
    #include <algorithm>
    #include <limits>
    #include <unordered_map>
    #include <bitset>
     
    #pragma GCC optimization ("unroll-loops")
     
    struct dot{
        long long x;
        long long y;
        dot():x(0), y(0){}
        dot(long long x, long long y): x(x), y(y){}
        dot(const dot& d): x(d.x), y(d.y){}
        bool operator==(const dot& other){
            return (x==other.x)&&(y==other.y);
        }
        long long dist(const dot& other){
            return (x-other.x)*(x-other.x)+(y-other.y)*(y-other.y);
        } 
    };
     
    struct segment {
        int dot1_index;
        int dot2_index;
        long long length;
    };
     
    bool comp(const segment& first, const segment& second){
        return first.length > second.length;
    }
     
    int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);
        int n, x, y;
        std::cin >> n;
        std::vector<dot> dots(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> x >> y;
            dots[i]=dot(x,y);
        }
        std::vector<segment> sides((n * (n - 1)) / 2);
        int curr_segment = 0;
        for(int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                sides[curr_segment] = segment({i, j, dots[i].dist(dots[j])});
                ++curr_segment;
            }
        }
        sort(sides.begin(), sides.end(), comp);
        std::vector<std::bitset<3000>> triangle(3000);
        for(int i = 0; i < sides.size(); ++i) {
            triangle[sides[i].dot1_index][sides[i].dot2_index] = true;
            triangle[sides[i].dot2_index][sides[i].dot1_index] = true;
            if ((triangle[sides[i].dot1_index] & triangle[sides[i].dot2_index]).any()) {
                std::cout<<std::setprecision(7) << sqrt(sides[i].length)/2;
                break;
            }
        }
        return 0;
    }
