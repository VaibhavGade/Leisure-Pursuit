namespace ns_tree
{
	class CBinaryTree
	{
	public:
		typedef struct node
		{
			int key;
			node *left, *right;
		} NODE, *P_NODE;

		static P_NODE m_root;

		CBinaryTree()
		{
			m_root = NULL;
		}

		~CBinaryTree()
		{
			m_root = NULL;
		}

		P_NODE newNode(int key)
		{
			P_NODE temp = new node;
			memset(temp, 0, sizeof(node));
			temp->key = key;
			return temp;
		}

		void inorder(P_NODE root = m_root)
		{
			if (!root)
			{
				return;
			}

			inorder(root->left);
			cout << root->key << endl;
			inorder(root->right);
		}

		void insert(int key)
		{
			queue<P_NODE> q;

			if (!m_root)
			{
				m_root = newNode(key);
				return;
			}

			q.push(m_root);

			while (!q.empty())
			{
				P_NODE temp = q.front();
				q.pop();
				if (!temp->left)
				{
					temp->left = newNode(key);
					break;
				}
				else
				{
					q.push(temp->left);
				}

				if (!temp->right)
				{
					temp->right = newNode(key);
					break;
				}
				else
				{
					q.push(temp->right);
				}
			}

			return;
		}

		bool remove(int key)
		{
			P_NODE parent_deepest_node;
			P_NODE keys_node;
			P_NODE deepest_node;
			queue<P_NODE> q;
			if (!m_root) return false;
			q.push(m_root);

			keys_node = NULL;
			deepest_node = NULL;
			parent_deepest_node = NULL;
			while (!q.empty())
			{
				deepest_node = q.front();
				q.pop();

				if (deepest_node->key == key)
				{
					keys_node = deepest_node;
				}

				if (deepest_node->left)
					q.push(deepest_node->left);

				if (deepest_node->right)
					q.push(deepest_node->right);

				if (deepest_node->right || deepest_node->left)
				{
					parent_deepest_node = deepest_node;
				}
			}

			if (!keys_node)
			{
				return false;
			}

			if (deepest_node != keys_node)
			{
				keys_node->key = deepest_node->key;
			}

			if (parent_deepest_node)
			{
				(parent_deepest_node->right) ? (parent_deepest_node->right = NULL) : (parent_deepest_node->left = NULL);
			}

			delete deepest_node;
			return true;
		}

		void removeall()
		{
			P_NODE parent;
			stack<P_NODE> stk;
			queue<P_NODE> q;
			if (!m_root) return;
			q.push(m_root);

			while (!q.empty())
			{
				parent = q.front();
				q.pop();

				if (parent->left)
					q.push(parent->left);

				if (parent->right)
					q.push(parent->right);

				if (parent->left || parent->right)
				{
					stk.push(parent);
				}
			}

			while (!stk.empty())
			{
				parent = stk.top();
				stk.pop();

				if (parent->left)
				{
					delete parent->left;
					parent->left = NULL;
				}

				if (parent->right)
				{
					delete parent->right;
					parent->right = NULL;
				}
			}

			delete m_root; m_root = NULL;
		}

		/* Print nodes at a given level */
		void printGivenLevel(struct node* root, int level, int ltr)
		{
			if (root == NULL)
				return;
			if (level == 1)
				printf("%d ", root->key);
			else if (level > 1)
			{
				if (ltr)
				{
					printGivenLevel(root->left, level - 1, ltr);
					printGivenLevel(root->right, level - 1, ltr);
				}
				else
				{
					printGivenLevel(root->right, level - 1, ltr);
					printGivenLevel(root->left, level - 1, ltr);
				}
			}
		}

		void PrintSpiral()
		{
			int h = height();
			bool ltr = false;
			for (int i = 1; i <= h; i++)
			{
				printGivenLevel(m_root, i, ltr);
				ltr = !ltr;
			}
		}

		void PrintLevelWise()
		{
			queue<P_NODE> q;
			q.push(m_root);
			int level = 0;
			int i = pow(2, 3);
			while (!q.empty())
			{
				level++;
				P_NODE temp = q.front();
				q.pop();
				cout << temp->key << " ";

				if (temp->left)
					q.push(temp->left);
				if (temp->right)
					q.push(temp->right);
			}
		}

		void PrintSpiralUsingStack()
		{
			stack<P_NODE> s1;
			stack<P_NODE> s2;
			s1.push(m_root);
			while (!s1.empty() || !s2.empty())
			{
				cout << endl;

				while (!s1.empty())
				{
					P_NODE temp = s1.top();
					s1.pop();
					cout << temp->key << " ";
					if (temp->right)
						s2.push(temp->right);
					if (temp->left)
						s2.push(temp->left);
				}

				cout << endl;
				while (!s2.empty())
				{
					P_NODE temp = s2.top();
					s2.pop();
					cout << temp->key << " ";
					if (temp->left)
						s1.push(temp->left);
					if (temp->right)
						s1.push(temp->right);
				}
			}
		}

		int height(P_NODE root = m_root)
		{
			if (!root)
				return 0;

			int lh = height(root->left);
			int rh = height(root->right);
			return (max(lh, rh) + 1);
		}

		int size(P_NODE root = m_root)
		{
			static int count = 0;
			if (!root)
				return 0;

			size(root->left);
			count++;
			size(root->right);
			return count;
		}
	};

	CBinaryTree::P_NODE CBinaryTree::m_root = NULL;
}

void entry_point()
{
	ns_tree::CBinaryTree bt;
	int a[] = { 13, 12, 10, 4, 19, 16, 9 };
	for (auto i : a)
	{
		bt.insert(i);
	}
	bt.inorder();
	//bt.remove(9);
	//bt.remove(4);
	//bt.remove(13);
	//bt.remove(-1);
	//bt.PrintSpiral();
	cout << "Print tree:" << endl;
	bt.PrintLevelWise();
	cout << "Print tree spirally:" << endl;
	bt.PrintSpiralUsingStack();
	bt.removeall();
  }
