class CPatterns
{
public:
#if 1
	// Function to determine if given pattern matches with a string or not
	bool match(string str, int i, string pat, int j, unordered_map<char, string>& map)
	{
		int n = str.size(), m = pat.size();

		// base condition
		if (n < m)
			return false;

		// if both pattern and the string reaches end
		if (i == n && j == m)
			return true;

		// if either string or pattern reaches end
		if (i == n || j == m)
			return false;

		// consider next character from the pattern
		char curr = pat[j];

		// if the character is seen before
		if (map.find(curr) != map.end())
		{
			string s = map[curr];
			int k = s.size();

			// return false if next k characters of the given string
			// doesn't match with s
			if (str.substr(i, k).compare(s))
				return false;

			// recurse for remaining characters if next k characters matches
			return match(str, i + k, pat, j + 1, map);
		}

		// process all remaining characters in the string if currrent character is
		// never seen before
		for (int k = 1; k <= n - i; k++)
		{
			// insert substring formed by next k characters of the string
			// into the map
			map[curr] = str.substr(i, k);

			// check if it leads to the solution
			if (match(str, i + k, pat, j + 1, map))
				return true;

			// else backtrack - remove current character from the map
			map.erase(curr);
		}

		return false;
	}
#endif
}

void entry_point()
{
	CPatterns patternobj;

	// input string and pattern
	string str = "codeparicode";
	string pat = "XYX";

	// create a map to store mappings between the pattern and string
	unordered_map<char, string> map;

	// check for solution
	if (patternobj.match(str, 0, pat, 0, map)) {
		for (auto entry : map) {
			cout << entry.first << ": " << entry.second << endl;
		}
	}
	else {
		cout << "Solution doesn't exist";
	}
}
