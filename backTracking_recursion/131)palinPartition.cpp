class Solution
{
public:
    /*
    suppose we have a string S.
    If I split at x, S[:x], S[x:], if both are palindrome, add.
    Then, we can go further, PalindromePartition(S[:x]) + S[x:]
    Recursive structure!
    Even tho I do DP to figure out which S[a:b] is palindrome, I should find the complete partition
    such as [a:b], [b+1:c] [c+1:]
    */
    bool isPalin(string &s)
    {
        int l = 0, r = s.size() - 1;
        while (l < r)
        {
            if (s[l] == s[r])
            {
                l++;
                r--;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
    // return all possible combinations when we split at the all possible positions
    // [0:split), [split :]
    vector<vector<string>> solve(string &s)
    {
        vector<vector<string>> res;

        for (int split = s.size(); split >= 1; split--) // split starting from the back
        {
            string rear = s.substr(s.size() - split, split);
            string front = s.substr(0, s.size() - split);
            if (isPalin(rear)) // if this chunk is palindrome, we have a possbility to make a palindrom partition!
            {
                if (front.empty()) // if it is a whole chunk
                {
                    vector<string> v;
                    v.push_back(rear);
                    res.emplace_back(v);
                    continue;
                }
                vector<vector<string>> frontPartitions = solve(front); // otherwise, get the palidrome partitions of the rest of the string!
                for (auto &v : frontPartitions)
                {
                    v.push_back(rear); // insert rear to all combinations to complete the partition!
                    res.emplace_back(v);
                }
            }
        }
        return res;
    }

    /**
     * Alternative using refernce not returning
     */
    void solve(string &s, vector<vector<string>> &res)
    {
        for (int split = s.size(); split >= 1; split--)
        {
            string rear = s.substr(s.size() - split, split); // 0,1
            string front = s.substr(0, s.size() - split);    //
            if (isPalin(rear))
            {
                if (front.empty())
                {
                    vector<string> v;
                    v.push_back(rear);
                    res.emplace_back(v);
                    continue;
                }
                int curIndex = res.size(); // record the current res index.
                solve(front, res);         // this recursive call will push all partition combinations to res, but they will not include rear
                for (int i = curIndex; i < res.size(); i++)
                {
                    res[i].push_back(rear); // insert rear to those combinations
                }
            }
        }
    }

    vector<vector<string>> partition(string s)
    {
        return solve(s);
    }
};

/**
 * @brief Using a reference.
 *
 * Always when we assign vector,
 * it is expensive! (O(N))
 *
 * so passing by reference is much efficient
 *
 */

class Solution
{
public:
    // vector<vector<vector<string>>> memo;
    vector<vector<int>> palinMemo;
    bool isPalin(string &s, int from, int to)
    {
        if (from == to)
            return true;
        if (palinMemo[from][to] != 0)
        {
            return palinMemo[from][to] == 1;
        }
        int mid = (from + to) / 2;
        for (int i = from; i <= mid; i++)
        {
            if (s[i] != s[to - i + from])
            {
                palinMemo[from][to] = -1;
                return false;
            }
        }
        palinMemo[from][to] = 1;
        return true;
    }
    void gen(string &s, int from, int to, vector<string> &cur, vector<vector<string>> &ans)
    {
        if (from > to)
        {
            ans.push_back(cur);
            return;
        }

        for (int i = from; i <= to; i++)
        {
            if (isPalin(s, from, i))
            {
                // cout << s.substr(from, i - from + 1) << " is palin \n";
                cur.push_back(s.substr(from, i - from + 1));
                gen(s, i + 1, to, cur, ans);
                cur.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s)
    {
        // memo.resize(s.size());// 0 ~ i, partition list
        palinMemo.resize(s.size(), vector<int>(s.size()));
        vector<vector<string>> ans;
        vector<string> cur;
        gen(s, 0, s.size() - 1, cur, ans);
        return ans;
    }
};

/**
 * @brief Using a memo and return vector
 *
 */

class Solution
{
public:
    vector<vector<vector<string>>> memo;
    vector<vector<int>> palinMemo;
    bool isPalin(string &s, int from, int to)
    {
        if (from == to)
            return true;
        if (palinMemo[from][to] != 0)
        {
            return palinMemo[from][to] == 1;
        }
        int mid = (from + to) / 2;
        for (int i = from; i <= mid; i++)
        {
            if (s[i] != s[to - i + from])
            {
                palinMemo[from][to] = -1;
                return false;
            }
        }
        palinMemo[from][to] = 1;
        return true;
    }
    vector<vector<string>> gen(string &s, int from, int to)
    {
        if (from > to)
            return vector<vector<string>>();
        if (from == to)
        {
            return {{s.substr(from, 1)}};
        }
        if (memo[to].size() != 0)
        {
            return memo[to];
        }
        vector<vector<string>> cur;
        if (isPalin(s, from, to))
        {
            cur.push_back({s.substr(from, to - from + 1)});
        }
        for (int i = to; i >= from; i--)
        {
            if (isPalin(s, i, to))
            {
                // cout << s.substr(i, to - i + 1) << "is palin!" << endl;
                string cand = s.substr(i, to - i + 1);
                vector<vector<string>> next = move(gen(s, from, i - 1));
                for (auto &v : next)
                {
                    v.push_back(cand);
                }
                cur.insert(cur.end(), next.begin(), next.end());
                // cout << cur.size() << endl;
            }
        }
        memo[to] = move(cur);
        return memo[to];
    }
    vector<vector<string>> partition(string s)
    {
        memo.resize(s.size()); // 0 ~ i, partition list
        palinMemo.resize(s.size(), vector<int>(s.size()));
        return gen(s, 0, s.size() - 1);
    }
};
