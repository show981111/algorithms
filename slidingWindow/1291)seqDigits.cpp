/**
 * Generate number like sliding window.
 * num -= firstdigit * digits
 * num *= 10 // shift
 * num += new last digit
 */

class Solution
{
public:
    int getDigitNum(int num)
    {
        int d = 0;
        while (num > 0)
        {
            d++;
            num /= 10;
        }
        return d;
    }
    int makeNum(int firstDigit, int d)
    {
        int num = 0;
        int curDigit = firstDigit;
        while (d > 0)
        {
            num += curDigit;
            d--;
            if (d == 0)
                break;
            num *= 10;
            curDigit++;
        }
        return num;
    }
    vector<int> sequentialDigits(int low, int high)
    {
        vector<int> seqs;
        int lowDigitNum = getDigitNum(low);
        int highDigitNum = getDigitNum(high);

        for (int d = lowDigitNum; d <= highDigitNum; d++)
        {
            int num = makeNum(1, d);
            for (int start = 1; start <= 10 - d; start++)
            {
                // cout << num << endl;
                if (num >= low && num <= high)
                {
                    seqs.push_back(num);
                }
                else if (num > high)
                    break;
                num -= start * pow(10, d - 1);
                num = num * 10;
                num += start + d;
            }
        }
        return seqs;
    }
};