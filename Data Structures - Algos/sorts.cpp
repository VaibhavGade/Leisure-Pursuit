namespace sort
{
	class CHeapSort
	{
		void Heapify(int arr[], int i, int count)
		{
			int largest = i;
			int left = 2 * i + 1;
			int right = 2 * i + 2;

			if (left < count && arr[left] > arr[largest])
			{
				largest = left;
			}

			if (right < count && arr[right] > arr[largest])
			{
				largest = right;
			}

			if (largest != i)
			{
				std::swap(arr[largest], arr[i]);
				Heapify(arr, largest, count);
			}
		}

	public:
		void HeapSort(int arr[], int begin, int end)
		{
			int count = end - begin;

			for (int i = (count / 2) - 1; i >= begin; i--)
			{
				Heapify(arr, i, count);
			}

			for (int i = count - 1; i > begin; i--)
			{
				std::swap(arr[begin], arr[i]);
				Heapify(arr, begin, i);
			}
		}

		void HeapSort_Caller()
		{
			int arr[] = { 11, 33, 22, 66, 44, 55, 77, 99, 111, 88 };
			HeapSort(arr, 0, _countof(arr));
		}
	};

	class CSelectionSort
	{
	public:
		void selectionsort()
		{
			int i, j, min_idx;

			int arr[] = { 11, 33, 22, 66, 44, 55, 77, 99, 111, 88 };

			int count = sizeof(arr) / sizeof(arr[0]);

			// One by one move boundary of unsorted subarray 
			for (i = 0; i < count - 1; i++)
			{
				// Find the minimum element in unsorted array 
				min_idx = i;
				for (j = i + 1; j < count; j++)
					if (arr[j] < arr[min_idx])
						min_idx = j;

				// Swap the found minimum element with the first element 
				std::swap(arr[min_idx], arr[i]);
			}
		}

		void stable_selectionsort()
		{
			int i, j, min_idx;

			int arr[] = { 11, 33, 22, 66, 44, 55, 77, 99, 111, 88 };

			int count = sizeof(arr) / sizeof(arr[0]);

			// One by one move boundary of unsorted subarray 
			for (i = 0; i < count - 1; i++)
			{
				// Find the minimum element in unsorted array 
				min_idx = i;
				for (j = i + 1; j < count; j++)
					if (arr[j] < arr[min_idx])
						min_idx = j;

				// Move minimum element at current i. 
				int key = arr[min_idx];
				while (min_idx > i)
				{
					arr[min_idx] = arr[min_idx - 1];
					min_idx--;
				}
				arr[i] = key;

				// Swap the found minimum element with the first element 
				//std::swap(arr[min_idx], arr[i]);
			}
		}

		void selectionsort_strings(char arr[][MAX_PATH], int count)
		{
			int i, j, min_idx;
			char minstr[MAX_PATH];

			// One by one move boundary of unsorted subarray 
			for (i = 0; i < count - 1; i++)
			{
				// Find the minimum element in unsorted array 
				min_idx = i;
				for (j = i + 1; j < count; j++)
					if (strcmp(arr[j], arr[min_idx]) < 0)
						min_idx = j;

				if (min_idx != i)		// Swap the found minimum element with the first element 
				{
					std::swap(arr[min_idx], arr[i]);
				}
			}
		}
	};

	class CInsertionSort
	{
	public:

		void InsertionSort_Recursive(int arr[], int count)
		{
			if (count <= 1) return;
			InsertionSort_Recursive(arr, count - 1);

			int key = arr[count-1];
			int j = count - 2;

			/* Move elements of arr[0..i-1], that are
			greater than key, to one position ahead
			of their current position */
			while (j >= 0 && arr[j] > key)
			{
				arr[j + 1] = arr[j];
				j = j - 1;
			}
			arr[j + 1] = key;
		}

		void recur()
		{
			int arr[] = { 111, 33, 22, 66, 44, 55, 77, 99, 11, 88 };

			int count = sizeof(arr) / sizeof(arr[0]);

			InsertionSort_Recursive(arr, count);
		}

		void InsertionSort(int arr[], int begin, int count)
		{
			int i, key, j;
			for (i = begin + 1; i < count; i++)
			{
				key = arr[i];
				j = i - 1;

				/* Move elements of arr[0..i-1], that are
				greater than key, to one position ahead
				of their current position */
				while (j >= begin && arr[j] > key)
				{
					arr[j + 1] = arr[j];
					j = j - 1;
				}
				arr[j + 1] = key;
			}
		}

		void InsertionSort_Caller()
		{
			int arr[] = { 111, 33, 22, 66, 44, 55, 77, 99, 11, 88 };

			int count = sizeof(arr) / sizeof(arr[0]);
			InsertionSort(arr, 0, count);
		}

		int binarysearch(int a[], int key, int low, int high)
		{
			if (high <= low)
				return (key > a[low]) ? (low + 1) : low;

			int mid = (low + high) / 2;
			if (key == a[mid])
				return mid + 1;

			if (key > a[mid])
				return binarysearch(a, key, mid + 1, high);

			return binarysearch(a, key, low, mid - 1);
		}

		void InsertionSort_BinarySearch()
		{
			int arr[] = { 111, 33, 22, 66, 44, 55, 77, 99, 11, 88 };

			int count = sizeof(arr) / sizeof(arr[0]);

			int i, key, j, loc;
			for (i = 1; i < count; i++)
			{
				key = arr[i];
				j = i - 1;

				loc = binarysearch(arr, key, 0, j);

				/* Move elements of arr[0..i-1], that are
				greater than key, to one position ahead
				of their current position */
				while (j >= loc)
				{
					arr[j + 1] = arr[j];
					j = j - 1;
				}
				arr[j + 1] = key;
			}
		}

		typedef struct node
		{
			int data;
			struct node *next;

			node()
			{
				data = -1; next = NULL;
			}

		} NODE, *P_NODE, **PP_NODE;

		void push(PP_NODE head, int data)
		{
			P_NODE temp = new NODE;
			temp->data = data;
			temp->next = *head;
			*head = temp;
		}

		void print(P_NODE head)
		{
			for (P_NODE runner = head; runner; runner = runner->next)
				cout << runner->data << "	";
		}

		void sorted_insert_linked_list(PP_NODE head, P_NODE newNode)
		{
			if (*head == NULL || (*head)->data > newNode->data)
			{
				newNode->next = *head;
				*head = newNode;
				return;
			}

			P_NODE runner = *head;
			while (runner->next && runner->next->data < newNode->data)
				runner = runner->next;

			newNode->next = runner->next;
			runner->next = newNode;
		}

		void insertion_sort_linked_list(PP_NODE head)
		{
			P_NODE sortedlist = NULL;

			for (P_NODE runner = *head; runner;)
			{
				P_NODE next = runner->next;
				sorted_insert_linked_list(&sortedlist, runner);
				runner = next;
			}

			*head = sortedlist;
		}

		void insertion_sort_linked_list_caller()
		{
			P_NODE list = NULL;

			int arr[] = { 111, 33, 22, 66, 44, 55, 77, 99, 11, 88 };
			for (auto i : arr)
			{
				push(&list, i);
			}

			insertion_sort_linked_list(&list);
			print(list);
		}
	};

	class CQuickSort
	{
	public:
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

		void quick_sort(int arr[], int low, int high)
		{
			if (low < high)
			{
				int pivot = partition(arr, low, high);
				quick_sort(arr, 0, pivot - 1);
				quick_sort(arr, pivot + 1, high);
			}
		}

		void InPlaceQuickSort(int arr[], int a, int b)
		{
			if (a >= b) return;

			int pivot = arr[b];
			int l = a;
			int r = b - 1;

			while (l <= r)
			{
				while ((l <= r) && (arr[l] <= pivot))
					l++;
				while ((r >= l) && (arr[r] >= pivot))
					r--;
				if (l < r)
					swap(arr[l], arr[r]);
			}

			swap(arr[l], arr[b]);
			InPlaceQuickSort(arr, a, l - 1);
			InPlaceQuickSort(arr, l + 1, b);
		}

		void quick_sort_caller()
		{
			int arr[] = { 111, 33, 22, 66, 44, 55, 77, 99, 11, 88 };

			int count = sizeof(arr) / sizeof(arr[0]);

			InPlaceQuickSort(arr, 0, count - 1);
			//quick_sort(arr, 0, count - 1);
		}
	};

	class CIntrosort
	{
		int* MedianOf3(int *start, int *mid, int *end)
		{
			if ((*mid < *start && *start < *end) ||(*end < *start && *start < *mid))
			{
				return start;
			}

			if ((*start < *mid && *mid < *end) || (*end < *mid && *mid < *start))
			{
				return mid;
			}

			if ((*start < *end && *end < *mid) || (*mid < *end && *end < *start))
			{
				return end;
			}

			return end;
		}

		void IntroSort(int arr[], int l, int r, int depthlimit)
		{
			if (r < l) return;

			if (16 >= ((r+1) - l))
			{
				CInsertionSort InsertionSortObj;
				return InsertionSortObj.InsertionSort(arr, l, r+1);
			}

			if (0 == depthlimit)
			{
				CHeapSort HeapSortObj;
				HeapSortObj.HeapSort(arr, l, r + 1);
				return;
			}

			int *pivot = MedianOf3(&arr[l], &arr[(l + r) / 2], &arr[r]);
			if (pivot != &(arr[r]))
			{
				swap(arr[r], *pivot);
			}

			CQuickSort QuickSortObj;
			int partition_index = QuickSortObj.partition(arr, l, r);
			IntroSort(arr, l, partition_index - 1, depthlimit-1);
			IntroSort(arr, partition_index + 1, r, depthlimit-1);
		}

		public:
		void intro_sort_entry_point()
		{
			while (1)
			{
				cout << "Enter n: ";
				int count;
				cin >> count;
				if (count < 0) break;
				int *arr = new int[count];

				//= { 111, 33, 22, 66, 44, 55, 77, 99, 11, 88, 131, 121, 151, 141,161, 181, 201, 211, 192, 171, 291, 301, 271,231,221, 211, 261, 281,251,241 };

				for (int i = 1, j = count; i <= count; i++)
				{
					arr[i - 1] = j--;
				}

				IntroSort(arr, 0, count - 1, (2 * log(count)));
				delete[]arr;
			}
		}
	};
}
