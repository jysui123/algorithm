#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template <typename T, typename Res>
class GenericMerge {
    void process(Itr l, Itr r, Res& res) {
        int dist = r - l;
        if (dist <= 0) return;
        Itr m = l + dist / 2;
        process(l, m), process(m, r);
        for (Itr i = l, j = m; i != m; ++i) {
            while (j != r && !criterion(i, j)) ++j;
            updateResult(i, j, m);
        }
        inplace_merge(l, m, r);
    }

public:
    using Vec = vector<pair<T, int>>;
    using Itr = Vec::iterator;
    function<bool(Itr, Itr)> criterion;
    function<void(Itr, Itr, Itr, Res)> updateResult;
    void doMerge(vector<T> &vec, Res &res) {
        Vec zipped;
        for (int i = 0; i < vec.size(); ++i)
            zipped.push_back({vec[i], i});
        process(zipped.begin(), zipped.end(), res);
        return res;
    }
};