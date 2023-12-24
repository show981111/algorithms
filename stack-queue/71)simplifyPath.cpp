/**
 * Splitting the string with a delimiter => Use istringstream! with last parameter "character". so put '/' not "/".
 */

class Solution
{
public:
    string simplifyPath(string path)
    {
        vector<string> vec;
        string w;
        istringstream iss(path);
        while (std::getline(iss, w, '/'))
        {
            if (w.empty())
                continue;
            else if (w == ".")
                continue;
            else if (w == "..")
            {
                if (!vec.empty())
                    vec.pop_back();
            }
            else
                vec.push_back(w);
        }
        string ans = "/";
        for (string &w : vec)
        {
            ans += w + "/";
        }
        if (ans.size() > 1)
            ans.pop_back();
        return ans;
    }
};

/**
 * Just append directly
 */

class Solution
{
public:
    string simplifyPath(string path)
    {
        string ans = "";
        string w;
        istringstream iss(path);
        while (std::getline(iss, w, '/'))
        {
            if (w.empty())
                continue;
            else if (w == ".")
                continue;
            else if (w == "..")
            {
                if (!ans.empty())
                {
                    while (ans.back() != '/')
                        ans.pop_back();
                    ans.pop_back(); // pop last /
                }
            }
            else
                ans += '/' + w;
        }
        if (ans.empty())
            return "/";
        return ans;
    }
};