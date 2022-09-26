/**
 * @brief Rotation
 * if we rotate A and get B,
 * B is in A + A
 *
 */

class Solution
{
public:
    bool rotateString(string s, string goal)
    {
        if (s.length() != goal.length())
            return false;
        s += s;
        int i = 0;
        int N = s.size();
        int G = goal.size();
        int index = 0;
        while (i < N)
        {
            bool stopped = false;
            while (i < N && goal[index] == s[i])
            {
                index++;
                i++;
                stopped = true;
                if (index == goal.size())
                    return true;
            }
            // if it is stopped, then we should start from there
            if (!stopped)
                i++;
            index = 0;
        }

        return false;
    }
};