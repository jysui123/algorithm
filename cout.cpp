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

template <typename T, unsigned int N>
ostream& operator<<(ostream& os, T (&arr)[N]) {
	for (int i = 0; i < N; ++i) {
		os << arr[i];
		os << ' ';
	}
	return os << endl;
}

template <typename T, unsigned int N1, unsigned int N2>
ostream& operator<<(ostream& os, T (&arr)[N1][N2]) {
	for (int i = 0; i < N1; ++i) os << arr[i];
	return os << endl;
}

int main() {
	constexpr int r = 5 + 2, c = 3;
	int arr[r][c] = {};
	arr[2][1] = arr[5][2] = 1;
	cout << arr;
}
