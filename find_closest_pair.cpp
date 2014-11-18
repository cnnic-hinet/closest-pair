#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 20000;
class Point
{
    public:
        Point();
        Point(double,double);
        double getX() const;
        double getY() const;
        void setX(double);
        void setY(double);
        double distance(const Point&) const;
    private:
        double x,y;
}split[MAXN];

Point::Point()
{
    x=0;
    y=0;
}
Point::Point(double x,double y)
{
    this->x = x;
    this->y = y;
}
double Point::getX() const 
{
    return x;
}
double Point::getY() const
{
    return y;
}
void Point::setX(double x)
{
    this->x = x;
}
void Point::setY(double y)
{
    this->y = y;
}
double Point::distance(const Point&p) const
{
    return sqrt((x - p.x) * (x-p.x) + (y-p.y)*(y-p.y));
}
bool com_x(const Point &p1,const Point &p2)
{
    return p1.getX() < p2.getX();
}
bool com_y(const Point &p1,const Point &p2)
{
    return p1.getY() < p2.getY();
}

pair <Point,Point> find_closest(Point points[],int left,int right)
{
    int mid = 0;
    int count = 0;
    double d1,d2,d3;
    pair<Point,Point> temp1,temp2,result;
    if(right - left == 1)
    {
        return pair<Point,Point>(points[left],points[right]);
    }
    if(right - left == 2)
    {
        d1 = points[left].distance(points[left+1]);
        d2 = points[left].distance(points[right]);
        d3 = points[left+1].distance(points[right]);
        if(d1 <= d2 && d1 <= d3)
        {
            return pair<Point,Point>(points[left],points[left+1]);
        }
        if(d2 <= d1 && d2 <= d3)
        {
            return pair<Point,Point>(points[left],points[right]);
        }
        
        return pair<Point,Point>(points[left+1],points[right]);
    }
    mid = (left + right) / 2;
    temp1 = find_closest(points,left,mid);
    temp2 = find_closest(points,mid+1,right);
    d1 = temp1.first.distance(temp1.second);
    d2 = temp2.first.distance(temp2.second);
    if(d1 < d2)
    {
        result = temp1;
        d3 = d1;
    }
    if(d2 < d1)
    {
        result = temp2;
        d3 = d2;
    }
    for(int i=left;i<=right;i++)
    {
        if(points[i].distance(points[mid])<= d3)
        {
            split[count++] = points[i];
        }
    }
    sort(split,split+count,com_y);
    for(int i=0;i<count;i++)
    {
        for(int j=i+1;j<count;j++)
        {
            if(split[i].distance(split[j]) > d3)
                break;
            else
            {
                result = pair<Point,Point>(split[i],split[j]);
            }
        }
    }
    return result;
}
pair <Point,Point> closest_pair(Point points[],int n)
{
    sort(points,points+n,com_x);
    return find_closest(points,0,n-1);
}
int main()
{
    int n,i;
    double x,y;
    Point points[MAXN];
    pair<Point,Point> result;
    while(1)
    {
        cout << "Points count: ";
        cin >> n;
        if(n<2 || n > MAXN)
            cout << "error"<<endl;
        else
            break;
    }
    cout << "Enter coordinates:"<<endl;
    for ( i=0;i< n;i++)
    {
        cin >> x >> y;
        points[i] = Point(x,y);
    }
    result = closest_pair(points,n);
    cout << endl;
    cout << result.first.getX()<<" "<<result.first.getY()<<endl;
    cout << result.second.getX()<<" "<<result.second.getY()<<endl;
    cout << endl;
    cout << "Distance:" << result.first.distance(result.second)<<endl;
    return 0;
}




