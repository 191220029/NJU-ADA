#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>

using namespace std;

struct edge {
	int u, v;
	edge(int _u, int _v) {
		u = _u; 
		v = _v;
	}
};

struct group;


enum {
	WHITE = 0,
	GREY = 1,
	BLACK = 2
}COLOR;

vector<vector<int>> a;
vector<vector<int>> a_t;
int* color;

vector<group> sc_parts;
int G_ID;
int* part;

struct group {
	vector<int> out;
	vector<int> member;
	int PRI;
	int priority() {
		int sum = member.size() - 1;
		bool *reachable = new bool[G_ID];
		stack<int> q;
		fill(reachable, reachable + G_ID, false);
		for (int i = 0; i < out.size(); i++) {
			q.push(out[i]);
		}
		while (!q.empty()) {
			if (!reachable[q.top()]) {
				reachable[q.top()] = true;
				int tmp = q.top();
				for (int i = 0; i < sc_parts[tmp].out.size(); i++) 
					q.push(sc_parts[tmp].out[i]);
			}
			else q.pop();
		}

		for(int i = 0; i < G_ID; i++)
			if(reachable[i])
				sum += sc_parts[i].member.size();
		delete[] reachable;
		return sum;
	}
	bool operator<(const group& g)const {
		return this->PRI < g.PRI;
	}
};

stack<int>nodeStack;
int max_affect;
vector<int> MANodes;





int n;

void DFS(int index, int parent, void (*post_process)(int), const vector<vector<int>> &G) {
	color[index] = GREY;
	for (int i = 0; i < G[index].size(); i++) {
		int w = G[index][i];
		if (w == index) continue;
		if (color[w] == WHITE) {
			DFS(w, index, post_process, G);
		}
		else if (color[w] == GREY && w != parent) {
			//w->edge_t = BE;
		}

		//}
	}
	(*post_process)(index);
	color[index] = BLACK;
}

void null(int) {
	return;
}

void FIRST_DFS_SCC(int v) {
	nodeStack.push(v);
	//cout << v << " pushed into stack\n";
	return;
}

void SECOND_DFS_SCC(int v) {
	sc_parts[G_ID].member.push_back(v);
	part[v] = G_ID;
	return;
}

void TRAVERSE_G() {
	a_t.resize(n);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[i].size(); j++) {
			a_t[a[i][j]].push_back(i);
		}
	}
	//swap(a, a_t);
	/*for (int i = 0; i < a_t.size(); i++) {
		for (int j = 0; j < a_t[i].size(); j++)
			cout << a_t[i][j] << ' ';
		cout << endl;
	}*/
	return;
}

void SCC() {
	void (*pf1)(int) = FIRST_DFS_SCC;
	void (*pf2)(int) = SECOND_DFS_SCC;
	for(int i = 0; i < n; i++)
		if(color[i] == WHITE)
			DFS(i, -1, pf1, a);
	TRAVERSE_G();
	fill(color, color + n, 0);
	while (!nodeStack.empty()) {
		if (color[nodeStack.top()] != WHITE) {
			nodeStack.pop();
			continue;
		}
		sc_parts.push_back(group());
		DFS(nodeStack.top(), -1, pf2, a_t);
		nodeStack.pop();
		G_ID++;
	}

	/*for (int i = 0; i < sc_parts.size(); i++) {
		cout << "PART" << i << ": ";
		for (int j = 0; j < sc_parts[i].member.size(); j++) {
			cout << sc_parts[i].member[j] << ' ';
		}
		cout << endl;
	}*/
	return;
}

void priority() {
	for (int id = 0; id < G_ID; id++) {
		int cur_priority = 0;
		for (int i = 0; i < sc_parts[id].member.size(); i++) {
			int u = sc_parts[id].member[i];
			for (int j = 0; j < a[u].size(); j++) {
				if (part[a[u][j]] != id) {
					bool flag = false;
					for (int k = 0; k < sc_parts[id].out.size(); k++)
						if (sc_parts[id].out[k] == part[a[u][j]]) {
							flag = true;
							break;
						}
					if (!flag)
						sc_parts[id].out.push_back(part[a[u][j]]);
				}
			}
		}
		//sc_parts[id].PRI = sc_parts[id].priority();
		//cout << "PART" << id << ".PRI = " << sc_parts[id].PRI << endl;
	}
	for(int id = 0; id < G_ID; id++)
		sc_parts[id].PRI = sc_parts[id].priority();
	//cout << "PART" << id << ".PRI = " << sc_parts[id].PRI << endl;
}

int main() {
	string str;
	//while (scanf("%s\n", &str[0]) != EOF){
	while (!cin.eof()) {
		getline(cin, str);
	//while (getline(cin, str)) {
		if (str == "-1") break;
		if (str.size() == 0) {
			n++;
			a.push_back(vector<int>(0));
			continue;
		}
		n++;
		a.push_back(vector<int>(0));
		istringstream ist(str);
		int i;
		while (ist >> i) {
			a[n - 1].push_back(i);
		}
	}

	

	color = new int[n];
	fill(color, color + n, 0);
	part = new int[n];
	SCC();
	priority();
	

	printf("I have read the rules about plagiarism punishment\n");
	sort(sc_parts.begin(), sc_parts.end());
	for (int i = sc_parts.size() - 1; i >= 0; i--) {
		if (sc_parts[i].PRI >= max_affect) {
			max_affect = sc_parts[i].PRI;
			for (int j = 0; j < sc_parts[i].member.size(); j++) {
				MANodes.push_back(sc_parts[i].member[j]);
			}
		}
		else break;
	}
	sort(MANodes.begin(), MANodes.end());
	cout << max_affect << endl;
	for (int i = 0; i < MANodes.size(); i++)
		cout << MANodes[i] << ' ' ;
	return 0;
}

/*
1
2 3
0
4
5
3

0 -> 1
¡ü¨L¡ý
2	 3 -> 4
      ¨I ¡ý
	     5

4
2 0 4
3
4

-1

0 <- 1 -> 2 -> 3
|    ¡ý        +
+ -> 4 <-------+
1 2
2

-1

0 -> 1
¡ý¨L
2

1 2
2
1 2

0 -> 1
¡ý/
2

1
2
0

1 2

1
-1

*/