#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

const int N = 100000;
int n;

string res[N];

struct word {
	string s;
	string key;
	//int cnt[26];
	word(string s) {
		this->s = s;
		char tmp[1000];
		//char* tmp = s.c_str();
		//s.copy(tmp, s.length(), 0);
		strcpy(tmp, s.data());
		//tmp[s.length()] = '\0';
		sort(tmp, tmp + s.length());
		key = tmp;
		//for (int i = 0; i < 26; i++)cnt[i] = 0;
		//for (int i = 0; i < s.length(); i++) cnt[s[i] - 'a']++;
	}
	word() { s = ""; }
	bool operator==(word& w) {
		//for (int i = 0; i < 26; i++)
		//	if (cnt[i] != w.cnt[i]) return false;
		//return true;
		return this->key == w.key;
	}
	bool operator>(word& w) {
		//for (int i = 0; i < 26; i++)
		//	if (cnt[i] < w.cnt[i]) return false;
		//	else if (cnt[i] > w.cnt[i]) return true;
		//if (this->s.length() > w.s.length())return true;
		//if(this->s >= w.s) return true;
		//return false;
		//return true;
		return this->key > w.key;
	}
	bool operator<(word& w) {
		//for (int i = 0; i < 26; i++)
		//	if (cnt[i] > w.cnt[i]) return true;
		//	else if (cnt[i] < w.cnt[i]) return false;
		//else if (cnt[i] < w.cnt[i]) return true;
	//if (this->s.length() < w.s.length()) return true;
	//if(this->s <= w.s) return true;
	//return false;
		//return true;
		return this->key < w.key;
	}
}words[N];

void swap_word(word& a, word& b) {
	word tmp = a;
	a = b, b = tmp;
	return;
}

int partition(word A[], int p, int r) {
	word pivot = A[r];
	int i = p - 1;
	for (int j = p; j < r; j++) {
		if (A[j] < pivot) {
			i++;
			//cout << A[j].s << '<' << pivot.s << endl;
			swap_word(A[i], A[j]);
		}
		//else cout << A[j].s << ">=" << pivot.s << endl;
	}
	swap_word(A[i + 1], A[r]);
	return i + 1;
}

void my_qsort(word A[], int p, int r) {
	if (p < r) {
		int q = partition(A, p, r);
		my_qsort(A, p, q - 1);
		my_qsort(A, q + 1, r);
	}
}



void check_words() {
	for (int i = 0; i < n; i++) cout << words[i].s << ' ';
	cout << endl;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		string tmp; cin >> tmp;
		words[i] = word(tmp);
	}
	//check_words();
	//sort(words, words + n);
	my_qsort(words, 0, n - 1);

	//check_words();

	cout << "wo yi yue du guan yu chao xi de shuo ming\n";

	int cnt = 0;

	for (int i = 0; i < n - 1; i++) {
		int j = i + 1;
		string tmp = words[i].s;
		bool flag = false;
		while (words[j] == words[i]) {
			tmp = min(words[j].s, tmp);
			j++;
			flag = true;
		}
		if (flag) res[cnt++] = tmp;
		i = j - 1;
	}

	sort(res, res + cnt);
	cout << cnt << endl;
	for (int i = 0; i < cnt; i++)cout << res[i] << endl;

	return 0;
}

/*
9
a ew vc tea oe eat zoo el le

12
a abc bca abc acb dca a ddd cab acd z z
*/