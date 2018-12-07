class CWildChars
{
public:

	void
		RemoveUnwantedAsterisks(
		wstring wsPattern,
		wstring &wsProcessedPattern
		)
	{
		int iIndex = -1;
		bool bFirst = true;
		size_t stLen = wsPattern.length();
		while (++iIndex < stLen)
		{
			if (L'*' == wsPattern[iIndex])
			{
				if (true == bFirst)
				{
					wsProcessedPattern.push_back(wsPattern[iIndex]);
					bFirst = false;
				}
			}
			else
			{
				wsProcessedPattern.push_back(wsPattern[iIndex]);
				bFirst = true;
			}
		}
	}


	bool test(wstring wsText, wstring wsPattern)
	{

		//
		//	Replace occurence of ** with *
		//	e.g.: a**b to a*b
		//
		wstring wsProcessedPattern;
		RemoveUnwantedAsterisks(wsPattern, wsProcessedPattern);

		size_t stTextLength = wsText.length() + 1;
		size_t stPatternLength = wsProcessedPattern.length() + 1;

		CInt2Darray arr(stTextLength, stPatternLength);
		bool **T = arr.m_arr;
		T[0][0] = true;

		if (stPatternLength > 0 && wsProcessedPattern[0] == L'*')
		{
			T[0][1] = true;
		}

		for (int i = 1; i < stTextLength; i++) {
			for (int j = 1; j < stPatternLength; j++) {
				if (wsProcessedPattern[j - 1] == L'?' || wsProcessedPattern[j - 1] == wsText[i - 1]) {
					T[i][j] = T[i - 1][j - 1];
				}
				else if (wsProcessedPattern[j - 1] == '*') {
						T[i][j] = T[i - 1][j] | T[i][j - 1];
				}
			}
		}

		return T[stTextLength - 1][stPatternLength - 1];
	}
};

void entry_point()
{
	CWildChars rx;
	unsigned char ch;
	do
	{
		cout << "enter string:";
		wstring wsText;
		wcin >> wsText;
		cout << "enter pattern:";
		wstring wsPattern;
		wcin >> wsPattern;
		bool bret = rx.test(wsText, wsPattern);
		cout << endl << bret <<endl;
		cout << "enter \'x\' to exit, other character to continue: ";
		cin >> ch;
	} while ('x' != ch);
}
