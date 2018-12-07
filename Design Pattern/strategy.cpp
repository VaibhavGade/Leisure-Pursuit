/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	S T R A T E G Y	 D P
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class IComparator
{
public:
	virtual bool compare(int a, int b) = 0;
	virtual ~IComparator() {}
};

class LesserComprataor : public IComparator
{
public:
	bool compare(int a, int b)
	{
		if (a > b)
			return true;
		else
			return false;
	}
};


class GreaterComprataor : public IComparator
{
public:
	bool compare(int a, int b)
	{
		if (a < b)
			return true;
		else
			return false;
	}
};

class SortingAlgo
{
	IComparator * m_pComparator;
	void swap(int &x, int &y)
	{
		int tmp = x;
		x = y;
		y = tmp;
	}

public:
	SortingAlgo()
	{
		m_pComparator = new LesserComprataor();
	}

	void sort(std::vector<int> & arr, IComparator * pComparator = NULL)
	{
		if (pComparator == NULL)
			pComparator = m_pComparator;

		bool isSwapped = true;
		int x = 0;
		while (isSwapped)
		{
			isSwapped = false;
			x++;
			for (int i = 0; i < arr.size() - x; i++)
			{
				if (pComparator->compare(arr[i], arr[i + 1]))
				{
					swap(arr[i], arr[i + 1]);
					isSwapped = true;
				}
			}
		}
	}
};

int strategy_dp()
{
	std::vector<int> arr = { 1,5,2,4,3 };
	SortingAlgo obj;
	IComparator * pComp = new LesserComprataor();
	obj.sort(arr, pComp);
	for (int var = 0; var < 5; ++var) {
		std::cout << arr[var] << " ";
	}
	std::cout << std::endl;
	delete pComp;
	pComp = NULL;

	pComp = new GreaterComprataor();
	obj.sort(arr, pComp);
	for (int var = 0; var < 5; ++var) {
		std::cout << arr[var] << " ";
	}
	std::cout << std::endl;
	delete pComp;
	pComp = NULL;

	delete pComp;
	pComp = NULL;

	obj.sort(arr);
	for (int var = 0; var < 5; ++var) {
		std::cout << arr[var] << " ";
	}
	std::cout << std::endl;
	delete pComp;
	pComp = NULL;

	return 0;
}
