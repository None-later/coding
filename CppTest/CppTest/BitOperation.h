int add(int x, int y)
{
	int a, b;
	do 
	{
		a = x & y;   // carries
		b = x ^ y;
		x = a << 1;
		y = b;
	}
	while (a);
	return b;
}

int negate(int x)
{
	return add(~x, 1);
}

int subtract(int x, int y)
{
	return add(x , negate(y));
}

int is_even(int n)
{
	return !(n & 1);
	// return ~n & 1 
}

int divide_by_two(int n)
{
	return n >> 1;
}

int multiply_by_two(int n)
{
	return n << 1;
}

int mutiply(int x, int y)
{
	int res = 0;
	if (x < 0 && y < 0)
		return mutiply(negate(x), negate(y));
	if (x >=0 && y < 0)
		return mutiply(y, x);

	while (y > 0)
	{
		if (is_even(y))
		{
			x = multiply_by_two(x); // x <<= 1
			y = divide_by_two(y);	// y >>= 1
		}
		else
		{
			res = add(res, x);
			y = add(y, -1);
		}
	}
	return res;
}

int divide(int x, int y)
{
	int res = 0, sign = 0;
	if (x < 0)
	{
		x = negate(x);
		sign ^= 1;
	}
	if (y < 0)
	{
		y = negate(y);
		sign ^= 1;
	}
	if (y != 0)
	{
		while (x >= y)
		{
			x = subtract(x,y); // need add function
		    res = add(res,1);  // res++
		}
	}
	if (sign)
		res = negate(res);

	return res;
}



