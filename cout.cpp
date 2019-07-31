#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
	for (const auto& t : v) os << t << " ";
	return os << endl;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& vv) {
	for (const auto& v : vv) os << v;
	return os << endl;
}

template <typename T>
ostream& operator<<(ostream& os, const unordered_set<T>& v) {
	for (const auto& t : v) os << t << " ";
	return os << endl;
}

template <typename K, typename V>
ostream& operator<<(ostream& os, const unordered_map<K, V>& m) {
	for (const auto& p : m)
		os << p.first << ": " << p.second << endl;
	return os << endl;
}

template <typename T, int N1, int N2>
void print(T (&arr)[N1][N2]) {
	for (int i = 0; i < N1; ++i) {
		for (int j = 0; j < N2; ++j)
			cout << arr[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

int main() {
	int arr[10][4] = {};
	arr[2][1] = arr[5][2] = 1;
	print(arr);
}
