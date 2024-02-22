class Solution
{
public:
    /*
    .. A B ..
    A < B, Answer[A] = 1
    A > B at least answer[B] + x

    monotonic stack? (want to keep the bigger one's idx) => we only want the big ones in the future!
    Dec stack from right? Keep big ones in dec order since lower value after big value doesn't matter
    pop until it gets warmer temperature, get idx difference, and push itself.(any colder temperature that
    comes after current idx doesn't affect the answer for temperatures that comes left to current one)
    */
    typedef pair<int, int> Pair;
    vector<int> dailyTemperatures(vector<int> &temperatures)
    {
        stack<Pair> st; // num, idx
        vector<int> ans(temperatures.size(), 0);
        for (int i = temperatures.size() - 1; i >= 0; i--)
        {
            // pop until it gets warmer day
            while (!st.empty() && st.top().first <= temperatures[i])
            {
                st.pop();
            }
            if (st.empty())
                ans[i] = 0;
            else
            {
                ans[i] = st.top().second - i;
            }
            st.push({temperatures[i], i});
        }

        return ans;
    }
};