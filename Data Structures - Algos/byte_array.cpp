class CByteArray
{
public:
	WORD m_wcbMaxSize;
	WORD m_wcbDataSize;

	CByteArray()
	{
		m_wcbMaxSize = 0;
		m_wcbDataSize = 0;
		m_pArr = NULL;
	}

	CByteArray(WORD wSize)
	{
		m_wcbMaxSize = wSize;
		m_wcbDataSize = 0;
		m_pArr = (BYTE*)malloc(wSize);
	}

	~CByteArray()
	{
		if (m_pArr)
		{
			free(m_pArr);
			m_wcbMaxSize = 0;
			m_wcbDataSize = 0;
			m_pArr = NULL;
		}
	}

	BYTE * m_pArr;

	bool Resize(WORD wSize)
	{
		if (m_pArr)
			free(m_pArr);

		m_pArr = (BYTE*)malloc(wSize);
		if (NULL == m_pArr)
		{
			return false;
		}

		m_wcbMaxSize = wSize;
		m_wcbDataSize = 0;
		return true;
	}

	bool Add(const BYTE* pcbyBuffer, DWORD dwcbBuffer)
	{
		if (!m_pArr)
			return false;

		if (m_wcbDataSize == m_wcbMaxSize)
			return false;

		WORD wcbDataToCopy = min(dwcbBuffer, m_wcbMaxSize - m_wcbDataSize);
		memcpy(m_pArr + m_wcbDataSize, pcbyBuffer, wcbDataToCopy);
		m_wcbDataSize += wcbDataToCopy;

		return true;
	}
};

void entry_point()
{
	CByteArray obj(5);
	if (!obj.m_pArr) return 0;

	BYTE byBuffer[] = { 0,1,2,3,4 };
	WORD wcbBuffer = sizeof(byBuffer);
	obj.Add(byBuffer, wcbBuffer);

	obj.Resize(3);

	BYTE byBuffer1[] = { 2,3,4,5 };
	WORD wcbBuffer1 = sizeof(byBuffer1);
	obj.Add(byBuffer1, wcbBuffer1);

	BYTE byBuffer2[] = { 6,7 };
	WORD wcbBuffer2 = sizeof(byBuffer2);
	obj.Add(byBuffer2, wcbBuffer2);
}
