/*
This source file contains code for patterns "Iterator" and "Visitor" for tree composite.
*/


class CBST
{
public:

	struct bst_node
	{
		int data;
		bst_node *left, *right;

		bst_node(int key): data(key)
		{
			left = right = NULL;
		}
	};

	bst_node* insert_non_recur(bst_node **root, int key)
	{
		if (*root == NULL)
		{
			*root = new bst_node(key);
			return *root;
		}

		bst_node **runner = root;
		while (*runner)
		{
			runner = (key <= (*runner)->data) ? &(*runner)->left : &(*runner)->right;
		}

		*runner = new bst_node(key);
		return *runner;
	}

	bst_node* insert(bst_node **root, int key)
	{
		if (*root == NULL)
		{
			*root = new bst_node(key);
			return *root;
		}
		else
		{
			bst_node *crawl = *root;

			if (key <= crawl->data)
			{
				crawl->left = insert(&crawl->left, key);
				return crawl;
			}
			else
			{
				crawl->right = insert(&crawl->right, key);
				return crawl;
			}
		}
	}

	void cleanup(bst_node **root)
	{
		if (NULL != *root)
		{
			cleanup(&((*root)->left));
			cleanup(&((*root)->right));
			free(*root);
			*root = NULL;
		}
	}

	class CBST_Iterator
	{
		public:
		CBST_Iterator(bst_node *root) {
			pushAll(root);
		}

		// return whether we have a next smallest number 
		bool hasNext()
		{
			return !myStack.empty();
		}

		// return the next smallest number
		int next()
		{
			bst_node *tmpNode = myStack.top();
			myStack.pop();
			pushAll(tmpNode->right);
			return tmpNode->data;
		}

	private:
		stack<bst_node *> myStack;

		void pushAll(bst_node *root)
		{
			while (root != NULL) {
				myStack.push(root);
				root = root->left;
			}
		}
	};

	class CNodeVisitor
	{
	public:
		virtual void beforeVisitingLeftChild(bst_node *node) {}
		virtual void afterVistingLeftChild(bst_node *node) {}
		virtual void beforeVistingRightChild(bst_node *node) {}
		virtual void afterVistingRightChild(bst_node *node) {}
		virtual void visit(bst_node *node) {}
	};

	class CDisplayVisitor : public CNodeVisitor
	{
	public:
		virtual void visit(bst_node *node)
		{
			cout << node->data << "	";
		}
	};

	class CCountingVisitor : public CNodeVisitor
	{
		int m_iCount;
	public:
		CCountingVisitor() :m_iCount(0) {}
		virtual void visit(bst_node *node)
		{
			m_iCount++;
		}

		int getCount() { return m_iCount;  }
	};

	class CMirrorVisitor : public CNodeVisitor
	{
	public:
		virtual void visit(bst_node *node)
		{
			swap(node->left, node->right);
		}
	};

	class CBTTraversal
	{
		CNodeVisitor *m_pVisitor;

	public:
		CBTTraversal()
		{
			m_pVisitor = new CDisplayVisitor();
		}

		~CBTTraversal()
		{
			if (m_pVisitor)
			{
				delete m_pVisitor;
			}
		}

		virtual void traverse(bst_node *node, CNodeVisitor *pVisitor) = 0;
		void traverse(bst_node *node)
		{
			traverse(node, m_pVisitor);
		}
	};

	class CBTTPreorderTraversal : public CBTTraversal
	{
	public:
		virtual void traverse(bst_node *node, CNodeVisitor *pVisitor)
		{
			if (NULL == node)
				return;


			pVisitor->visit(node);

			pVisitor->beforeVisitingLeftChild(node);
			traverse(node->left, pVisitor);
			pVisitor->afterVistingLeftChild(node);

			pVisitor->beforeVistingRightChild(node);
			traverse(node->right, pVisitor);
			pVisitor->afterVistingRightChild(node);
		}
	};

	class CBTTInorderTraversal : public CBTTraversal
	{
	public:
		virtual void traverse(bst_node *node, CNodeVisitor *pVisitor)
		{
			if (NULL == node)
				return;

			pVisitor->beforeVisitingLeftChild(node);
			traverse(node->left, pVisitor);
			pVisitor->afterVistingRightChild(node);

			pVisitor->visit(node);

			pVisitor->beforeVistingRightChild(node);
			traverse(node->right, pVisitor);
			pVisitor->afterVistingRightChild(node);
		}
	};

	class CBTTPostorderTraversal : public CBTTraversal
	{
	public:
		virtual void traverse(bst_node *node, CNodeVisitor *pVisitor)
		{
			if (NULL == node)
				return;

			pVisitor->beforeVisitingLeftChild(node);
			traverse(node->left, pVisitor);
			pVisitor->afterVistingRightChild(node);

			pVisitor->beforeVistingRightChild(node);
			traverse(node->right, pVisitor);
			pVisitor->afterVistingRightChild(node);

			pVisitor->visit(node);
		}
	};
}

void entry_point()
{
	CBST bst;
	CBST::bst_node *root = NULL;

	int arr[] = { 4,3,5,7,1,2,6 };
	for (int i = 0; i < _countof(arr); i++)
	{
		bst.insert_non_recur(&root, arr[i]);
	}

#if 0
	CBST::CBST_Iterator bst_it(root);
	while (bst_it.hasNext())
		cout << bst_it.next() << endl;
#endif

	CBST::CBTTPreorderTraversal preOrderTT;
	CBST::CBTTInorderTraversal inOrderTT;
	CBST::CBTTPostorderTraversal postOrderTT;

#if 0
	CBST::CDisplayVisitor displayVisitor;
	preOrderTT.traverse(root, &displayVisitor);
	cout << endl;
	inOrderTT.traverse(root, &displayVisitor);
	cout << endl;
	postOrderTT.traverse(root, &displayVisitor);
#endif

#if  0
	CBST::CCountingVisitor countingVisitor;
	preOrderTT.traverse(root, &countingVisitor);
	cout << countingVisitor.getCount();

	inOrderTT.traverse(root, &countingVisitor);
	cout << countingVisitor.getCount();

	postOrderTT.traverse(root, &countingVisitor);
	cout << countingVisitor.getCount();
#endif //  0

#if 1
	CBST::CMirrorVisitor mirrorVisitor;
	preOrderTT.traverse(root, &mirrorVisitor);
	preOrderTT.CBTTraversal::traverse(root);

#endif

	bst.cleanup(&root);
 }
