#include<iostream>
#include<vector>

using namespace std;

//vector<char> a;
string a;
int max_len;
int n;
vector<vector<short>>dp;

void check_a() {
	cout << a << endl;
	return;
}

void check_dp() {
	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < n + 1; j++) {
			cout << dp[i][j] << ' ';
		}
		cout << endl;
	}
}

void DP() {
	for (int i = n - 1; i >= 0; i--) {
		dp[i][i] = 1;
		for (int j = i + 1; j < n; j++) {
			if (a[i] == a[j])
				dp[i][j] = dp[i + 1][j - 1] + 2;
			else
				dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
		}
	}
	/*
	for (int i = 0; i < n; i++) {
		for (int j = n - 1; j >= 0; j--) {
			int k = n - j - 1;
			if (a[i] == a[j])
				dp[i + 1][k + 1] = dp[i][k] + 1;
			else
				dp[i + 1][k + 1] = max(dp[i][k + 1], dp[i + 1][k]);
			//max_len = max((int)dp[i + 1][k + 1], max_len);
		}
	}
	*/
	return;
}

int main() {
	char c;
	while (scanf("%c", &c) != EOF) {
		if (c == '-')break;
		if (c != ' ')
			a = a + c;
	}
	n = a.size();
	printf("I have read the rules about plagiarism punishment\n");
	//check_a();
	dp = vector<vector<short>>(n + 1, vector<short>(n + 1, 0));
	DP();
	printf("%d\n",dp[0][n - 1]);

	//check_dp();
	
	return 0;
}

/*
A C G T G T C A A A A T C G -
*/