class CWordFreq
{
	ifstream wordfile;
	map<string, int64_t> wordCountMap;

public:
	CWordFreq(const string &filename);
	~CWordFreq();

	void CountWords()
	{
		string fileContents;
		wordfile.seekg(0, ios::end);
		fileContents.resize(wordfile.tellg());
		wordfile.seekg(0, ios::beg);
		wordfile.read(&fileContents[0], fileContents.size());

		string alnum= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
		ostringstream os;

		string::iterator current = fileContents.begin();
		string::iterator next = current;

		while (1)
		{
			if (next == fileContents.end() && os.str() != "")
			{
				wordCountMap[os.str()]++;
				break;
			}

			if (alnum.find(*next) == string::npos)
			{
				wordCountMap[os.str()]++;
				while ((next != fileContents.end()) && (alnum.find(*next)) == string::npos)
				{
					next++;
				}
				os.str("");
			}
			else
			{
				if (*next <= 'Z' && *next >= 'A')
					os << char(*next - ('Z' - 'z'));
				else
					os << (*next);
				next++;
			}
		}
	}

	const size_t getWordCount()
	{
		return wordCountMap.size();
	}

	const int64_t getWordFreq(const string &word) const
	{
		if (wordCountMap.find(word) != wordCountMap.end())
		{
			return wordCountMap.at(word);
		}
		return 0;
	}

	int64_t getDotProduct(const CWordFreq &wordFreq)
	{
		int64_t acc = 0;

		for (map<string, int64_t>::iterator it = wordCountMap.begin(); it != wordCountMap.end(); it++)
		{
			acc += (this->getWordFreq(it->first)) * (wordFreq.getWordFreq(it->first));
		}
		return acc;
	}
};


CWordFreq::CWordFreq(const string &filename):wordfile(filename)
{
	if (!wordfile)
	{
		ostringstream os;
		os << "Could not open file" << filename;
		throw runtime_error(os.str());
	}
}

CWordFreq::~CWordFreq()
{
}

void entry_point(int argc, char**argv)
{
	if (argc < 2)
	{
		cerr << "Insufficient args" << endl;
		return 1;
	}

	CWordFreq file1(argv[1]);
	file1.CountWords();
	CWordFreq file2(argv[2]);
	file2.CountWords();
	cout << "Distinct words from file1:" << file1.getWordCount() << endl;
	cout << "Distinct words from file2:" << file2.getWordCount() << endl;

	int64_t t1 = file1.getDotProduct(file2);

	double t2 = (double)file1.getDotProduct(file1);
	double t3 = (double)file2.getDotProduct(file2);
	t2 = sqrt(t2*t3);

	cout << "Document distance is " << acos(t1/t2) << "\n";
}
