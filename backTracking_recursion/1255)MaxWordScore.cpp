class Solution
{
    /**
     * Backtracking: When to stop? How to go through all possibilities?
     * Building a DECISION TREE helps! This case, at each index, include current element OR Not (Two choices)
     *
     * How did I know it is a backtracking?
     * Most max/minimization or counting, which requires brute force can be solved using backtracking.
     * Backtracking is the brute force. First think about DP or Greedy. If those don't work, use backtracking.
     */
public:
    void solve(vector<string> &words, unordered_map<char, int> &freq, vector<int> &score, int &maxScore, int curScore, int curIndex)
    {
        if (curIndex == words.size())
        {
            maxScore = max(maxScore, curScore);
            return;
        }
        solve(words, freq, score, maxScore, curScore, curIndex + 1); // without
        bool possible = true;
        int wordScore = 0;
        for (char &c : words[curIndex])
        {
            freq[c]--;
            wordScore += score[c - 'a'];
            if (freq[c] < 0)
                possible = false;
        }
        if (possible)
            solve(words, freq, score, maxScore, curScore + wordScore, curIndex + 1);
        for (char &c : words[curIndex])
        {
            freq[c]++;
        }
    }
    int maxScoreWords(vector<string> &words, vector<char> &letters, vector<int> &score)
    {
        unordered_map<char, int> freq;
        for (char &c : letters)
        {
            freq[c]++;
        }
        int maxScore = 0;
        solve(words, freq, score, maxScore, 0, 0);
        return maxScore;
    }
};
