#include<iostream>
#include<algorithm>
#include<string>
#include<sstream>
#include<vector>
using namespace std;

int n;
enum {
	WHITE = 0,
	GREY = 1,
	BLACK = 2
}COLOR;

enum {
	NONE = 1,
	TE = 2,
	BE = 3,
	CE = 4,
	DE = 5
}EDGE_TYPE;

//const int N = 10000;

struct item {
	int i;
	short edge_t;
	item(int _i = -1) {
		i = _i;
		edge_t = NONE;
	}
};

vector<vector<item>> a;
short* color;
int* startTime, * back;

//int num_cutv, num_cute;
bool* cutVertex;
vector<pair<int, int>> cutEdge;


/*
because this is an undirected connected graph, only need to start dfs from random vertex
of G(the cost is O(n + m)) and find all the BE edges, then judge if v and e is the vertex
and edge we want to find
*/
int my_time = 0;
void dfs(int index, int parent) {
	color[index] = GREY;
	my_time++;
	back[index] = startTime[index] = my_time;
	for (int i = 0; i < a[index].size(); i++) {
		item* w = &a[index][i];
		if (w->i == index) continue;
		//if (a[index][i] == 1) {
		if (color[w->i] == WHITE) {
			w->edge_t = TE;
			for (int j = 0; j < a[w->i].size(); j++)
				if (a[w->i][j].i == index) {
					a[w->i][j].edge_t == TE;
					break;
				}
			//printf("TE: %d -> %d\n", index, w->i);

			dfs(w->i, index);

			if (back[w->i] >= startTime[index] && index != 0) {
				cutVertex[index] = true;
				//printf("%d is cutPoint\n", index);
			}

			back[index] = min(back[index], back[w->i]);
			if (back[w->i] > startTime[index])
				cutEdge.push_back({ min(w->i, index), max(w->i, index) });
		}
		else if (color[w->i] == GREY && w->i != parent) {
			w->edge_t = BE;
			for (int j = 0; j < a[w->i].size(); j++)
				if (a[w->i][j].i == index) {
					a[w->i][j].edge_t == BE;
					break;
				}
			//printf("BE: %d -> %d\n", index, w->i);
			back[index] = min(back[index], startTime[w->i]);
		}

		//}
	}
	color[index] = BLACK;
}

int main() {
	//cin >> n;
	cin >> n;
	//at = new Node[n];
	a = vector<vector<item>>(n);
	color = new short[n];
	cutVertex = new bool[n];
	startTime = new int[n];
	back = new int[n];
	int x, y;
	while (cin >> x && cin >> y) {
		if (x == -1 && y == -1) break;
		a[x].push_back(item(y));
		a[y].push_back(item(x));
	}

	for (int i = 0; i < n; i++) {
		cutVertex[i] = false;
		color[i] = WHITE;
		startTime[i] = back[i] = 0;
	}
	cout << "wo yi yue du guan yu chao xi de shuo ming\n";
	if (n == 0)return 0;
	dfs(0, -1);
	// if root has more than 2 dfs subtrees, root is cut vertex
	int cnt_root_subtree = 0;

	for(int i = 0; i < a[0].size(); i++){
	//for (auto w : a[0]) {
		item w = a[0][i];
		if(w.edge_t == TE) cnt_root_subtree++;
		if (cnt_root_subtree >= 2) {
			cutVertex[0] = true;
			break;
		}
	}
	//sort(cutVertex.begin(), cutVertex.end());
	sort(cutEdge.begin(), cutEdge.end());

	for (int i = 0; i < n; i++)
		if (cutVertex[i]) cout << i << endl;
	for (int i = 0; i < cutEdge.size(); i++)
		//if(cutEdge[i] != cutEdge[i + 1])
			cout << (int)cutEdge[i].first << ' ' << (int)cutEdge[i].second << endl;
	return 0;
}

/*
5
1 2
1 3
2 4
0 1
0 2
-1 -1

0
| \
1 - 2 - 4
|
3

3
0 1
1 2

0

4
0 1
1 3
2 3
0 2
0 3

0 - 1
| \ |
2 - 3

7
0 3
3 4
0 1
2 3
2 4
1 5
1 3
0 6
0 2
-1 -1

6
|
0 - 1 - 5
| \ |  
2 - 3
  \ |
    4

*/