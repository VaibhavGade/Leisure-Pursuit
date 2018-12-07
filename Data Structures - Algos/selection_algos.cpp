namespace selection
{
	class CQuick_Select
	{
		int random_partition(int arr[], int low, int high)
		{
			int n = high - low + 1;
			int random_index = rand() % n;
			swap(arr[random_index], arr[high]);
			return partition(arr, low, high);
		}

		int partition(int arr[], int low, int high)
		{
			int pivot = arr[high];
			int smaller = low;
			for (int j = low; j < high; j++)
			{
				if (arr[j] <= pivot)
				{
					swap(arr[j], arr[smaller]);
					smaller++;
				}
			}

			swap(arr[high], arr[smaller]);
			return smaller;
		}

		int KthSmallest(int arr[], int low, int high, int k)
		{
			if (k >= low && k <= high)
			{
				int Index = random_partition(arr, low, high);
				//int Index = partition(arr, low, high);
				if (k == Index)
					return arr[Index];
				if (k < Index)
					return KthSmallest(arr, low, Index-1, k);

				return KthSmallest(arr, Index + 1, high, k);
			}

			return INT_MAX;
		}

	public:
		void quick_selection_caller()
		{
			int arr[] = { 111, 33, 22, 66, 44, 55, 77, 99, 11, 88 };

			int count = sizeof(arr) / sizeof(arr[0]);
			int k;
			do
			{
				cout << "Enter k: ";
				cin >> k;
				cout << KthSmallest(arr, 0, count - 1, k-1) << endl;
			} while (k != -1);
		}
	};
}
