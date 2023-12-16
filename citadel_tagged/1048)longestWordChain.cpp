/**
 *
 * Longest Length + Ordering constrain?
 *  => LIS PATTERN!
 *
 * "Longest".. need to get an optimal solution
 * a) Greedy?
 *    Since we can only insert one character.. let's sort based on length!
 *          (Only the value with smaller length can be a pred! If they are same length, they cannot be a predecessor relationship!)
 *    Now it is sorted. Problem is, getting the longest length. At i_th index, which one is longer? taking i+a or i+b's word?
 *    In a sorted order, getting the longest chain => Smells like LIS
 * b) DP (LIS): Longest length when there is a ordering constraint!
 *    We have an ordering constraint where a is a predecessor of b when we can insert one character to make them the same.
 *    Now, use LIS.
 *    T(i) : longest word chain ending at i_th and including i_th.
 *    T(i) = max(T(k) + 1) where k : 0 <= k < i and words[k] is a predecssor if words[i]
 *
 * TC: O(N*N*Word_size)
 *
 * TakeAway: Longest + any type of ordering constraint => LIS!
 *           Also, do SORT + LIS so that we can maintain the ordering constraint!
 */

class Solution
{
public:
    bool isPred(string &a, string &b)
    {
        if (a.size() + 1 == b.size())
        {
            bool diff = false;
            int aIndex = 0;
            for (int i = 0; i < b.size(); i++)
            {
                if (aIndex < a.size() && b[i] == a[aIndex])
                {
                    aIndex++;
                }
                else
                {
                    if (diff)
                        return false;
                    else
                    {
                        diff = true;
                    }
                }
            }
            return true;
        }

        return false;
    }
    int longestStrChain(vector<string> &words)
    {
        sort(words.begin(), words.end(), [](string &a, string &b)
             {
            if(a.length() < b.length())
                return true;
            else if(a.length() == b.length())
                return a < b;
            return false; }); // O(nlogn)

        vector<int> memo(words.size(), 1);
        int ans = 0;

        for (int i = 0; i < words.size(); i++) // O(n)
        {
            for (int j = 0; j < i; j++) // O(n)
            {
                if (isPred(words[j], words[i])) // O(word.size)
                {
                    memo[i] = max(memo[i], memo[j] + 1);
                }
            }
            ans = max(ans, memo[i]);
        }

        return ans;
    }
};

/**
 *
 * Different solution using the constraint on word size.
 *
 * Constraint said, 1 <= word.size() <= 16.
 * using this, we can just generate all possible predecessor.
 * All we need to make sure is, smaller legnth is processed before, so that we can accumulate the length.
 */

class Solution
{
public:
    int longestStrChain(vector<string> &words)
    {
        sort(words.begin(), words.end(), [](string &a, string &b)
             {
            if(a.length() < b.length())
                return true;
            else if(a.length() == b.length())
                return a < b;
            return false; });

        int ans = 0;
        vector<unordered_map<string, int>> mp(17); // For "index" legnth of word, word -> longest chain length

        for (auto &w : words)
        { // O(N)
            if (mp[w.size()].count(w) == 0)
                mp[w.size()][w] = 1;
            // cout << w << " : ";
            for (int i = 0; i < w.size(); i++)
            {                                                           // O(16)
                string possiblePred = w.substr(0, i) + w.substr(i + 1); // O(16) -> Generate all possible predecessors
                // cout << possiblePred << ",";
                if (mp[w.size() - 1].count(possiblePred) > 0) // If that predecessor exists
                {
                    mp[w.size()][w] = max(mp[w.size()][w], mp[w.size() - 1][possiblePred] + 1); // accumulate the legnth
                }
            }
            // cout << endl;
            ans = max(ans, mp[w.size()][w]);
        }

        return ans;
    }
};