namespace linked_list
{
	typedef struct Node
	{
		int key;
		struct Node *next;
		Node(int k)
		{
			key = k;
			next = NULL;
		}
	} NODE, *P_NODE, **PP_NODE;

	class CSinglyLinkedList
	{
	public:
		P_NODE head;
		P_NODE tail;

		CSinglyLinkedList():head(NULL), tail(NULL)
		{}

		void add(int data)
		{
			if (!head)
			{
				head = new NODE(data);
				tail = head;
			}
			else
			{
				tail->next = new NODE(data);
				tail = tail->next;
			}
		}

		void release()
		{
			P_NODE temp, runner = head;
			while (runner)
			{
				temp = runner;
				runner = runner->next;
				delete temp;
			}
		}

		bool FindLoop_UsingSet()
		{
			P_NODE runner = head;
			set<P_NODE> AddrSet;
			while (runner)
			{
				if (AddrSet.end() == AddrSet.find(runner))
					AddrSet.insert(runner);
				else
				{
					cout << "Loop found at: " << runner->key;
					return true;
				}
				runner = runner->next;
			}
			return false;
		}

		bool FindLoop_UsingFloydDetection()
		{
			P_NODE slow, fast;
			slow = fast = head;

			while (slow && fast && fast->next)
			{
				slow = slow->next;
				fast = fast->next->next;

				if (slow == fast)
				{
					cout << "Loop found at: " << slow->key;
					return true;
				}
			}

			return false;
		}

		static void Loop_Caller()
		{
			CSinglyLinkedList SLL;
			int arr[] = { 11, 12, 13, 14 };
			for (auto i : arr)
			{
				SLL.add(i);
			}

			//	Create loop
			SLL.head->next->next->next = SLL.head->next;
			//SLL.FindLoop_UsingSet();
			SLL.FindLoop_UsingFloydDetection();
		}
	};
}
