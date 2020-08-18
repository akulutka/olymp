#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <limits.h>
#define PI 3.14159265359

using namespace std;
typedef long double ld;

struct vec {
    ld dX;
    ld dY;
    vec() {
        dX = 0;
        dY = 0;
    }
    vec(ld _dx, ld _dy) {
        dX = _dx;
        dY = _dy;
    }
    vec(point p1, point p2) {
        dX = p2.X - p1.X;
        dY = p2.Y - p1.Y;
    }
};

struct line {
    ld A;
    ld B;
    ld C;
    line() {
        A = 0;
        B = 0;
        C = 0;
    }
    line(ld _a, ld _b, ld _c) {
        A = _a;
        B = _b;
        C = _c;
    }
};

struct point {
    ld X;
    ld Y;
    point() {
        X = 0;
        Y = 0;
    }
    point(ld _x, ld _y) {
        X = _x;
        Y = _y;
    }
};

struct segment {
    point L, R;
    segment() {
        L = point(0, 0);
        R = point(0, 0);
    }
    segment(point _L, point _R) {
        L = _L;
        R = _R;
    }
};

line pToLine(point p1, point p2) {
    ld A = p2.Y - p1.Y;
    ld B = p1.X - p2.X;
    ld C = p1.Y * (p2.X - p1.X) - p1.X * (p2.Y - p1.Y);
    return line(A, B, C);
}

struct circle {
    point C;
    ld R;
    circle() {
        C = point(0, 0);
        R = 0;
    }
    circle(point _c, ld _r) {
        C = _c;
        R = _r;
    }
    circle(ld xC, ld yC, ld _r) {
        C = point(xC, yC);
        R = _r;
    }
};

ld vecMul(vec A, vec B) {
    return A.dX * B.dY - B.dX * A.dY;
}

ld scalMul(vec A, vec B) {
    return A.dX * B.dX + A.dY * B.dY;
}

bool isInLine(point p, line l) {
    return l.A * p.X + l.B * p.Y + l.C == 0;
}

bool isInner(point toCheck, point p1, point p2) { // point in rectangle with diag. p1 -> p2 
    if (toCheck.X >= min(p1.X, p2.X) && toCheck.X <= max(p1.X, p2.X)) {
        return toCheck.Y >= min(p1.Y, p2.Y) && toCheck.Y <= max(p1.Y, p2.Y);
    }
    return false;
}

ld d(point p1, point p2) {
    return sqrt((p1.X - p2.X) * (p1.X - p2.X) + (p1.Y - p2.Y) * (p1.Y - p2.Y));
}

ld lineDist(point p, line l) { // distance from point to line 
    return (l.A * p.X + l.B * p.Y + l.C) / (l.A * l.A + l.B * l.B);
}

ld segmentPDist(point p, segment s) { // distance from point to segment
    point pX;
    line l;
    l = pToLine(s.L, s.R);
    ld param = lineDist(p, l);
    pX.X = p.X - l.A * param;
    pX.Y = p.Y - l.B * param;
    if (isInner(pX, s.L, s.R)) {
        return d(p, pX);
    } else {
        return min(d(p, s.L), d(p, s.R));
    }
}

point lineIntersection(line l1, line l2) { // point of line intersectioon
    ld x = (l2.B * l1.C - l2.C * l1.B) / (l1.B * l2.A - l2.B * l1.A);
    ld y = (l2.A * l1.C - l1.A * l2.C) / (l1.A * l2.B - l2.A * l1.B);
    return point(x, y);
}

vec calibrated(vec x, ld d) {
    ld hyp = sqrt(x.dX * x.dX + x.dY * x.dY);
    x.dX = x.dX * d / hyp;
    x.dY = x.dY * d / hyp;
    return x;
}

line perpLine(line l, point p) {
    return line(l.B, -l.A, -l.B * p.X + l.A * p.Y);
}

int circles(circle c1, circle c2, point &p1, point &p2) { // different states of line and circle locations
    if (c1.R < c2.R) {
        swap(c1, c2);
    }
    vec v = vec(c2.C.X - c1.C.X, c2.C.Y - c1.C.Y);
    ld ds = d(c1.C, c2.C);
    if (c1.C.X == c2.C.X && c1.C.Y == c2.C.Y && c1.R == c2.R) {
        return -1;
    } else if (c1.R + c2.R < ds || c2.R + ds < c1.R) {
        return 0;
    } else if (c1.R + c2.R == ds) {
        v = calibrated(v, c1.R);
        p1 = point(c1.C.X + v.dX, c1.C.Y + v.dY);
        return 1;
    } else if (c2.R + ds == c1.R) {
        v = calibrated(v, c1.R);
        p1 = point(c1.C.X + v.dX, c1.C.Y + v.dY);
        return 1;
    } else {
        ld d1 = (c1.R * c1.R - c2.R * c2.R + ds * ds) / (2 * ds);
        v = calibrated(v, d1);
        point pM = point(c1.C.X + v.dX, c1.C.Y + v.dY);
        line l = pToLine(c1.C, c2.C);
        line lp = perpLine(l, pM);
        vec v1 = vec(-lp.B, lp.A);
        v1 = calibrated(v1, sqrt(c1.R * c1.R - d1 * d1));
        p1 = point(pM.X + v1.dX, pM.Y + v1.dY);
        p2 = point(pM.X - v1.dX, pM.Y - v1.dY);
        return 2;
    }
}

ld hyp(ld x, ld y) {
    return sqrt(x * x + y * y);
}

ld cath(ld hyp, ld cath1) {
    return sqrt(hyp * hyp - cath1 * cath1);
}

ld polarAng(point p) {
    ld A = atan2(p.Y, p.X);
    A < 0 ? A += 2 * PI : A += 0;
    return A;
}

ld area(vector<point> pol) { // area of polygon
    point def;
    ld res = 0;
    for (int i = 0; i < pol.size() - 1; i++) {
        vec v1 = vec(def, pol[i]);
        vec v2 = vec(def, pol[i + 1]);
        res += vecMul(v1, v2);
    }
    vec v1 = vec(def, pol[pol.size() - 1]);
    vec v2 = vec(def, pol[0]);
    res += vecMul(v1, v2);
    return abs(res) / 2;
}

bool isInside(point toCheck, vector<point> pol) { // is point in polygon
    ld res = 0;
    for (int i = 0; i < pol.size() - 1; i++) {
        vec v1 = vec(toCheck, pol[i]);
        vec v2 = vec(toCheck, pol[i + 1]);
        res += atan2(vecMul(v1, v2), scalMul(v1, v2));
    }
    vec v1 = vec(toCheck, pol[pol.size() - 1]);
    vec v2 = vec(toCheck, pol[0]);
    res += atan2(vecMul(v1, v2), scalMul(v1, v2));
    return !(res == 0);
}

bool isConvex(vector<point> vP) { // is polygon convex?
    vec v1, v2, v3;
    for (int i = 0; i < vP.size() - 3; i++) {
        v1 = vec(vP[i], vP[i + 1]);
        v2 = vec(vP[i + 1], vP[i + 2]);
        v3 = vec(vP[i + 2], vP[i + 3]);
        if (signbit(vecMul(v1, v2)) != signbit(vecMul(v2, v3)))
            return false;
    }
    v1 = vec(vP[vP.size() - 3], vP[vP.size() - 2]);
    v2 = vec(vP[vP.size() - 2], vP[vP.size() - 1]);
    v3 = vec(vP[vP.size() - 1], vP[0]);
    if (signbit(vecMul(v1, v2)) != signbit(vecMul(v2, v3)))
        return false;
    v1 = vec(vP[vP.size() - 2], vP[vP.size() - 1]);
    v2 = vec(vP[vP.size() - 1], vP[0]);
    v3 = vec(vP[0], vP[1]);
    if (signbit(vecMul(v1, v2)) != signbit(vecMul(v2, v3)))
        return false;
    v1 = vec(vP[vP.size() - 1], vP[0]);
    v2 = vec(vP[0], vP[1]);
    v3 = vec(vP[1], vP[2]);
    if (signbit(vecMul(v1, v2)) != signbit(vecMul(v2, v3)))
        return false;
    return true;
}

int main() {
    //any code
}