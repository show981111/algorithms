/**
 * @brief How to increase the bottom i elems?
 * Brute force... make an array
 * [ith index] -> add 'X'
 * However, stack pops element one at a time! from the top!
 * We can just add the value when we pop it and
 * propagate this value to the bottom!
 *
 * *** what if we are incrementing top K element?
 * Store [st.size()] => pair<int,int> (value, st.size() - k)
 * Add each pair's value one by one.
 * When we pop, add those pairs and propagate pair
 * if the index is within the threshold
 *
 */

class CustomStack
{
public:
    CustomStack(int maxSize)
    {
        this->maxSize = maxSize;
        inc.push_back(0); // for 0 index
    }

    void push(int x)
    {
        if (st.size() == maxSize)
            return;
        st.push(x);
        inc.push_back(0);
    }

    int pop()
    {
        if (st.size() <= 0)
            return -1;
        int t = st.top();
        int N = st.size();
        t += inc[N];
        if (N - 1 >= 1)
        {
            inc[N - 1] += inc[N];
        }
        inc.pop_back();
        st.pop();
        return t;
    }

    void increment(int k, int val)
    {
        int below = min(k, (int)st.size());
        inc[below] += val;
    }

private:
    int maxSize;
    stack<int> st;
    vector<int> inc;
    // unordered_map<int,int> inc;
};

/**
 * @brief Using a Map...
 * If we are using a "UNSINGED INT" as a Key,,,
 * Think about using a Vector!
 *
 */
class CustomStack
{
public:
    CustomStack(int maxSize)
    {
        this->maxSize = maxSize;
    }

    void push(int x)
    {
        if (st.size() == maxSize)
            return;
        st.push(x);
    }

    int pop()
    {
        if (st.size() <= 0)
            return -1;
        int t = st.top();
        int N = st.size();
        if (inc.find(N) != inc.end())
        {
            int offset = inc[N];
            t += offset;
            inc.erase(N);
            if (N - 1 >= 1)
                inc[N - 1] += offset;
        }
        st.pop();
        return t;
    }

    void increment(int k, int val)
    {
        inc[min(k, (int)st.size())] += val;
    }

private:
    int maxSize;
    stack<int> st; // val, inc
    unordered_map<int, int> inc;
};
