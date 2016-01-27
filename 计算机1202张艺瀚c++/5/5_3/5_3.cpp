#include<iostream.h>
     int a=1,b=2;
     int f1(int x)
     {
         int i,b=3;
         i=(a*b)/x;
         cout<<"i="<<i<<endl;
         return i;
      }
      int c=3;
      int f2(int x,int y)
      { 
          int u,v,a=5;
          u=x+y;
          v=(b-a)/c;
          cout<<"u="<<u<<endl;
          cout<<"v="<<v<<endl;
          return u-v;
       }
       void main()
       {
       cout<<f1(1)+a-b<<endl;
       cout<<f2(2,3)*c<<endl;
    }
