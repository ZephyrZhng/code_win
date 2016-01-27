#include<iostream.h>
int func(int);
void main()
{
   cout<<func(1)<<endl;
   cout<<func(1)<<endl;
}
int func(int c)
{
   int a=0;
   static int b=1;
   a++;
   b++;
return a+b+c;
}
