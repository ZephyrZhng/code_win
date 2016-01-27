//lab2_3.cpp
#include<iostream.h>
const float PI=3.1416;
void main()
{
    int iType;
    float radius,a,b,area;
    cout<<"图形的类型为?(1为圆形，2为长方形，3为正方形)：";
    cin>>iType;
    switch(iType)
    {
    case 1:
    cout<<"圆的半径为：";
    cin>>radius;
    area=PI*radius*radius ;
    cout<<"面积为："<<area<<endl;
    break;
    case 2:
    cout<<"矩形的长为：";
    cin>>a;
    cout<<"矩形的宽为：";
    cin>>b;
    area=a*b;
    cout<<"面积为："<<area<<endl;
    break;
    case 3:
    cout<<"正方形的边长为：";
    cin>>a;
    area=a*a;
    cout<<"面积为："<<area<<endl;
    break;
    default:
    cout<<"不是合法的输入值!"<<endl;
	}
}
