class CBacktracking
{
	typedef list<pair<int, char>> LIST;

public:
	int CountWaysToCalculateTarget(int arr[], int n, int target)
	{
		if (0 == target)
			return 1;

		if (n < 0)
			return 0;

		int exclude = CountWaysToCalculateTarget(arr, n - 1, target);
		int include = CountWaysToCalculateTarget(arr, n-1, target - arr[n]) + CountWaysToCalculateTarget(arr, n-1, target + arr[n]);

		return exclude + include;
	}

	void test_CountWaysToCalculateTarget()
	{
		//int arr[] = { 5, 3, -6, 2 };
		//int target = 6;
		int arr[] = {2, 1};
		int target = 3;
		cout << CountWaysToCalculateTarget(arr, _countof(arr)-1, target);
	}

	void Print_Pairs_CountWaysToCalculateTarget(int arr[], int n, int sum, int target, LIST &lst)
	{
		if (sum == target)
		{
			for (auto i : lst)
			{
				cout << "(" << i.second << ")" << i.first << " ";
			}
			cout << endl;

			return;
		}

		if (n < 0)
			return;

		Print_Pairs_CountWaysToCalculateTarget(arr, n - 1, sum, target, lst);

		lst.push_back({ arr[n], '-' });
		Print_Pairs_CountWaysToCalculateTarget(arr, n - 1, sum - arr[n], target, lst);
		lst.pop_back();

		lst.push_back({ arr[n], '+' });
		Print_Pairs_CountWaysToCalculateTarget(arr, n - 1, sum + arr[n], target, lst);
		lst.pop_back();

		return;
	}

	void test_Print_Pairs_CountWaysToCalculateTarget()
	{
		int arr[] = { 5, 3, -6, 2 };
		int target = 6;
		//int arr[] = { 2, 1 };
		//int target = 3;
		LIST lst;
		Print_Pairs_CountWaysToCalculateTarget(arr, _countof(arr) - 1, 0, target, lst);
	}

	void Print_BinaryCombinations(char Pattern[], int index)
	{
		if (Pattern[index] == '\0')
		{
			cout << Pattern << endl;
			return;
		}

		if (Pattern[index] == '?')
		{
			for (int k = 0; k < 2; k++)
			{
				Pattern[index] = k + '0';
				Print_BinaryCombinations(Pattern, index + 1);
				Pattern[index] = '?';
			}
			return;
		}

		Print_BinaryCombinations(Pattern, index + 1);
	}

	void Print_BinaryCombinations_Iterative(string str)
	{
		stack<string> stk;

		stk.push(str);

		while (!stk.empty())
		{
			str = stk.top();
			stk.pop();

			size_t index = str.find_first_of('?');
			if (index != string::npos)
			{
				for (int k = 0; k < 2; k++)
				{
					str[index] = k + '0';
					stk.push(str);
				}
			}
			else
				cout << str << endl;
		}
	}

	void test_Print_BinaryCombinations()
	{
		char pattern[] = "???";
		Print_BinaryCombinations_Iterative(pattern);
	}
}

void entry_point()
{
	CBacktracking bktrack;
	bktrack.test_CountWaysToCalculateTarget();
	bktrack.test_Print_Pairs_CountWaysToCalculateTarget();
	bktrack.test_Print_BinaryCombinations();
}
