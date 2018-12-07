class LCS
{
	unordered_map<string, int> lookup;
public:
	int lcs(string s1, string s2, int len1, int len2)
	{
		if (s1.length() == len1 || s2.length() == len2)
		{
			return 0;
		}
		
		string key = to_string(len1) + "|" + to_string(len2);

		if (lookup.find(key) == lookup.end())
		{
			if (s1[len1] == s2[len2])
			{
				return 1 + lcs(s1, s2, len1 + 1, len2 + 1);
			}
			else
			{
				return max(lcs(s1, s2, len1 + 1, len2), lcs(s1, s2, len1, len2 + 1));
			}
		}
		else return lookup[key];
	}

	void entry_point()
	{
		string str1 = "ABCDAF";
		string str2 = "ACBCF";
		int i = lcs(str1, str2, 0, 0);
		int j = 1 + 2;
	}
};
