namespace recursion
{
	//	Here optimizing compiler uses one stack frame for all the recursive calls.
	void factex(int n, int &a)
	{
		if (n == 0) return;
		a *= n;
		factex(n - 1, a);
	}

	void driver()
	{
		int ans = 1;
		factex(5, ans);
		cout << ans << endl;
	}
}
