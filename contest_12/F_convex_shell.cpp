    #include <iostream>
    #include <vector>
     
    class Point {
     public:
      int64_t x_coord;
      int64_t y_coord;
      Point() = default;
      Point(int64_t x_coord, int64_t y_coord) : x_coord(x_coord), y_coord(y_coord) {};
    };
     
    bool operator<(const Point& first, const Point& second) {
      if (first.x_coord < second.x_coord) {
        return true;
      }
      return first.x_coord == second.x_coord && first.y_coord <= second.y_coord;
    }
     
    Point operator-(const Point& first, const Point& second) {
      return {first.x_coord - second.x_coord, first.y_coord - second.y_coord};
    }
     
    int64_t VectorProduct(Point first, Point second) {
      return first.x_coord * second.y_coord - first.y_coord * second.x_coord;
    }
     
    bool WrongLastConvexPoint(std::vector<Point>& convex, bool is_upper, Point new_point) {
      if (convex.size() < 2) {
        return false;
      }
      int64_t vect_prod = VectorProduct(convex[convex.size() - 1] - convex[convex.size() - 2],
                                        new_point - convex[convex.size() - 1]);
      return (is_upper && (vect_prod >= 0) || !is_upper && (vect_prod <= 0));
    }
     
    void UpdateConvex(std::vector<Point>& convex, bool is_upper, Point new_point) {
      while (WrongLastConvexPoint(convex, is_upper, new_point)) {
        convex.pop_back();
      }
      convex.push_back(new_point);
    }
     
    std::vector<Point> BuildConvex(std::vector<Point> points) {
      size_t points_num = points.size();
      std::sort(points.begin(), points.end());
      std::vector<Point> upper_convex;
      std::vector<Point> lower_convex;
      for (size_t i = 0; i < points_num; ++i) {
        UpdateConvex(upper_convex, true, points[i]);
        UpdateConvex(lower_convex, false, points[i]);
      }
      std::vector<Point> convex;
      for (size_t i = 0; i < upper_convex.size(); ++i) {
        convex.push_back(upper_convex[i]);
      }
      for (size_t i = lower_convex.size() - 2; i >= 1; --i) {
        convex.push_back(lower_convex[i]);
      }
      return convex;
    }
     
    int main() {
      int64_t points_num;
      std::cin >> points_num;
      std::vector<Point> points(points_num);
      for (int64_t i = 0; i < points_num; ++i) {
        std::cin >> points[i].x_coord >> points[i].y_coord;
      }
      std::vector<Point> convex = BuildConvex(points);
      std::cout << convex.size() << '\n';
      for (const auto& point : convex) {
        std::cout << point.x_coord << ' ' << point.y_coord << '\n';
      }
    }
