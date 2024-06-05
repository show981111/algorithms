class Solution
{
public:
    int maxDepth(string s)
    {
        size_t ans = 0;
        vector<char> st;
        for (char &c : s)
        {
            if (c == '(')
            {
                st.push_back(c);
                ans = max(ans, st.size());
            }
            else if (c == ')')
                st.pop_back();
        }

        return ans;
    }
};