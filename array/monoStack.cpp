/*
 * some applications using monotonic stack
 */

#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

class MonoStack {
public:
    // find the next largest value for an array, if no such value, assign 0
    vector<int> nextLargest(vector<int>& arr) {
        int n = arr.size();
        stack<int> mono;
        vector<int> res(n, 0);
        for (int i = 0; i < n; ++i) {
            while (!mono.empty() && arr[mono.top()] < arr[i]) {
                int j = mono.top();
                mono.pop();
                res[j] = arr[i];
            }
            mono.push(i);
        }
        return res;
    }
};