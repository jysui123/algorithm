# Description
Suffix array is the lexically sorted suffices of a given string.   
eg. s = "banana", sa = ["a","ana","anana","banana","na","nana"]   
To simplify, suffix array can be represented by the starting index of each suffix.    
eg. s = "banana", sa = [5,3,1,0,4,2]   

# Build Suffix Array
## O(n(logn)^2) algorithm
- We sort the suffices in k (k = 1,2,3,...) rounds. In each round, only consider the first 2^k characters of each suffices.  
- At round k, we split the first 2^k charaters into 2 parts, 1st part is [0, 2^(k-1)), 2nd part is [2^(k-1), 2^k). We denote them as key1_k and key2_k.  
- At round k, we assume we have done the round k-1, which means the first 2^(k-1) characters are sorted for all suffices. In other words, we have sorted the suffices by key1_k.
- To prepare round k sorting, we need to assgin ranks for key1_k and key2_k of suffix starting from s[i]. 
  - key1_k's rank is trivial since we already sort by it. We just maintain a rank r starting from 0 and iterate the partially sorted suffices. If we encounter an different key1_k, we increment the rank and assign the increamented rank to it.
  - key2_k is just another key1_k of the suffix starting from s[i+2^(k-1)]. Notice that we already sort them in the previous round. So just assign its rank as the order of s[i+2^(k-1)] in previous round.
- If key2_k is beyond string s, assign -1 as its rank.
- To initialize, the rank is just s[i]-'a'.     
Code:
~~~
class Suffix {
public:
    int id, rank1, rank2;
    Suffix(int id, int rank1, int rank2): id(id), rank1(rank1), rank2(rank2) {}
};

vector<int> suffixArray(const string& s) {
    int n = s.size();
    auto cmp = [](const Suffix& s1, const Suffix& s2) {
        return s1.rank1 == s2.rank1 ? s1.rank2 < s2.rank2 : s1.rank1 < s2.rank1;
    };
    vector<Suffix> suffices;
    
    // initialize: for any i, suffix = s[i:], rank1 = suffix[0]-'a', rank2 = suffix[1]-'a'
    for (int i = 0; i < n; ++i) 
        suffices.emplace_back(i, s[i]-'a', i+1<n?s[i+1]-'a':-1);
    sort(suffices.begin(), suffices.end(), cmp);
    
    // invInd[i] = j : suffix starting at s[i] is now at the jth position of suffices
    vector<int> invInd(n, 0); 
    for (int k = 4; k < n*2; k *= 2) {
        int newRank1 = 0, prevOldRank1 = suffices[0].rank1, unique = 1;
        suffices[0].rank1 = 0, invInd[suffices[0].id] = 0;
        
        // assign rank1 for next round
        for (int i = 1; i < n; ++i) {
            if (suffices[i].rank1 == prevOldRank1 && suffices[i].rank2 == suffices[i-1].rank2) 
                suffices[i].rank1 = newRank1, unique = 0;
            else 
                prevOldRank1 = suffices[i].rank1, suffices[i].rank1 = ++newRank1;
            invInd[suffices[i].id] = i;
        }
        if (unique) break;
        
        // assign rank2 for next round, just use the just assigned rank1
        for (int i = 0; i < n; ++i) {
            int nextInd = suffices[i].id + k/2;
            suffices[i].rank2 = nextInd < n ? suffices[invInd[nextInd]].rank1 : -1;
        }
        sort(suffices.begin(), suffices.end(), cmp);
    }
    vector<int> sa(n, 0);
    for (int i = 0; i < n; ++i) sa[i] = suffices[i].id;
    return sa;
}
~~~

## O(nlogn) algorithm
We can observe that all the ranks are in range [-1, n). By using radix sort, we can avoid a logn factor in time complexity.

## O(n) algorithm
See DC3.

## Build Longest Common Prefix (LCP) of Suffix Array in O(n)
Def. lcp[i] is the length of lcp between suffix starting at position s[i] and the suffix with next rank. If this is the last suffix in sa, lcp[i] = 0.    
Lemma. lcp[i+1] >= lcp[i]-1   
Intuition: we denote suffix starting at s[i] as suffix[i]. We have suffix[i].substr(1:) == suffix[i+1]. In sa, suppose the corresponding next suffix of suffix[i] and suffix[i+1] are suffix[j] and suffix[j'] respectively. We have cp(suffix[i], suffix[i+1]) == suffix[i][0] + cp(suffix[j], suffix[j']). As a result, lcp[i+1] >= lcp[i]-1.     
Code:
~~~
vector<int> lcpArray(string& s, vector<int>& sa) {
    int n = s.size();
    // invInd[i] = r: suffix start at s[i] has rank r (is at sa[r])
    vector<int> lcp(n, 0), invInd(n, 0);
    for (int i = 0; i < n; ++i) invInd[sa[i]] = i;
    // here i is the suffix starting position
    for (int i = 0, len = 0; i < n; ++i) {
        if (invInd[i] == n-1) {
            len = 0;
            continue;
        }
        int j = sa[invInd[i]+1]; // j is the start position in s of the next rank suffix
        while (i+len < n && j+len < n && s[i+len] == s[j+len]) len++;
        lcp[invInd[i]] = len;
        // we keep len due to h(i+1) >= h(i)-1
        len = max(len-1, 0);
    }
    return lcp;
}
~~~
