class CInt2Darray
{
	int m_iRows, m_iCols;

public:
	bool **m_arr;

	CInt2Darray(int nRows = 0, int nCols = 0, bool bDefaultVal = false) : m_arr(NULL), m_iRows(nRows), m_iCols(nCols)
	{
		if (0 == nRows || 0 == nCols)
			return;

		m_arr = new bool*[nRows];
		for (int i = 0; i < nRows; ++i)
		{
			m_arr[i] = new bool[nCols];
			for (int j = 0; j < nCols; ++j)
			{
				m_arr[i][j] = bDefaultVal;
			}
		}
	}

	~CInt2Darray()
	{
		for (int i = 0; i < m_iRows; ++i) {
			delete[] m_arr[i];
		}
		delete[] m_arr;
		m_arr = NULL;
	}
}
