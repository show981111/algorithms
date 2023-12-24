/*
Observation:
At each index, we should see if we can create a substring that is a permutation of words
Better to use previous map of count (Which words are included) at next step (No need to start from the left again to count words we alr counted)

** Sliding window, step = length of each word

Brute Force: O(N^2) = why? at each index, just check if it is a perm, CheckPerm(string w, words) => O(|w|) if w is a permutation of words.
Might be DP?: But still it is O(N^2) too. Since it is using a 2D array of substrings

Since step of sliding window is length of each word, we should check left + 1 ~ can make a permutation too.
Thus, starting point can be
left~, left+1~, left+2~, ..., left + word.size - 1 ~

**
CheckPerm(string w, words) optimization
In sliding window, if we just check the map's item then it will take O(words.length()) to check if they are permutation

We can put additional constraints to the window's count,
such as we maintain words at max we need.
So if we see a redundant word that we have more than we need, shrink until we match the amount!
-> this works because if we have more elem, then we cannot make any perm until we make the matching amount.

*/

class Solution
{
public:
    vector<int> findSubstring(string s, vector<string> &words)
    {
        int cur = 0;
        unordered_map<string, int> cnt;
        for (auto &word : words)
        {
            cnt[word]++;
        }
        int wordSize = words[0].size();
        int N = s.size();
        vector<int> ans;

        // TC: O(wordSize*s.size()*words.size()) -> Worst case
        for (int cur = 0; cur < wordSize; ++cur) // O(wordSize)
        {
            int left = cur;
            int right = left;
            unordered_map<string, int> window;
            while (right + wordSize <= N) // O(s.size())
            {
                string w = s.substr(right, wordSize);
                right += wordSize;

                if (cnt.count(w) > 0)
                {
                    window[w]++;
                    // check if its a permutation of words array. O(words.size())
                    if (right - left == wordSize * words.size())
                    {
                        bool same = true;
                        for (auto &item : cnt) // O(words.size())
                        {
                            if (window.count(item.first) > 0 && window[item.first] == item.second)
                                continue;
                            else
                            {
                                same = false;
                                break;
                            }
                        }
                        if (same)
                            ans.push_back(left);
                    }
                }
                else
                {
                    window.clear();
                    left = right;
                }

                // shrink
                string first = s.substr(left, wordSize);
                if (right - left >= wordSize * words.size())
                {
                    if (cnt.count(first) > 0)
                    {
                        window[first]--;
                        if (window[first] == 0)
                            window.erase(first);
                    }
                    left += wordSize;
                }
            }
        }

        return ans;
    }
};

/**
 * Better way to check the permutation
 */

class Solution
{
public:
    vector<int> findSubstring(string s, vector<string> &words)
    {
        int cur = 0;
        unordered_map<string, int> cnt;
        for (auto &word : words)
        {
            cnt[word]++;
        }
        int wordSize = words[0].size();
        int N = s.size();
        vector<int> ans;

        // O(WordSize*N)
        for (int cur = 0; cur < wordSize; ++cur)
        {
            int left = cur;
            int right = left;
            unordered_map<string, int> window;
            int curWordCnt = 0; // how many words that are in words array are in current wo=indow

            while (right + wordSize <= N)
            {
                string w = s.substr(right, wordSize);
                right += wordSize;

                if (cnt.count(w) > 0)
                {
                    window[w]++;
                    curWordCnt++;
                    if (window[w] == cnt[w])
                    {
                        if (right - left == wordSize * words.size() && curWordCnt == words.size())
                        { // if the length are the appropriate and we have all words
                            /**
                             * If the window length is right - left and curWordCnt == words.size(), it is 100% permutation.
                             * Because if we have more elements than we need, than curWordCnt will be bigger.
                             * !! Since we maintain the window so that we have each word in the window only as much as we need or less !!
                             */
                            ans.push_back(left);
                        }
                    }
                }
                else
                {
                    window.clear();
                    curWordCnt = 0;
                    left = right;
                }
                // shrink
                string first = s.substr(left, wordSize);
                while (right - left >= wordSize * words.size() || window[w] > cnt[w])
                { // shrink the window if the window is too large, or we have too many words than we need
                    if (cnt.count(first) > 0)
                    {
                        window[first]--;
                        curWordCnt--;
                        if (window[first] == 0)
                            window.erase(first);
                    }
                    left += wordSize;
                    first = s.substr(left, wordSize);
                }
            }
        }

        return ans;
    }
};