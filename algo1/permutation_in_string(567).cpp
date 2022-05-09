// O(s2.length() * s1.length())

class Solution
{
public:
    bool checkInclusion(string s1, string s2)
    {
        int arr[28] = {
            0,
        };
        for (int i = 0; i < s1.length(); i++)
        {
            arr[s1[i] - 'a']++;
        }

        for (int i = 0; i < s2.length(); i++)
        {
            if (i + s1.length() > s2.length())
                return false;
            bool flag = true;
            int tempArr[28] = {
                0,
            };
            copy(arr, arr + 28, tempArr);
            for (int k = i; k < i + s1.length(); k++)
            {
                if ((--tempArr[s2[k] - 'a']) < 0)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                return true;
            }
        }
        return false;
    }
};