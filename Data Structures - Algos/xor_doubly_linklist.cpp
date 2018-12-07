class CXORList
{
	typedef struct Node
	{
		int data;
		struct Node *next;

		Node(int k, struct Node *nxt)
		{
			data = k;
			next = nxt;
		}

	} NODE, *P_NODE, **PP_NODE;

	NODE *m_head;

	P_NODE XOR(P_NODE x, P_NODE y)
	{
		return (P_NODE)((uintptr_t)x ^ (uintptr_t)y);
	}

public:
	CXORList()
	{
		m_head = NULL;
	}

	void add(int k)
	{
		P_NODE pNode = new NODE(k, XOR(NULL, m_head));
		if (m_head)
		{
			P_NODE NextOfHead = XOR(NULL, m_head->next);
			m_head->next = XOR(pNode, NextOfHead);
		}
		m_head = pNode;
	}

	void print()
	{
		P_NODE Runner = m_head;
		P_NODE Prev = NULL;
		P_NODE Next = NULL;

		while (Runner)
		{
			cout << Runner->data << "	";
			Next = XOR(Prev, Runner->next);
			Prev = Runner;
			Runner = Next;
		}
	}

	void free()
	{
		P_NODE Runner = m_head;
		P_NODE Prev = NULL;
		P_NODE Next = NULL;

		while (Runner)
		{
			cout << Runner->data << "	";
			Next = XOR(Prev, Runner->next);
			Prev = Runner;
			Runner = Next;
			P_NODE del = Prev;
			delete del;
		}
	}
};

void entry_point()
{
	CXORList list;
	list.add(4);
	list.add(3);
	list.add(2);
	list.add(1);
	list.print();
	list.free();
}
