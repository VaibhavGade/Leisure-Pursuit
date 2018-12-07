class CMyPriorityQ
{
public:
	CMyPriorityQ();
	~CMyPriorityQ();

	void Try_MaxPQ()
	{
		priority_queue<int> pq;
		pq.push(8);
		pq.push(4);
		pq.push(10);
		pq.push(1);

		while (!pq.empty())
		{
			cout << pq.top() << endl;
			pq.pop();
		}
	}

	struct compare
	{
		bool operator()(const int &l, const int &r)
		{
			return l > r;
		}
	};

	void Try_MinPQ(vector<int> &rvtData)
	{
		//priority_queue<int, vector<int>, compare> pq;
		priority_queue<int, vector<int>, greater<int>> pq(rvtData.begin(), rvtData.begin() + 2);
	/*	pq.push(8);
		pq.push(4);
		pq.push(10);
		pq.push(1);
*/
		while (!pq.empty())
		{
			cout << pq.top() << endl;
			pq.pop();
		}
	}

	int FindElemWithMinHeap(vector<int> &A, int k)
	{
		priority_queue<int, vector<int>, greater<>> pq(A.begin(), A.begin() + k);
		for (int i = k; i < A.size(); i++)
		{
			if (A[i] > pq.top())
			{
				pq.pop();
				pq.push(A[i]);
			}
		}
		return pq.top();
	}

	int FindElemWithMaxHeap(vector<int> &A, int k)
	{
		priority_queue<int, vector<int>> pq(less<int>(), A);
		while (--k) pq.pop();
		return pq.top();
	}
};

CMyPriorityQ::CMyPriorityQ()
{
}

CMyPriorityQ::~CMyPriorityQ()
{
}

void entry_point()
{
	vector<int> data = {1,2,3,4,5,6};
	CMyPriorityQ pq;
	pq.Try_MinPQ(data);
	cout << pq.FindElemWithMinHeap(data, 3) << endl;
	cout << pq.FindElemWithMaxHeap(data, 3) << endl;
}
