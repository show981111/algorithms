/**
 * Union-find requires us to have an edge!
 *
 * Process of using union-find is
 * For edge in edges
 *      Merge
 *
 * So, we need to construct edges first.
 * And how to construct an edge could be a bottleneck!
 *
 * Here, we need to construct an edge between A, B where gcd(A,B) > 1
 * However, we don't need to do this for all paris but with one elem that shares the factor
 * Since we are only checking the connectivity, as long as we have "edges" between A,B it is fine!
 */

class Solution
{
public:
    /*
    Brute force: O(N^2)*O(Finding Sequence = N)

    12 8 4 3
    [...] [X]
    IF [...] is traversable, if any element from [...] has an element Y such that gcd(X,Y) > 1,
    [...] + [X] is traversable since every elem can just go through Y.

    But, we can go through some future elems.
    EX) [2,4] [3] [6]. 6 is future elem that can make us to get to [3]
    Can we sort in a way that no elem in the future will make cur elem traversable?
    Descending
    [A B C] [D] [E]
    D >= E
    Is it possible gcd(D,E) > 1 && gcd([A,B,C], [E]) > 1 && gcd([A,B,C], [D]) == 1?
    YES
    32    16    9   6

-------------------------

    UNION FIND? O(N^2) -> TLE
    We want every elem to have the same parent, so that we can traverse to any element we want.
    (like a rooted tree, we can traverse to top and go bottom)

    elems can be grouped into the largest ones.
    [42,99,98]
    99 can be grouped with 42
    but 98 should be grouped with 42 not 99 => Can't use path compression: worst O(N^3)

    What we want is connectivity. Since all pairs should be connected -> All nodes should be connected.
    Connectivity is defined as traversability (share an elem that has gcd > 1)
    For connectivity, we can use union-find, but connecting it self takes O(N^2) if we use naive gcd comparison
    for all pairs.
    Can we come up with better one? How to connect elems in a faster way.

    */
    int getPar(vector<int> &par, int x)
    {
        if (par[x] == x)
            return x;
        else
            return par[x] = getPar(par, par[x]);
    }

    bool canTraverseAllPairs(vector<int> &nums)
    {
        unordered_set<int> st(nums.begin(), nums.end());
        if (st.count(1) > 0 && nums.size() > 1)
            return false;

        vector<int> uNums(st.begin(), st.end());
        vector<int> primes(100005, -1);
        vector<vector<int>> edges;

        for (int i = 0; i < uNums.size(); i++)
        {
            // Traverse all possible factors and connect with "ONE" element that shares the same factor
            for (int p = 2; p * p <= uNums[i]; p++)
            {
                if (uNums[i] % p == 0)
                {
                    if (primes[p] != -1)
                    {
                        edges.push_back({primes[p], i}); // connect
                    }
                    else
                    {
                        primes[p] = i;
                    }
                    int pair = uNums[i] / p;
                    if (primes[pair] != -1)
                    {
                        edges.push_back({primes[pair], i}); // connect
                    }
                    else
                    {
                        primes[pair] = i;
                    }
                }
            }
            if (primes[uNums[i]] != -1)
            {
                edges.push_back({primes[uNums[i]], i}); // connect
            }
            else
            {
                primes[uNums[i]] = i;
            }
        }
        // Now connectivity check
        vector<int> par(uNums.size());
        for (int i = 0; i < uNums.size(); i++)
        {
            par[i] = i;
        }

        for (auto &e : edges)
        {
            int ap = getPar(par, e[0]);
            int bp = getPar(par, e[1]);

            if (ap >= bp)
            {
                par[bp] = ap;
            }
            else
            {
                par[ap] = bp;
            }
        }

        int p = getPar(par, 0);

        for (int i = 1; i < uNums.size(); i++)
        {
            if (p != getPar(par, i))
            {
                return false;
            }
        }
        return true;
    }
};
