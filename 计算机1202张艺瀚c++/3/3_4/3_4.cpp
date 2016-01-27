      //lab3_5
      #include<iostream.h>
      int fib(int n);
      int main()
      {
		int n,answer;
	  cout<<"Enter number:";
           cin>>n;
      cout<<"\n\n";
      answer=fib(n);
      cout<<answer<<"is the"<<n<<"th Fibonacci number\n";
      return 0;
}
int fib(int n)
{
	cout<<"Processing fib("<<n<<")бн";
	if(n<3)
	{
		cout<<"Reutrn 1!\n";
		return(1);
}
else
{
	 cout<<"Call fib("<<n-2<<")and fib("<<n-1<<").\n";
  return(fib(n-2)+fib(n-1));
}   
}
