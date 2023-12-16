/**
 *
 * Substring counting with equality conditions, it rings a bell of prefix sum.
 *
 * Prefix + Map using the Count[i:j] = Prefix[j] - Prefix[i-1]
 *
 * If we have to find some sort of substrings/pairs that satisfies the condition,
 * we could use Prefix + Map to make O(N^2) -> O(N)
 *
 * The key of Prefix + Map is => 1. Create a Key 2. Retrieve the Key
 * 1) what is KEY of map?  VowelCount - ConsonantCount = P[i].V - P[i].C
 * 2) At index I, how can I get the KEY I want in O(1)? P[i].V - P[i].C is the key we are looking for.
 *
 * At index I, I want to pinpoint the number of J's where, Sub[j:i].V - Sub[j:i].C == 0.
 * Sub[j:i].V - Sub[j:i].C = (P[i].V - P[j-1].V) - (P[i].C - P[j-1].C)
 *                         = (P[i].V - P[i].C) - (P[j-1].V - P[j-1].C) == 0, => (P[i].V - P[i].C) == (P[j-1].V - P[j-1].C)
 *                         So, we can just look for (P[i].V - P[i].C)! and at each index, we record P[i].V - P[i].C to MAP!
 *
 * Now, how can I just count (V*C%k == 0)?
 * See below
 *
 *
 *
 * https://leetcode.com/problems/count-beautiful-substrings-ii/solutions/4330972/clever-problem-simple-o-n-k-solution/
 */

class Solution
{
public:
    /*
        b a e y h
    V   0 1 2 2 2
    C.  1 1 1 2 3
       -1 0 1 0 -1

    Sub[i:j].V - Sub[i:j].C = (P[i].V - P[j-1].V) - (P[i].C - P[j-1].C)
                            = (P[i].V - P[i].C) - (P[j-1].V - P[j-1].C)
        a b b a
    V   1 1 1 2
    C.  0 1 2 2
        1 0 -1 0

    1. Prefix[j].V - Prefix[i-1].V == Prefix[j].C - Prefix[i-1].C
    2. V * C % k == 0 => V * V % k == 0

    V*V % k == ((V%K)*(V%K))%K
    V = kp + r.
    V*V = (kp + r)(kp + r) = k(...) + r^2, so V*V %K == r^2 % K
    Since V%K = r,   r^2 % K == (V%K)*(V%K) % K
    Using this fact,

    (CurV - prevV)*(CurV - prevV) MOD k
    == ((CurV - prevV) % K * (CurV - prevV) % K) % K
    (CurV - prevV) % K = CurV % K - prevV %K

    SO, If (CurV % K - prevV %K)^2 %K == 0, then V*V %K == 0
    */
    long long beautifulSubstrings(string s, int k)
    {
        // O(N*K)
        unordered_map<long long, unordered_map<long long, long long>> mp;
        long long curVowelCount = 0, curConsoCount = 0;
        long long ans = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
            {
                curVowelCount++;
            }
            else
                curConsoCount++;
            if (curVowelCount == curConsoCount && (curVowelCount * curVowelCount) % k == 0)
                ans++;
            long long diff = curVowelCount - curConsoCount;
            if (mp.count(diff) > 0)
            {
                for (auto &[prevV, count] : mp[diff])
                {
                    if ((curVowelCount - prevV) * (curVowelCount - prevV) % k == 0)
                        ans += count;
                }
            }

            mp[diff][curVowelCount % k]++;
        }
        return ans;
    }
};

/**
 * Alternative O(N)...
 * https://leetcode.com/problems/count-beautiful-substrings-ii/solutions/4330972/clever-problem-simple-o-n-k-solution/
 *
 * Interesting way to count pairs..
 */

long long beautifulSubstrings(string s, int k)
{
    unordered_map<int, vector<int>> grps;
    grps[0].push_back(0);
    long long vCount = 0;
    string vowels("aeiou");

    for (int i = 0, presum = 0; i < s.size(); i++)
    {
        if (vowels.find(s[i]) != string::npos)
        {
            ++presum;
            vCount++;
        }
        else
            --presum;
        grps[presum].push_back(vCount); // store current VowelCount
    }

    int x;
    for (x = 1; x <= k && x * x % k; x++)
        ;
    // cout << x << endl;
    int64_t ans = 0;

    for (auto &[diff, grp] : grps)
    {
        vector<int> mod(x);
        for (int i : grp)
        { // group of strings that can form a beautiful substring by subtrating each other
            // If they have the same VowelCount % x, then if it gets subtract, Vcnt in substring = (CurVcnt - PrevVcnt) % x == 0 then
            // it satisfies second requirement
            ans += mod[i % x]++;
        }
    }
    return ans;
}