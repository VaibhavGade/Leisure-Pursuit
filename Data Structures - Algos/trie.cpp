class CTrie
{
public:
	struct TrieNode
	{
		map<char, TrieNode*> Children;
		bool endofWord;
		TrieNode()
		{
			endofWord = false;
		}
	};

	TrieNode root;

	CTrie()
	{
	}

	~CTrie()
	{
	}

	void insert(string word)
	{
		TrieNode *current = &root;

		for (int i = 0; i < word.length(); i++)
		{
			char ch = word.at(i);
			if (current->Children.end() == current->Children.find(ch))
			{
				TrieNode *node = new TrieNode;
				current->Children[ch] = node;
				current = node;
			}
		}
		current->endofWord = true;
	}

	void insert_recur_outer(string word)
	{
		insert_recur(&root, word, 0);
	}

	void insert_recur(TrieNode* current, string word, int index)
	{
		if (index == word.length())
		{
			current->endofWord = true;
			return;
		}

		char ch = word.at(index);
		if (current->Children.end() == current->Children.find(ch))
		{
			TrieNode *node = new TrieNode;
			current->Children[ch] = node;
			current = node;
			insert_recur(current, word, index + 1);
		}
	}

	bool search_recur_outer(string word)
	{
		return search_recur(&root, word, 0);
	}

	bool search_recur(TrieNode *current, string word, int index)
	{
		if (index == word.length())
		{
			return current->endofWord;
		}

		char ch = word.at(index);
		map<char, TrieNode*>::iterator it;
		it = current->Children.find(ch);
		if (current->Children.end() == it)
		{
			return false;
		}

		return search_recur(it->second, word, index+1);
	}

	bool search(string word)
	{
		TrieNode *current = &root;
		map<char, TrieNode*>::iterator it;
		for (int i = 0; i < word.length(); i++)
		{
			char ch = word.at(i);
			it = current->Children.find(ch);
			if (current->Children.end() == it)
			{
				return false;
			}
			else
			{
				current = it->second;
			}
		}
		return current->endofWord;
	}

	bool delete_recur(TrieNode *current, string word, int index)
	{
		if (index == word.length())
		{
			if (!current->endofWord)
				return false;
			return current->Children.size() == 0;
		}

		map<char, TrieNode*>::iterator it;
		char ch = word.at(index);
		it = current->Children.find(ch);
		if (it == current->Children.end())
			return false;
		bool shouldDeleteCurrentNode = delete_recur(it->second, word, index+1);

		if (shouldDeleteCurrentNode)
		{
			current->Children.erase(ch);
			return current->Children.size() == 0;
		}

		return false;
	}

	void _delete(string word)
	{
		delete_recur(&root, word, 0);
	}
}
