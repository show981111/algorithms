// Sliding Window : but O(s2.length()) -> LINEAR
// When moving sliding window, only fix offset(previous starting point, current endpoint)
// 0 1 2 3 4 5 6
// v v v => func(0) + func(1) + func(2) = prevSum
//   v v v => preSum - func(0) + func(3) = prevSum
//     v v v => preSum - func(1) + func(4) = prevSum ... on & on

class Solution
{
public:
    bool checkInclusion(string s1, string s2)
    {
        int freq[26] = {
            0,
        };
        for (int i = 0; i < s1.length(); i++)
        {
            freq[s1[i] - 'a']++;
        }

        int startWindowIndex = 0;
        int step = startWindowIndex;
        while (step < s2.length())
        {
            freq[s2[step] - 'a']--;
            if (step + 1 < s1.length())
                step++;
            else
            {
                bool flag = true;
                for (int k = 0; k < 26; k++)
                {
                    if (freq[k] != 0)
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                    return true;
                freq[s2[startWindowIndex] - 'a']++;
                startWindowIndex++;
                step++;
            }
        }
        return false;
    }
};