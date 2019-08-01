/*
 * Convex hull
 */

#include <vector>
#include <algorithm>

using namespace std;

class ConvexHull {
public:
    class Point {
    public:
        int x, y;
        Point() {}
        Point(int x_, int y_): x(x_), y(y_) {}
        bool operator<(const Point& rhs) {
            return x < rhs.x || x == rhs.x && y < rhs.y;
        }
    };

    void addPoint(int x, int y) {
        points.emplace_back(x, y);
    }
    // return convexhull points in counter clockwise
    vector<Point> convexHull(bool countBoundary = false) {
        int n = points.size(), k = 0;
        if (n <= 3) return points;
        sort(points.begin(), points.end());
        vector<Point> CH(2 * n);

        // Build lower hull
        for (size_t i = 0; i < n; ++i) {
            while (k >= 2 && clockWise(CH[k-2], CH[k-1], points[i], countBoundary)) k--;
            CH[k++] = points[i];
        }
	    // Build upper hull
        for (size_t i = n-1, t = k+1; i > 0; --i) {
            while (k >= t && clockWise(CH[k-2], CH[k-1], points[i-1], countBoundary)) k--;
            CH[k++] = points[i-1];
        }

        CH.resize(k-1);
        return CH;
    }

private:
    vector<Point> points;
    // 2D cross product of OA and OB vectors
    int cross(const Point &O, const Point &A, const Point &B) {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }
    bool clockWise(const Point &O, const Point &A, const Point &B, bool countBoundary) {
        int crossProduct = cross(O, A, B);
        return countBoundary ? crossProduct < 0 : crossProduct <= 0;
    }
};