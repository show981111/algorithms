/**
 * @brief DP
 * Think the relationship between T(n) vs T(n-k)[previous step]!!
 * This case, previous step(n-k) is all possible words(where memo is true)
 * == string that is breakable with words
 * If previous string is breakable and current word is in the wordDict => that string is breakable
 *
 * Bottom-up DP
 * Time : O(s.length() * wordDict.size())
 *
 * How about Brute Force?
 *
 * https://leetcode.com/problems/word-break/discuss/169383/solved-The-Time-Complexity-of-The-Brute-Force-Method-Should-Be-O(2n)-and-Prove-It-Below
 * Time : O(2^s.length())
 * s = "abcdef",
 * T(N) = T(N-1) + T(N-2) + ... + T(0) => 2^N b/c T(N-1) = T(N-2) + ... + T(0), T(N) - T(N-1) = T(N-1), T(N) = 2*T(N-1)
 * N length is breakable = (1, N-1) pair or (2, N-2) pair or ...
 * [pair means words in WordDict and leftover.
 * EX) "abcdef" => ("a", "bcdef"), ("ab","cdef")]
 *
 * PS)
 * the word abcd can be partitioned into abc and d only .
 * But if it was to be partitioned in any combination like abc/bac/cab then it would result in N^N.
 */

class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        vector<bool> memo(s.length()); // [n, k) is breakable => memo[k] = true
                                       // make the k exclusive in order to stop at there
        for (int i = 0; i < memo.size(); i++)
        {
            if (i == 0 || memo[i] == true)
            { // if memo is true, then stop and compare all words
                // to find next string that is breakable
                // since it stops when memo[i] == true, memo[k] = true when s[0 : k-1] is breakable!
                for (auto &word : wordDict)
                {
                    if (word == s.substr(i, word.length()))
                    {
                        if (i + word.length() == s.length())
                            return true;
                        memo[i + word.length()] = true;
                    }
                }
            }
        }

        return false;
    }
};