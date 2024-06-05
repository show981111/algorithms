class Solution
{
public:
    /*
    Since laser is in each row and column doesn't affect lasers,
    let's use number of devices in each row.
    Then, we can just multiply the device in the next row and reset the number of devices
    to that row.
    */
    int countOnes(string &s)
    {
        int ones = 0;
        for (const char &c : s)
        {
            if (c == '1')
                ones++;
        }
        return ones;
    }
    int numberOfBeams(vector<string> &bank)
    {
        int beams = 0;
        int cur = 0, prev = 0;
        for (int r = 0; r < bank.size(); r++)
        {
            int temp = countOnes(bank[r]);
            if (temp == 0)
                continue;
            prev = cur;
            cur = temp;
            beams += prev * cur;
        }
        return beams;
    }
};