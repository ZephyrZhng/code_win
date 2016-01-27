#include<iostream.h>
    void main()
    {
        int a=1,b=2,c=3;
        cout<<"a="<<a<<'\t'<<"b="<<b<<'\t'<<"c="<<c<<'\t'<<endl;
        {
            int b=4,c=5;
            cout<<"a="<<a<<'\t'<<"b="<<b<<'\t'<<"c="<<c<<'\t'<<endl;
            a=b;
            {
                int c=b;
                cout<<"a="<<a<<'\t'<<"b="<<b<<'\t'<<"c="<<c<<'\t'<<endl;
            }
            cout<<"a="<<a<<'\t'<<"b="<<b<<'\t'<<"c="<<c<<'\t'<<endl;
         }
         cout<<"a="<<a<<'\t'<<"b="<<b<<'\t'<<"c="<<c<<'\t'<<endl;
      }
