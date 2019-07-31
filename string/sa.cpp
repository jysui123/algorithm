#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class SuffixArray {
    class Suffix {
    public:
        int id, rank1, rank2;
        Suffix(int id_, int rank1_, int rank2_): id(id_), rank1(rank1_), rank2(rank2_) {}
        bool operator<(const Suffix& rhs) const {
            return rank1 == rhs.rank1 ? rank2 < rhs.rank2 : rank1 < rhs.rank1;
        }
    };

    int n;
    string s;
    vector<Suffix> suffices;

public:
    SuffixArray(const string& s_): n(s_.size()), s(s_) {
        for (int i = 0; i < n; ++i)
            suffices.emplace_back(i, s[i] - 'a', i + 1 < n ? s[i + 1] - 'a' : -1);
        sort(suffices.begin(), suffices.end());

        vector<int> invIndex(n, 0);
        for (int k = 4; k < n * 2; k *= 2) {
            int newRank1 = 0, prevOldRank1 = suffices[0].rank1, unique = 1;
            suffices[0].rank1 = 0, invIndex[suffices[0].id] = 0;
            for (int i = 1; i < n; ++i) {
                if (suffices[i].rank1 == prevOldRank1 && suffices[i].rank2 == suffices[i-1].rank2)
                    suffices[i].rank1 = newRank1, unique = 0;
                else
                    prevOldRank1 = suffices[i].rank1, suffices[i].rank1 = ++newRank1;
                invIndex[suffices[i].id] = i;
            }
            if (unique) break;

            for (int i = 0; i < n; ++i) {
                int nextIndex = suffices[i].id + k/2;
                suffices[i].rank2 = nextIndex < n ? suffices[invIndex[nextIndex]].rank1 : -1;
            }
            sort(suffices.begin(), suffices.end());
        }
    }

    vector<int> suffixArray() {
        vector<int> res(n, 0);
        for (int i = 0; i < n; ++i) res[i] = suffices[i].id;
        return res;
    }

    vector<int> lcp() {
        vector<int> res(n, 0), invIndex(n, 0);
        for (int i = 0; i < n; ++i) invIndex[suffices[i].id] = i;

        for (int i = 0, len = 0; i < n; ++i) {
            if (invIndex[i] == n-1) {
                len = 0;
                continue;
            }
            int j = suffices[invIndex[i]+1].id;
            while (i + len < n && j + len < n && s[i + len] == s[j + len]) len++;

            res[i] = len;
            len = max(len-1, 0);
        }
        return res;
    }
};