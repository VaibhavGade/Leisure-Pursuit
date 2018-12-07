namespace segment_tree
{
	class CSegmentTree
	{
	public:
		void buildTree(int tree[], int arr[], int index, int low, int high)
		{
			if (low == high)
				tree[index] = arr[low];
			else
			{
				int mid = (low + high) >> 1;
				buildTree(tree, arr, index * 2 + 1, low, mid);
				buildTree(tree, arr, index * 2 + 2, mid + 1, high);
				tree[index] = min(tree[index * 2 + 1], tree[index * 2 + 2]);
			}
		}
		//-1,-1,0,-1,2,4,0
		static void driver()
		{
			int arr[] = { -1,2,4,0 };
			int input_size = _countof(arr);
			int segment_tree_size = nextPowerOf2(_countof(arr)) * 2 - 1;
			int *out = new int[segment_tree_size];
			CSegmentTree obj;
			obj.buildTree(out, arr, 0, 0, input_size - 1);
			int min = obj.rangeQuery(out, 0, 0, input_size - 1, 1, 3);
		}

		int rangeQuery(int tree[], int index, int low, int high, int l, int r)
		{
			//	No overlap
			if (l > r) return INT_MAX;
			//	Total overlap
			if (l == low && r == high) return tree[index];
			int mid = (low + high) >> 1;
			return min(rangeQuery(tree, 2 * index + 1, low, mid, l, min(r, mid)), rangeQuery(tree, 2 * index + 2, mid + 1, high, max(l, mid + 1), r));
		}
	};
}
