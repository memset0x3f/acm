#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define EPS 1e-2
#define N 128
using namespace std;
struct Point
{
    double x, y;
    Point(double _x, double _y)
    {
        x = _x, y = _y;
    }
    Point(){}
    double toPoint(Point a)
    {
        return sqrt((a.x - x) * (a.x - x) + (a.y - y) * (a.y - y));
    }
}p[N];
int n;
double cost(Point v)
{
    double sum = 0;
    for (int i = 1; i <= n; ++i)
        sum += v.toPoint(p[i]);
    return sum;
}

double delta, nows, temps;
Point a, b;
double step[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool change;
int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 1; i <= n; ++i)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        a = Point(0, 0), delta = 1000;
        nows = cost(a);
        while (delta > EPS)
        {
            do
            {
                change = false;
                for (int k = 0; k < 4; ++k)
                {
                    b = Point(a.x + step[k][0] * delta, a.y + step[k][1] * delta);
                    temps = cost(b);
                    if (temps < nows)
                    {
                        a = b;
                        nows = temps;
                        change = true;
                        break;
                    }
                }
            }while (change);
            delta *= 0.8;
        }
        printf("%d\n", (int)(round(nows)));
    }
    return 0;
}
