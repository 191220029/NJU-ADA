#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;



int main() {
	priority_queue<int> down;
	priority_queue<int, vector<int>, greater<int>> up;

	int x = 0;
	while (scanf("%d", &x) != EOF) {
		if (down.empty() || x <= down.top())
			down.push(x);
		else up.push(x);

		if (down.size() > up.size() + 1)
			up.push(down.top()), down.pop();
		if (up.size() > down.size()) down.push(up.top()), up.pop();

		cout << down.top() << " ";
	}
	return 0;
}

/*
-18 -2 14 -20 -6 7 2 14 11 6
*/