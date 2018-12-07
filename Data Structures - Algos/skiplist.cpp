namespace skiplist
{
	// Class to implement node 
	class Node
	{
	public:
		int key;

		// Array to hold pointers to node of different level 
		Node **forward;
		Node(int, int);
	};

	Node::Node(int key, int level)
	{
		this->key = key;

		// Allocate memory to forward 
		forward = new Node*[level + 1];

		// Fill forward array with 0(NULL) 
		memset(forward, 0, sizeof(Node*)*(level + 1));
	};

	// Class for Skip list 
	class CSkipList
	{
		// Maximum level for this skip list 
		int MAXLVL;

		// P is the fraction of the nodes with level 
		// i pointers also having level i+1 pointers 
		float P;

		// current level of skip list 
		int level;

		// pointer to header node 
		Node *header;
	public:
		CSkipList(int, float);
		int randomLevel();
		Node* createNode(int, int);
		void insertElement(int);
		void displayList();
		static void driver();
		void searchElement(int key);
		void deleteElement(int key);
	};

	CSkipList::CSkipList(int MAXLVL, float P)
	{
		this->MAXLVL = MAXLVL;
		this->P = P;
		level = 0;

		// create header node and initialize key to -1 
		header = new Node(-1, MAXLVL);
	};

	// create random level for node 
	int CSkipList::randomLevel()
	{
		float r = (float)rand() / RAND_MAX;
		int lvl = 0;
		while (r < P && lvl < MAXLVL)
		{
			lvl++;
			r = (float)rand() / RAND_MAX;
		}
		return lvl;
	};

	// create new node 
	Node* CSkipList::createNode(int key, int level)
	{
		Node *n = new Node(key, level);
		return n;
	};

	// Insert given key in skip list 
	void CSkipList::insertElement(int key)
	{
		Node *current = header;
		// create update array and initialize it 
		Node **update = new Node*[MAXLVL + 1];
		memset(update, 0, sizeof(Node*)*(MAXLVL + 1));

		/* start from highest level of skip list
		move the current pointer forward while key
		is greater than key of node next to current
		Otherwise inserted current in update and
		move one level down and continue search
		*/
		for (int i = level; i >= 0; i--)
		{
			while (current->forward[i] != NULL &&
				current->forward[i]->key < key)
				current = current->forward[i];
			update[i] = current;
		}

		/* reached level 0 and forward pointer to
		right, which is desired position to
		insert key.
		*/
		current = current->forward[0];

		/* if current is NULL that means we have reached
		to end of the level or current's key is not equal
		to key to insert that means we have to insert
		node between update[0] and current node */
		if (current == NULL || current->key != key)
		{
			// Generate a random level for node 
			int rlevel = randomLevel();

			// If random level is greater than list's current 
			// level (node with highest level inserted in 
			// list so far), initialize update value with pointer 
			// to header for further use 
			if (rlevel > level)
			{
				for (int i = level + 1; i<rlevel + 1; i++)
					update[i] = header;

				// Update the list current level 
				level = rlevel;
			}

			// create new node with random level generated 
			Node* n = createNode(key, rlevel);

			// insert node by rearranging pointers 
			for (int i = 0; i <= rlevel; i++)
			{
				n->forward[i] = update[i]->forward[i];
				update[i]->forward[i] = n;
			}
			cout << "Successfully Inserted key " << key << "\n";
		}
		delete[]update;
	};

	void CSkipList::searchElement(int key)
	{
		Node *current = header;

		/*    start from highest level of skip list
		move the current pointer forward while key
		is greater than key of node next to current
		Otherwise inserted current in update and
		move one level down and continue search
		*/
		for (int i = level; i >= 0; i--)
		{
			while (current->forward[i] &&
				current->forward[i]->key < key)
				current = current->forward[i];

		}

		/* reached level 0 and advance pointer to
		right, which is possibly our desired node*/
		current = current->forward[0];

		// If current node have key equal to 
		// search key, we have found our target node 
		if (current && current->key == key)
			cout << "Found key: " << key << "\n";
	};

	void CSkipList::deleteElement(int key)
	{
		Node *current = header;

		// create update array and initialize it 
		Node **update = new Node*[MAXLVL + 1];
		memset(update, 0, sizeof(Node*)*(MAXLVL + 1));

		/*    start from highest level of skip list
		move the current pointer forward while key
		is greater than key of node next to current
		Otherwise inserted current in update and
		move one level down and continue search
		*/
		for (int i = level; i >= 0; i--)
		{
			while (current->forward[i] != NULL &&
				current->forward[i]->key < key)
				current = current->forward[i];
			update[i] = current;
		}

		/* reached level 0 and forward pointer to
		right, which is possibly our desired node.*/
		current = current->forward[0];

		// If current node is target node 
		if (current != NULL && current->key == key)
		{
			/* start from lowest level and rearrange
			pointers just like we do in singly linked list
			to remove target node */
			for (int i = 0; i <= level; i++)
			{
				/* If at level i, next node is not target
				node, break the loop, no need to move
				further level */
				if (update[i]->forward[i] != current)
					break;

				update[i]->forward[i] = current->forward[i];
			}

			delete current;

			// Remove levels having no elements  
			while (level>0 &&
				header->forward[level] == 0)
				level--;
			cout << "Successfully deleted key " << key << "\n";
		}
		delete[]update;
	};

	// Display skip list level wise 
	void CSkipList::displayList()
	{
		cout << "\n*****Skip List*****" << "\n";
		for (int i = 0; i <= level; i++)
		{
			Node *node = header->forward[i];
			cout << "Level " << i << ": ";
			while (node != NULL)
			{
				cout << node->key << " ";
				node = node->forward[i];
			}
			cout << "\n";
		}
	};

	// Driver to test above code 
	void CSkipList::entry_point()
	{
		// Seed random number generator 
		srand((unsigned)time(0));

		// create SkipList object with MAXLVL and P 
		CSkipList lst(3, 0.5);

		lst.insertElement(3);
		lst.insertElement(6);
		lst.insertElement(7);
		lst.insertElement(9);
		lst.insertElement(12);
		lst.insertElement(19);
		lst.insertElement(17);
		lst.insertElement(26);
		lst.insertElement(21);
		lst.insertElement(25);
		lst.displayList();
		lst.searchElement(7);
		lst.deleteElement(7);
		lst.displayList();
	}
}