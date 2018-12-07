class CPeakFinder
{
public:
	int Find1DPeakUtil(int arr[], int low, int high, int n)
	{
		int mid = (low + high) / 2;
		if (mid == 0 || mid == n - 1 || (arr[mid] > arr[mid + 1] && arr[mid] > arr[mid - 1]))
			return arr[mid];

		if (arr[mid] < arr[mid - 1])
			return Find1DPeakUtil(arr, low, mid - 1, n);

		return Find1DPeakUtil(arr, mid + 1, high, n);
	}

	int Find1DPeak(int arr[], int n)
	{
		return Find1DPeakUtil(arr, 0, n - 1, n);
	}

	int FindMax(int arr[][10], int row, int column, int &max)
	{
		int Max_index;
		for (int i = 0; i < row; i++)
		{
			if (max < arr[i][column])
			{
				max = arr[i][column];
				Max_index = i;
			}
		}

		return Max_index;
	}

	int div_ceil(int numerator, int denominator)
	{
		std::div_t res = std::div(numerator, denominator);
		return res.rem ? (res.quot + 1) : res.quot;
	}

	int Find2DPeak(int arr[][10], int rows, int columns, int mid)
	{
		int max = 0;
		int max_index = FindMax(arr, rows, mid, max);

		if (
			((mid - 1) >= 0 && max > arr[max_index][mid - 1]) &&
			((mid + 1) <= (columns - 1) && max > arr[max_index][mid + 1])
			)
		{
			return arr[max_index][mid];
		}
		else if ((mid - 1) >= 0 && max < arr[max_index][mid - 1])
		{
			int temp_mid = div_ceil(mid, 2);
			return Find2DPeak(arr, rows, columns, mid - temp_mid);
		}
		else if ((mid != 0) && (mid + 1) <= (columns - 1) && max > arr[max_index][mid + 1])
		{
			int temp_mid = div_ceil(mid, 2);
			return Find2DPeak(arr, rows, columns, mid + temp_mid);
		}

		return max;
	}
};

void entry_point()
{
#if 0
	CPeakFinder PeakFinder;
	int arr[] = { 1, 3, 20, 4, 1, 0 };
	int peak = PeakFinder.Find1DPeak(arr, _countof(arr));
	int arr1[] = { 5, 10, 20, 15 };
	peak = PeakFinder.Find1DPeak(arr1, _countof(arr1));
	int arr2[] = { 10, 20, 15, 2, 23, 90, 67 };
	peak = PeakFinder.Find1DPeak(arr2, _countof(arr2));
	int arr3[] = { 10, 20, 30, 40, 50 };
	peak = PeakFinder.Find1DPeak(arr3, _countof(arr3));
	int arr4[] = { 100, 80, 60, 50, 20 };
	peak = PeakFinder.Find1DPeak(arr4, _countof(arr4));
#endif

#if 0
	CPeakFinder PeakFinder;
	int arr[][10] = {
					{1,2,3},
					{4,5,6},
					{7,8,9}
				};
	int peak = PeakFinder.Find2DPeak(arr, 3, 3, 3/2);

	int arr1[][10] = {
					{ 2,3 },
					{ 6,5 },
				};
	peak = PeakFinder.Find2DPeak(arr1, 2, 2, 2 / 2);
#endif

#if 0
	int arr1[] = { 5, 10, 20, 15 };
	peak = PeakFinder.Find1DPeak(arr1, _countof(arr1));
	int arr2[] = { 10, 20, 15, 2, 23, 90, 67 };
	peak = PeakFinder.Find1DPeak(arr2, _countof(arr2));
	int arr3[] = { 10, 20, 30, 40, 50 };
	peak = PeakFinder.Find1DPeak(arr3, _countof(arr3));
	int arr4[] = { 100, 80, 60, 50, 20 };
	peak = PeakFinder.Find1DPeak(arr4, _countof(arr4));
#endif
}
