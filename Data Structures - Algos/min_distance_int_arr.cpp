class CMinDistanceBetweenTwoIntegersInArray
{
public:
	bool TrivialMethod(int arr[], int n,  int x, int y, int &dist)
	{
		int min_dist = INT_MAX;

		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (
					(arr[i] == x && arr[j] == y) ||
					(arr[i] == y && arr[j] == x) &&
					min_dist > abs(i - j)
					)
				{
					min_dist = abs(i - j);
				}
			}
		}

		if (min_dist != INT_MAX)
		{
			dist = min_dist;
			return true;
		}
		return false;
	}

	bool TrickyMethod(int arr[], int n, int x, int y, int &dist)
	{
		int prevX = -1, prevY = -1;

		for (int i = 0; i < n; i++)
		{
			if (
				arr[i] == x	&&
				(-1 == prevY || -1 == prevX ||  (-1 != prevX && -1 != prevY && abs(prevX-prevY) > abs(i-prevY)))
				)
				prevX = i;
			if (arr[i] == y &&
				(-1 == prevX || -1 == prevY || (-1 != prevX && -1 != prevY && abs(prevX - prevY) > abs(i - prevX)))
				)
				prevY = i;
		}

		if (-1 == prevX || -1 == prevY)
			return false;

		dist = abs(prevX - prevY);
		return true;
	}
};

void findmaxmin(int arr[], int low, int high, int& max, int& min)
{
	if (low == high)
	{
		if (max < arr[low]) max = arr[low];
		if (min > arr[low]) min = arr[low];
		return;
	}

	if (low == high - 1)
	{
		if (arr[low] < arr[high])
		{
			if (min > arr[low]) min = arr[low];
			if (max < arr[high]) max = arr[high];
		}
		else
		{
			if (min > arr[high]) min = arr[high];
			if (max < arr[low]) max = arr[low];
		}

		return;
	}

	int mid = (low + high) / 2;
	findmaxmin(arr, low, mid, max, min);
	findmaxmin(arr, mid+1, high, max, min);
}

void entry_point()
{
	CMinDistanceBetweenTwoIntegersInArray min;
	int arr[] = { 1, 2 };
	int dist0 = -1;
	bool ret = min.TrivialMethod(arr, 2, 1, 2, dist0);
	//int arr[] = { 6,4,3};
	//int dist = -1;
	//bool ret = min.TrivialMethod(arr, 3, 3, 6, dist);
	//int arr[] = { 3, 5, 4, 2, 6, 5, 6, 6, 5, 4, 3, 9 };
	//int dist = -1;
	//bool ret = min.TrivialMethod(arr, 12, 3, 6, dist);
	int arr4[] = { 1, 2 };
	int dist = -1;
	bool ret = min.TrickyMethod(arr4, 2, 1, 2, dist);
	int arr1[] = { 6,4,3};
	dist = -1;
	ret = min.TrickyMethod(arr1, 3, 3, 6, dist);
	int arr2[] = { 3, 4, 6, 3};
	dist = -1;
	ret = min.TrickyMethod(arr2, 4, 3, 6, dist);
	int arr3[] = { 3, 6, 4, 3 };
	dist = -1;
	ret = min.TrickyMethod(arr3, 4, 3, 6, dist);	

	int arr8[] = {4,3,2,1,5,6,7};
	int min = INT_MAX, max = INT_MIN;
	findmaxmin(arr8, 0, _countof(arr8)-1, max, min);	
}
