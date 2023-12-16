class Solution
{
public:
    bool isValid(string s)
    {
        vector<char> st;

        for (char &c : s)
        {
            char k = c;
            bool close = true;
            if (c == ')')
            {
                k = '(';
            }
            else if (c == ']')
            {
                k = '[';
            }
            else if (c == '}')
            {
                k = '{';
            }
            else
                close = false;

            if (close)
            {
                if (st.empty() || st.back() != k)
                    return false;
                st.pop_back();
            }
            else
            {
                st.push_back(c);
            }
        }

        return st.size() == 0;
    }
};