class CGraphApplications
{
public:
	CGraphApplications()
	{
	}
	struct edge
	{
		int src, dest, weight;
	};

	#define N	4
	const int INF = INT_MAX;

	bool bellman_ford(vector<edge> edges, int source)
	{
		int d[N], p[N];

		fill_n(d, N, INF);
		d[source] = 0;
		fill_n(p, N, 0);

		int k = N;
		int E = edges.size();

		while (--k)
		{
			for (int j = 0; j < E; j++)
			{
				int u = edges[j].src;
				int v = edges[j].dest;
				int w = edges[j].weight;

				if (d[v] > d[u] + w)
				{
					d[v] = d[u] + w;
					p[v] = u;
				}
			}
		}

		for (int j = 0; j < E; j++)
		{
			int u = edges[j].src;
			int v = edges[j].dest;
			int w = edges[j].weight;

			if (d[v] > d[u] + w)
			{
				return true;
			}
		}

		return false;
	}

	void test_bellman_ford()
	{
		int i;
		int adjmatrix[N][N] = {
			{0, INF, -2, INF},
			{4, 0, -3, INF},
			{INF, INF, 0, 2},
			{INF, -1, INF, 0}
		};

		vector<edge> edges;
		for (int u = 0; u < N; u++)
			for (int v = 0; v < N; v++)
				if (adjmatrix[u][v] && adjmatrix[u][v] != INF)
					edges.push_back({ u, v, adjmatrix[u][v] });

		for (i = 0; i < N; i++)
		{
			if (bellman_ford(edges, i))
			{
				cout << "Negative cycle found" << endl;
				break;
			}
		}

		if (i == N)
			cout << "No -ve cycle found" << endl;
	}

	bool floyd_marshall(int graph[N][N])
	{
		int distance[N][N], path[N][N];

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				distance[i][j] = graph[i][j];
				if (distance[i][j] != INF && i != j)
					path[i][j] = i;
				else
					path[i][j] = -1;
			}

		for (int k = 0; k < N; k++)
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
				{
					if (distance[i][k] == INF || distance[k][j] == INF)
						continue;

					if (distance[i][j] > distance[i][k] + distance[k][j])
					{
						distance[i][j] = distance[i][k] + distance[k][j];
						path[i][j] = path[k][j];
					}
				}

		for (int i = 0; i < N; i++)
			if (distance[i][i] < 0)
				return true;

		print_path(path, 3, 2);
		return false;
	}

	void print_path(int path[N][N], int src, int dest)
	{
		cout << "Path from " << src << " -> " << dest << ":";
		stack<int> stk;
		stk.push(dest);
		while (1)
		{
			dest = path[src][dest];
			stk.push(dest);
			if (src == dest)
				break;
		}
		while (!stk.empty())
		{
			int val = stk.top();
			stk.pop();
			cout << val << "	";
		}
	}

	void test_floyd_marshall()
	{
		int adjmatrix[N][N] = {
#if 0
			{ 0, INF, -2, INF },
			{ 4, 0, -3, INF },
			{ INF, INF, 0, 2 },
			{ INF, -1, INF, 0 }
#else
			{ 0, 3, 6, 15 },
			{ INF, 0, -2, INF },
			{ INF, INF, 0, 2 },
			{ 1, INF, INF, 0 }
#endif
		};

		if (floyd_marshall(adjmatrix))
			cout << "Negative cycle found" << endl;
		else
			cout << "No -ve cycle found" << endl;
	}
}

void entry_point()
{
	CGraphApplications graphs;
	graphs.test_floyd_marshall();
}
