int fac(int x)
{
	if(x == 0)
	{
		return 1;
	}
	else
	{
		return x * fac(x - 1);
	}
}
