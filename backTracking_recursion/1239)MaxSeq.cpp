/**
 * https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/solutions/4616042/bitset-for-letters-and-unordered-map-for-backtracking/
 *
 * For subset/subsequence, in the worst case we can just do a BackTrack.
 *
 * We can use DP or Greedy to avoid this but in this case, we cannot use them. (see below)
 */

void backTrack(unordered_map<string, bitset<30>> &mp, int &maxLeng, unordered_map<string, bitset<30>>::iterator iter, bitset<30> curLetters, int curLength)
{
    // cout << iter->first << " " << curLength << endl;
    maxLeng = max(maxLeng, curLength);
    if (next(iter) == mp.end())
    {
        return;
    }
    backTrack(mp, maxLeng, next(iter), next(iter)->second, next(iter)->first.size());
    for (auto it = next(iter); it != mp.end(); ++it)
    {
        if ((curLetters & it->second) == 0)
        {
            backTrack(mp, maxLeng, it, curLetters | it->second, curLength + it->first.size());
        }
    }
}
int maxLength(vector<string> &arr)
{
    unordered_map<string, bitset<30>> mp;
    for (string &s : arr)
    {
        bitset<30> temp;
        bool redundant = false;
        for (char &c : s)
        {
            if (temp[c - 'a'])
            {
                redundant = true;
                break;
            } // string itself contaisn redundant chars
            else
            {
                temp[c - 'a'] = true;
            }
        }
        if (!redundant)
            mp[s] = temp;
    }

    int maxLeng = 0;
    if (mp.size() > 0)
    {
        backTrack(mp, maxLeng, mp.begin(), mp.begin()->second, mp.begin()->first.size());
    }
    return maxLeng;
}

class Solution
{
public:
    /*
    LIS Pattern
    T(i) : Longest subsequence ending at i
    T(i) = max(T(0) ... T(i)) + arr[i].size() // if no overlap
    O(N^2)

    Difference from LIS. For LIS, For each sequence ending at i_th, it doesn't matter which sequence it choose if the length is the same. EX) 1 3 5 == 1 2 5 since they ends at 5 so doesn't affect future choice.

    "abcde" "def" "abc"
    "ab" "bc" "de" "za"
    But this case, which letter we choose affect future choice. Since
    "ab" + "de" == "bc"+"de" (both length 4), but only "bc"+"de" can make "bc"+"de"+"za".

    Can't to greedy by length since the strings that are
    small can make a longer one

    2D DP?
    T(i,j) = when we inlcude arr[i ~ j], longest seq ... No

    1 ^ 1 = 0
    1 ^ 0 = 1
    0 ^ 0 = 0

    I want 1 ^ 1 = 1, and others to be 0
    */
    struct Info
    {
        size_t length;
        vector<bitset<30>> letters;
    };
    int maxLength(vector<string> &arr)
    {
        vector<int> letters(30, 0);
        vector<Info> maxLengthEndingAt(arr.size());

        int maxLeng = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            bitset<30> t = 0;
            vector<bitset<30>> tempLetters;
            bool redundant = false;
            for (char &c : arr[i])
            {
                if (t[c - 'a'])
                { // string it self contains redundant
                    redundant = true;
                    break;
                }
                else
                    t[c - 'a'] = true;
            }
            if (redundant)
                continue;
            tempLetters.push_back(t);
            size_t tempLength = arr[i].size();

            for (int j = 0; j < i; j++)
            {
                if (maxLengthEndingAt[j].letters.size() == 0)
                    continue;
                for (int k = 0; k < maxLengthEndingAt[j].letters.size(); k++)
                {
                    if ((t & maxLengthEndingAt[j].letters[k]) == 0 &&
                        tempLength < maxLengthEndingAt[j].length + arr[i].size())
                    {
                        tempLength = maxLengthEndingAt[j].length + arr[i].size();
                        tempLetters.clear();
                        tempLetters.push_back(t | maxLengthEndingAt[j].letters[k]);
                    }
                    else if ((t & maxLengthEndingAt[j].letters[k]) == 0 && tempLength == maxLengthEndingAt[j].length + arr[i].size())
                    {
                        // same length
                        tempLetters.push_back(t | maxLengthEndingAt[j].letters[k]);
                    }
                }
            }

            maxLengthEndingAt[i].length = tempLength;
            maxLengthEndingAt[i].letters = move(tempLetters);

            maxLeng = max(maxLeng, (int)maxLengthEndingAt[i].length);
        }

        return maxLeng;
    }
};

/*
["ab","cd","cde","cdef","efg","fgh","abxyz"]
Output: "ab" "cde" "fgh" why? abxyz cannot choose previous ones since
previous one's state represent the susequence ending at that index.
Optimal: abxyz fgh cdef
T(i)'s optimal choice doesn't lead to T(i+k)'s optimal choice.
WHY? : this subsequence is NOT ordered. It can pick anything it wants.
LIS's restriction is, the number that is bigger should come after. So it cannot previous numbers.

*/