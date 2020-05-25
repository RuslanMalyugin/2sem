//
// Created by User on 28.04.2020.
//

#ifndef GEOMETRY_GEOMETRY_H

#include <utility>
#include <vector>
#include <cmath>
#include <iostream>
#include <cassert>
#include <cstdarg>

const double EPS = 0.0001;
const double PI = 3.14159265358979323846;

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base *>(ptr) != nullptr;
}

struct Point {
    double x = 0.0;
    double y = 0.0;

    Point() = default;

    Point(double x_, double y_) : x(x_), y(y_) {}

    Point(const Point &other) = default;

    Point &operator=(const Point &other) = default;

    bool operator==(const Point &second) const {
        return (std::abs(x - second.x) <= EPS) && (std::abs(y - second.y) <= EPS);
    }

    bool operator!=(const Point &second) const {
        return !(*this == second);
    }
};

class Line {
public:
    double a; // уравнение kx + b = y
    double b;
    double c;

    Line(double k, double b_) : a(k), b(-1.0), c(b_) {}

    Line (double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}

    Line(const Point &first, const Point &second) {
        //assert(first != second);
        a = second.y - first.y;
        b = first.x - second.x;
        c = (first.y - second.y) * first.x + first.y * (second.x - first.x);
    }

    Line(Point point_, double k_) {
        a = k_;
        b = -1.0;
        c = point_.y - point_.x * k_;
    }

    bool operator==(Line second) const {
        return (std::abs(b * second.a - second.b * a) <= EPS) && (std::abs(c * second.a - second.c * a) <= EPS) &&
               (std::abs(a * second.b - second.a * b) <= EPS) && (std::abs(c * second.b - second.c * b) <= EPS) &&
               (std::abs(b * second.c - second.b * c) <= EPS) && (std::abs(a * second.c - second.a * c) <= EPS);
    }

    bool operator!=(Line second) const {
        return !(*this == second);
    }
};

Point reflex_point(Point current, Point center) {
    double x1 = 2.0 * center.x - current.x;
    double y1 = 2.0 * center.y - current.y;
    return {x1, y1};
}

bool is_line_intersect(Line first, Line second, Point &intersection) {
    double zn = (first.a * second.b - first.b * second.a);
    if (std::abs(zn) < EPS) {
        //std::cout << 1;
        return false;
    }
    intersection.x = -(first.c * second.b - first.b * second.c) / zn;
    intersection.y = -(first.a * second.c - second.a * first.c) / zn;
    //std :: cout << '\n' << zn << '\n';
    return true;
}

Point reflex_point(Point current, Line axis) {
//    if (abs(axis.b) < EPS) {
//        double d = -axis.c / axis.a;
//        Point r(2.0 * d - current.x, current.y);
//        return r;
//    }
//    double k = -axis.a / axis.b;
//    double b = -axis.c / axis.b;
//    double x1 = 2.0 * (current.x - k * (b - current.y)) / (1.0 + k * k) - current.x;
//    double y1 = 2.0 * (k * (2.0 * current.x + k * current.y) + 2.0 * b - current.y) / (1.0 + k * k);
//    return {x1, y1};
    Line Ortho(-axis.b, axis.a, -axis.a * current.y + axis.b * current.x);
    Point inter;
    is_line_intersect(axis, Ortho, inter);
    return {2 * inter.x - current.x, 2 * inter.y - current.y,};

}


Point rotate_point(Point current, Point center, double angle) {
    double radian = angle * PI / 180.0;
    double x1 = center.x + (current.x - center.x) * cos(radian) - (current.y - center.y) * sin(radian);
    double y1 = center.y + (current.x - center.x) * sin(radian) + (current.y - center.y) * cos(radian);
    return {x1, y1};
}



char rotate_angle(Point a1, Point a2, Point b1, Point b2) {
    double vec1x = a2.x - a1.x;
    double vec1y = a2.y - a1.y;
    double vec2x = b2.x - b1.x;
    double vec2y = b2.y - b1.y;
    double angle = std::atan2((vec1x * vec2y - vec1y * vec2x), (vec1x * vec2x + vec1y * vec2y));
    if (angle > EPS)
        return 1;
    else if (angle < -EPS)
        return -1;
    else
        return 0;
}

bool is_segment_and_ray_intersect(Point seg1, Point seg2, Point ray_start, Point another) {
    Point intersection(0.0, 0.0);
    double x0, x1, y0, y1;
    x0 = std::min(seg1.x, seg2.x);
    x1 = std::max(seg1.x, seg2.x);
    y0 = std::min(seg1.y, seg2.y);
    y1 = std::max(seg1.y, seg2.y);
    bool chk = is_line_intersect(Line(seg1, seg2), Line(ray_start, another), intersection);
    if (chk) {
        bool p = (intersection.x >= x0) && (intersection.x <= x1) && (intersection.y >= y0) && (intersection.y <= y1);
        //std::cout << x0 << ' ' <<  x1 << ' '<<  y0 << ' '<<  y1 << ' '<< intersection.x <<" "<< intersection.y;
        bool r = ((intersection.x > ray_start.x) == (another.x > ray_start.x)) &&
                 ((intersection.y > ray_start.y) == (another.y > ray_start.y));
        //std::cout << '\n' << p << '\n' << r << '\n';
        return p && r;
    }
    return false;

}

bool is_segment_and_segment_intersect(Point seg1, Point seg2, Point _seg1, Point _seg2) {
    Point intersection(0.0, 0.0);
    double x0, x1, y0, y1;
    double x0_, x1_, y0_, y1_;
    x0 = std::min(seg1.x, seg2.x);
    x1 = std::max(seg1.x, seg2.x);
    y0 = std::min(seg1.y, seg2.y);
    y1 = std::max(seg1.y, seg2.y);
    x0_ = std::min(_seg1.x, _seg2.x);
    x1_ = std::max(_seg1.x, _seg2.x);
    y0_ = std::min(_seg1.y, _seg2.y);
    y1_ = std::max(_seg1.y, _seg2.y);
    bool chk = is_line_intersect(Line(seg1, seg2), Line(_seg1, _seg2), intersection);
    if (chk) {
        bool p = (intersection.x >= x0) && (intersection.x <= x1) && (intersection.y >= y0) && (intersection.y <= y1);
        //std::cout << x0 << ' ' <<  x1 << ' '<<  y0 << ' '<<  y1 << ' '<< intersection.x <<" "<< intersection.y;
        bool r = (intersection.x >= x0_) && (intersection.x <= x1_) && (intersection.y >= y0_) &&
                 (intersection.y <= y1_);
        //std::cout << '\n' << p << '\n' << r << '\n';
        return p && r;
    }
    return false;

}


double Distance(const Point &a, const Point &b) {
    double dist = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    return dist;
}

double angle(const Point &a, const Point &b, const Point &c) {
    double x1 = -b.x + a.x;
    double x2 = +c.x - b.x;
    double y1 = -b.y + a.y;
    double y2 = c.y - b.y;
    double vecx = x1 * x2 + y1 * y2;
    double sum = Distance(a, b) * Distance(b, c);
    return acos(vecx / sum);
}

Point scaling(const Point &current, const Point &center, double coeff) {
    double x = coeff * (current.x - center.x) + center.x;
    double y = coeff * (current.y - center.y) + center.y;
    return {x, y};
}


class Shape {
public:
    virtual double perimeter() const = 0;

    virtual double area() const = 0;

    virtual bool isCongruentTo(const Shape &another) const = 0;

    virtual bool operator==(const Shape &another) const = 0;

    virtual bool isSimilarTo(const Shape &another) const = 0;

    virtual bool containsPoint(Point point) const = 0;

    virtual void rotate(Point center, double angle) = 0;

    virtual void reflex(Point center) = 0;

    virtual void reflex(Line axis) = 0;

    virtual void scale(Point center, double coefficient) = 0;

    virtual ~Shape() = default;
};

class Ellipse : public Shape {
protected:
    Point focus1;
    Point focus2;
    double sum_of_dist;
public:
    Ellipse() = default;

    Ellipse(Point f1, Point f2, double dist) : focus1(f1), focus2(f2), sum_of_dist(dist) {

    }

    std::pair<Point, Point> focuses() {
        return std::make_pair(focus1, focus2);
    }

    std::pair<Line, Line> directrices() {
        Line ox(focus1, focus2);
        if (abs(ox.a) > EPS) {
            double coef = ox.b / ox.a;
            double c = sqrt(pow((focus2.x - focus1.x), 2) + pow((focus2.y - focus1.y), 2)) * 0.5;
            Point center((focus2.x + focus1.x) * 0.5, (focus1.y + focus2.y) * 0.5);
            double x0 = pow((sum_of_dist / 2.0), 2) / c;
            Point d1 = rotate_point(Point(x0, 0.0), center, -1.0 / coef);
            Point d2 = rotate_point(Point(-x0, 0.0), center, -1.0 / coef);
            Line dir1(d1, coef);
            Line dir2(d2, coef);
            return std::make_pair(dir1, dir2);
        }
        double c = sqrt(pow((focus2.x - focus1.x), 2) + pow((focus2.y - focus1.y), 2)) * 0.5;
        double x0 = pow((sum_of_dist / 2), 2) / c;
        Point center((focus2.x + focus1.x) * 0.5, (focus1.y + focus2.y) * 0.5);
        Line dir1(Point(center.x + x0, 0.0), Point(center.x + x0, 1));
        Line dir2(Point(center.x - x0, 0.0), Point(center.x - x0, 1));
        return std::make_pair(dir1, dir2);
    }

    double eccentricity() {
        double c = sqrt(pow((focus2.x - focus1.x), 2) + pow((focus2.y - focus1.y), 2)) * 0.5;
        return c * 2 / sum_of_dist;
    }

    double perimeter() const override {
        double a = sum_of_dist / 2.0;
        double c = Distance(focus2, focus1) / 2.0;
        double b = sqrt(a * a - c * c);
        double per = PI * (3 * (a + b) - sqrt((3 * a + b) * (a + 3 * b)));
        return per;
    }

    double area() const override {
        double a = sum_of_dist / 2.0;
        double c = Distance(focus2, focus1) / 2.0;
        double b = sqrt(a * a - c * c);
        return PI * a * b;
    }


    bool isCongruentTo(const Shape &another) const override {
        const Ellipse *another_ellipse = dynamic_cast<const Ellipse *>(&another);
        if (instanceof<Ellipse, Shape>(&another)) {
            return abs(sum_of_dist - another_ellipse->sum_of_dist) < EPS &&
                   abs(Distance(focus1, focus2) - Distance(another_ellipse->focus2, another_ellipse->focus1)) < EPS;
        }
        return false;
    }

    bool operator==(const Shape &another) const override {
        const Ellipse *another_ellipse = dynamic_cast<const Ellipse *>(&another);
        if (instanceof<Ellipse, Shape>(&another)) {
            return ((focus2 == another_ellipse->focus2 && focus1 == another_ellipse->focus1) ||
                    (focus1 == another_ellipse->focus2 && focus2 == another_ellipse->focus1)) &&
                   abs(sum_of_dist - another_ellipse->sum_of_dist) < EPS;
        }
        return false;
    }

    bool isSimilarTo(const Shape &another) const override {
        const Ellipse *another_ellipse = dynamic_cast<const Ellipse *>(&another);
        if (instanceof<Ellipse, Shape>(&another)) {
            return abs(Distance(focus2, focus1) * another_ellipse->sum_of_dist -
                       Distance(another_ellipse->focus1, another_ellipse->focus2) * sum_of_dist) < EPS;
        }
        return false;
    }

    bool containsPoint(Point point) const override {
        double dist = Distance(point, focus1) + Distance(point, focus2);
        return dist < sum_of_dist + EPS;
    }

    void rotate(Point center, double angle) override {
        focus1 = rotate_point(focus1, center, angle);
        focus2 = rotate_point(focus2, center, angle);
    }

    void reflex(Point center) override {
        focus1 = reflex_point(focus1, center);
        focus2 = reflex_point(focus2, center);
    }

    void reflex(Line axis) override {
        focus1 = reflex_point(focus1, axis);
        focus2 = reflex_point(focus2, axis);
    }

    void scale(Point center, double coefficient) override {
        focus1 = scaling(focus1, center, coefficient);
        focus2 = scaling(focus2, center, coefficient);
    }

};

class Circle : public Ellipse {
    double radius_;
public:
    Circle() = default;

    Circle(Point cnt, double r) : Ellipse(cnt, cnt, r), radius_(r), center_(cnt) {}

    double radius() {
        return radius_;
    }

    Point center_;

    Point center() {
        return center_;
    }
};


class Polygon : public Shape {
protected:
    std::vector<Point> points;


public:
    Polygon() = default;

    bool operator==(const Shape &another) const override {
        const Polygon *another_pol = dynamic_cast<const Polygon *>(&another);
        if (instanceof<Polygon, Shape>(&another)) {
            if (verticesCount() != another_pol->verticesCount())
                return false;
            int equal = -1;
            for (int i = 0; i < another_pol->verticesCount(); i++) {
                if (another_pol->getVertices()[0] == getVertices()[i]) {
                    equal = i;
                    break;
                }
            }
            if (equal == -1)
                return false;
            bool chk1, chk2;
            chk1 = true;
            chk2 = true;
            for (int i = 0; i < verticesCount(); i++) {
                if (another_pol->getVertices()[i] != getVertices()[(i + equal) % verticesCount()]) {
                    chk1 = false;
                    break;
                }

                if (another_pol->getVertices()[i] !=
                    getVertices()[(-i + equal + verticesCount() * 2) % verticesCount()]) {
                    chk2 = false;
                    break;
                }

                return chk1 || chk2;
            }
        }
        return false;
    }

    bool operator!=(const Shape &a) {
        return !(*this == a);
    }

    template<class T>
    void PushArgs(const T &value) {
        points.push_back(T(value));
    }

    template<class T, class... Args>
    void PushArgs(const T &value, const Args &... args) {
        points.push_back(T(value));
        PushArgs(args...);
    }

    template<class point_, class... points_>
    Polygon(const point_ &one_, const points_ &... current_points) {
        //points = std::vector<Point>{current_points...};
        PushArgs(one_);
        PushArgs(current_points...);
    }

    Polygon(std::vector<Point> points_) : points(std::move(points_)) {};

    int verticesCount() const {
        return points.size();
    }

    bool isSimilarTo(const Shape &another) const override {

        const auto *another_pol = dynamic_cast<const Polygon *>(&another);
//        for (int i = 0; i < verticesCount(); i++) {
//            std::cerr <<'f';
//            std::cerr << "(" <<getVertices()[i].x << "," << getVertices()[i].y << ")"<<'\n';
//        }
//        for (int i = 0; i < another_pol->verticesCount(); i++) {
//            std::cerr << 's';
//            std::cerr << "("<< another_pol->getVertices()[i].x << "," << another_pol->getVertices()[i].y << ")"<<'\n';
//        }
        if (instanceof<Polygon, Shape>(&another)) {

            if (verticesCount() != another_pol->verticesCount()) {
                return false;
            }
            std::vector<Point> a_p = another_pol->getVertices();
            std::vector<Point> c_p = getVertices();
            double k = sqrt(another_pol->area() / area());
            int index1 = -1;
            int index2 = -1;
            int orient;
            for (int i = 0; i < verticesCount(); i++) {
                if (abs(angle(a_p[0], a_p[1], a_p[2]) -
                        angle(c_p[(i) % verticesCount()], c_p[(i + 1) % verticesCount()],
                              c_p[(i + 2) % verticesCount()])) < EPS) {
                    //std::cout << 2;
                    int chk = 0;
                    for (int j = 0; j < verticesCount(); j++) {
                        if (abs(angle(a_p[(j)], a_p[(j + 1) % verticesCount()], a_p[(j + 2) % verticesCount()]) -
                                angle(c_p[(i - j + verticesCount()) % verticesCount()],
                                      c_p[(i + 1 - j + verticesCount()) % verticesCount()],
                                      c_p[(i + 2 - j + verticesCount()) % verticesCount()])) < EPS) {
                            chk++;
                            orient = -1;
                        }
                    }
                    if (chk != verticesCount()) {
                        //std::cout << 9;
                        chk = 0;
                        for (int j = 0; j < verticesCount(); j++) {
                            if (abs(angle(a_p[(j)], a_p[(j + 1) % verticesCount()], a_p[(j + 2) % verticesCount()]) -
                                    angle(c_p[(i + j + verticesCount()) % verticesCount()],
                                          c_p[(i + 1 + j + verticesCount()) % verticesCount()],
                                          c_p[(i + 2 + j + verticesCount()) % verticesCount()])) < EPS) {
                                chk++;
                                orient = 1;
                            }
                        }
                    }
                    if (chk != verticesCount())
                        continue;
                    else {
                        return true;
                    }
                }
            }
            return false;
        }
        return false;
    }

    bool isCongruentTo(const Shape &another) const override {
        const auto *another_pol = dynamic_cast<const Polygon *>(&another);
                for (int i = 0; i < verticesCount(); i++) {
           // std::cerr <<'f';
           // std::cerr << "(" <<getVertices()[i].x << "," << getVertices()[i].y << ")"<<'\n';
        }
        for (int i = 0; i < another_pol->verticesCount(); i++) {
            //std::cerr << 's';
            //std::cerr << "("<< another_pol->getVertices()[i].x << "," << another_pol->getVertices()[i].y << ")"<<'\n';
        }
        return isSimilarTo(another) && abs(perimeter() - another.perimeter()) < EPS &&
               abs(area() - another.area()) < EPS;
    }

    std::vector<Point> getVertices() const {
        return points;
    }

    void scale(Point center, double coefficient) override {
        for (int i = 0; i < verticesCount(); i++) {
            points[i].x = coefficient * (points[i].x - center.x) + center.x;
            points[i].y = coefficient * (points[i].y - center.y) + center.y;
        }
    }

    double area() const override {
        double area_ = 0;
        int count = points.size();
        area_ += (-points[0].y * points[count - 1].x + points[0].x * points[count - 1].y);
        for (int i = 0; i < count - 1; i++) {
            area_ += (points[i].y * points[i + 1].x - points[i].x * points[i + 1].y);
        }
        return std::abs(area_) / 2;
    }

    double perimeter() const override {
        double perimeter_ = 0;
        int count = points.size();
        perimeter_ += std::sqrt(std::pow((points[count - 1].x - points[0].x), 2) +
                                std::pow((points[count - 1].y - points[0].y), 2));
        for (int i = 0; i < count - 1; i++) {
            perimeter_ += std::sqrt(std::pow((points[i].x - points[i + 1].x), 2) +
                                    std::pow((points[i].y - points[i + 1].y), 2));
        }
        return perimeter_;
    }

    void rotate(Point center, double angle) override {
        for (int i = 0; i < verticesCount(); i++) {
            points[i] = rotate_point(points[i], center, angle);
        }
    }

    void reflex(Point center) override {
        for (int i = 0; i < verticesCount(); i++) {
            points[i] = reflex_point(points[i], center);
        }
    }


    bool isConvex() const {
        int count = points.size();
        char last1 = rotate_angle(points[count - 2], points[count - 1], points[count - 1], points[0]);
        char last2 = rotate_angle(points[count - 1], points[0], points[0], points[1]);
        char last = last1;
        if (last1 == 0)
            last = last2;
        if (last2 == 0)
            last = last1;
        if (last1 != last2 && last1 != 0 && last2 != 0)
            return false;
        if (last == 0) {
            for (int i = 0; i < count - 2; i++) {
                char current = rotate_angle(points[i], points[i + 1], points[i + 1], points[i + 2]);
                if (current != 0) {
                    last = current;
                    break;
                }
            }
        }
        for (int i = 0; i < count - 2; i++) {
            char current = rotate_angle(points[i], points[i + 1], points[i + 1], points[i + 2]);
            if (current == 0)
                continue;
            if (current != last)
                return false;
        }
        return true;
    }

    bool containsPoint(Point point) const override {
        int chk = 0;
        Point ray2(point.x + 10, point.y);
        Point tmpl(point.x + EPS, point.y + EPS);
        Point tmpr(point.x - EPS, point.y - EPS);
        double x = point.x;
        double y = point.y;
        int n = verticesCount();
        for (int i = 0; i < n; i++) {
            if (point == points[i])
                return true;
            if (abs(Line(points[i], points[(i + 1) % n]).a * x + Line(points[i], points[(i + 1) % n]).b +
                    Line(points[i], points[(i + 1) % n]).c) < EPS && x > std::min(points[i].x, points[(i + 1) % n].x) &&
                x < std::max(points[i].x, points[(i + 1) % n].x) && y < std::max(points[i].y, points[(i + 1) % n].y) &&
                y > std::min(points[i].y, points[(i + 1) % n].y))
                return true;
            if (abs(points[i].y - points[(i + 1) % n].y) <= EPS) {
                //std::cout << 1;
                continue;
            }
            if (abs(y - std::max(points[i].y, points[(i + 1) % n].y)) <= EPS &&
                x < std::min(points[i].x, points[(i + 1) % n].x)) {
                //std::cout << 2;
                chk++;
                continue;
            }
            if (abs(y - std::min(points[i].y, points[(i + 1) % n].y)) <= EPS) {
                //std::cout << 3;
                continue;
            }
            if (is_segment_and_ray_intersect(points[i], points[(i + 1) % n], point, ray2)) {
                chk++;
                //std::cout << 4;
                continue;
            }
        }
        return chk % 2;
    }

    void reflex(Line axis) override {
        for (int i = 0; i < verticesCount(); i++) {
            points[i] = reflex_point(points[i], axis);
        }
    }
};

class Rectangle : public Polygon {
public:
    Rectangle() = default;

    template<class point, class... points_>
    Rectangle(const point &one_, const points_ &... current_points) : Polygon(one_, current_points...) {
    }

    Rectangle(Point x1, Point x2, int coefficient) : Rectangle(x1, x2, static_cast<double>(coefficient)) {
    }

    Rectangle(Point x1, Point x2, double coefficent) {
        points.emplace_back(x1);
        double alpha = 180 - 2 * (atan(coefficent) * 180 / PI);
        Point center((x1.x + x2.x) * 0.5, (x1.y + x2.y) * 0.5);
        points.emplace_back(rotate_point(x1, center, alpha));
        points.emplace_back(x2);
        points.emplace_back(rotate_point(x2, center, alpha));
    }

    Point center() {
        Point center((getVertices()[0].x + getVertices()[2].x) * 0.5, (getVertices()[0].y + getVertices()[2].y) * 0.5);
        return center;
    }

    std::pair<Line, Line> diagonals() {
        Line diag1(getVertices()[0], getVertices()[2]);
        Line diag2(getVertices()[1], getVertices()[3]);
        return std::make_pair(diag1, diag2);
    }
};

class Square : public Rectangle {
public:
    Square() = default;

    template<class point, class... points_>
    Square(const point &one_, const points_ &... current_points) : Rectangle(one_, current_points...) {
    }

    Square(Point x1, Point x2) {
        points.emplace_back(x1);
        Point center((x1.x + x2.x) * 0.5, (x1.y + x2.y) * 0.5);
        points.emplace_back(rotate_point(x1, center, 90.0));
        points.emplace_back(x2);
        points.emplace_back(rotate_point(x2, center, 90.0));
    }

    Circle circumscribedCircle() {
        Point center((getVertices()[0].x + getVertices()[2].x) * 0.5, (getVertices()[0].y + getVertices()[2].y) * 0.5);
        double rad = sqrt(
                pow(getVertices()[0].x - getVertices()[2].x, 2) + pow(getVertices()[0].y - getVertices()[2].y, 2)) / 2;
        return {center, rad};
    }

    Circle inscribedCircle() {
        Point center((getVertices()[0].x + getVertices()[2].x) * 0.5, (getVertices()[0].y + getVertices()[2].y) * 0.5);
        double rad = Distance(getVertices()[0], getVertices()[1]) / 2;
        return {center, rad};
    }

};

class Triangle : public Polygon {
public:
    template<typename ... points_>
    Triangle(const points_ &... current_points) : Polygon(current_points...) {
        points = std::vector<Point>{current_points...};
    }

    Circle inscribedCircle() {
//        double alpha = acos(((getVertices()[1].x - getVertices()[0].x) * (getVertices()[2].x - getVertices()[1].x) +
//                             (getVertices()[1].y - getVertices()[0].y) * (getVertices()[2].y - getVertices()[1].y)) /
//                            (Distance(getVertices()[0], getVertices()[1]) *
//                             Distance(getVertices()[1], getVertices()[2])));
//        double betta = acos(((getVertices()[0].x - getVertices()[2].x) * (getVertices()[1].x - getVertices()[0].x) +
//                             (getVertices()[0].y - getVertices()[2].y) * (getVertices()[1].y - getVertices()[0].y)) /
//                            (Distance(getVertices()[0], getVertices()[1]) *
//                             Distance(getVertices()[0], getVertices()[2])));
//        Point a1 = rotate_point(getVertices()[0], getVertices()[1], 180 * (alpha / 2) / PI);
//        Point a0 = rotate_point(getVertices()[1], getVertices()[0], 180 * (betta / 2) / PI);
//        Line bis1(a1, getVertices()[1]);
//        Line bis2(a0, getVertices()[0]);
//        Point center(0, 0);
//        is_line_intersect(bis1, bis1, center);
       double radius = 2 * area() / perimeter();
//        return {center, radius};
    Point a = getVertices()[0];
    Point b = getVertices()[1];
    Point c = getVertices()[2];

    double a_ = sin(angle(b,a,c));
    double b_ = sin(angle(a,b,c));
    double c_ = sin(angle(a,c,b));
    double x1 = (a_* a.x + b_ * b.x + c_ * c.x) / (a_ + b_ + c_);
        double y1 = (a_* a.y + b_ * b.y + c_ * c.y) / (a_ + b_ + c_);
        return {Point(x1,y1), radius};
    }

    Circle circumscribedCircle() {
        Point a = getVertices()[0];
        Point b = getVertices()[1];
        Point c = getVertices()[2];
        double x = (a.y * (b.x * b.x + b.y * b.y - c.x * c.x - c.y * c.y) +
                    b.y * (c.x * c.x + c.y * c.y - a.x * a.x - a.y * a.y) +
                    c.y * (a.x * a.x + a.y * a.y - b.x * b.x - b.y * b.y)) /
                   (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
        double y = (a.x * (b.x * b.x + b.y * b.y - c.x * c.x - c.y * c.y) +
                    b.x * (c.x * c.x + c.y * c.y - a.x * a.x - a.y * a.y) +
                    c.x * (a.x * a.x + a.y * a.y - b.x * b.x - b.y * b.y)) /
                   (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
        Point center(-x / 2, y / 2);
        double radius = Distance(getVertices()[0], getVertices()[1]) * Distance(getVertices()[2], getVertices()[1]) *
                        Distance(getVertices()[0], getVertices()[2]) / area();
        return {center, radius / 4};
    }

    Circle ninePointsCircle() {
        Line a(getVertices()[1], getVertices()[2]);
        Line b(getVertices()[0], getVertices()[2]);
        Line c(getVertices()[1], getVertices()[0]);
        Point a12 = reflex_point(getVertices()[0], a);
        Point b02 = reflex_point(getVertices()[1], b);
        Point c10 = reflex_point(getVertices()[2], c);
        Point h1(0, 0);
        Point h2(0, 0);
        Point h3(0, 0);
        is_line_intersect(a, Line(getVertices()[0], a12), h1);
        is_line_intersect(b, Line(getVertices()[1], b02), h2);
        is_line_intersect(c, Line(getVertices()[2], c10), h3);
        Triangle ar(h1, h2, h3);
        return ar.circumscribedCircle();
    }

    Point orthocenter() {
        Line a(getVertices()[1], getVertices()[2]);
        Line b(getVertices()[0], getVertices()[2]);
        Point a12 = reflex_point(getVertices()[0], a);
        Point b02 = reflex_point(getVertices()[1], b);
        Point h1(0, 0);
        is_line_intersect(Line(a12, getVertices()[0]), Line(b02, getVertices()[1]), h1);
        return h1;
    }

    Point centroid() {
        Line a(getVertices()[0], Point(getVertices()[1].x * 0.5 + getVertices()[2].x * 0.5,
                                       getVertices()[1].y * 0.5 + getVertices()[2].y * 0.5));
        Line b(getVertices()[1], Point(getVertices()[2].x * 0.5 + getVertices()[0].x * 0.5,
                                       getVertices()[2].y * 0.5 + getVertices()[0].y * 0.5));
        Point h1(0, 0);
        is_line_intersect(a, b, h1);
        return h1;
    }

    Line EulerLine() {
        return {orthocenter(), circumscribedCircle().center_};
    }
};


//int main() {
//    int count;
//    std::cin >> count;
//    double px, py;
//    std::cin >> px >> py;
//    std::vector<Point> p;
//    double x, y;
//    for (int i = 0; i < count; i++) {
//        std::cin >> x >> y;
//        p.emplace_back(Point(x, y));
//    }
//    Polygon a(p);
//    Point point(px, py);
//    if (a.containsPoint(point))
//        std::cout << "YES";
//    else
//        std::cout << "NO";
//    //std::cout.precision(15);
//    //std::cout << std::fixed << a.perimeter();
//}

#define GEOMETRY_GEOMETRY_H

#endif //GEOMETRY_GEOMETRY_H
