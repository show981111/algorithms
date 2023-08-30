/**
 * @brief Key is using the recursion to simplify the code!
 *
 */

class Solution
{
public:
    string one(int num)
    {
        switch (num)
        {
        case 1:
            return "One";
        case 2:
            return "Two";
        case 3:
            return "Three";
        case 4:
            return "Four";
        case 5:
            return "Five";
        case 6:
            return "Six";
        case 7:
            return "Seven";
        case 8:
            return "Eight";
        case 9:
            return "Nine";
        }
        return "";
    }

    string twoLessThan20(int num)
    {
        switch (num)
        {
        case 10:
            return "Ten";
        case 11:
            return "Eleven";
        case 12:
            return "Twelve";
        case 13:
            return "Thirteen";
        case 14:
            return "Fourteen";
        case 15:
            return "Fifteen";
        case 16:
            return "Sixteen";
        case 17:
            return "Seventeen";
        case 18:
            return "Eighteen";
        case 19:
            return "Nineteen";
        }
        return "";
    }

    string ten(int num)
    {
        switch (num)
        {
        case 2:
            return "Twenty";
        case 3:
            return "Thirty";
        case 4:
            return "Forty";
        case 5:
            return "Fifty";
        case 6:
            return "Sixty";
        case 7:
            return "Seventy";
        case 8:
            return "Eighty";
        case 9:
            return "Ninety";
        }
        return "";
    }
    string numberToWords(int num)
    {
        if (num == 0)
            return "Zero";
        int billion = 1000000000;
        int million = 1000000;
        int thousand = 1000;

        string res = "";

        if (num >= billion)
        {
            int b = num / billion;
            res += numberToWords(b) + " Billion ";
            num -= b * billion;
        }
        if (num >= million)
        {
            int m = num / million;
            res += numberToWords(m) + " Million ";
            num -= m * million;
        }
        if (num >= thousand)
        {
            int t = num / thousand;
            res += numberToWords(t) + " Thousand ";
            num -= t * thousand;
        }
        if (num >= 100)
        {
            int h = num / 100;
            res += one(h) + " Hundred ";
            num -= h * 100;
        }
        // cout << num << endl;
        if (num >= 20)
        {
            res += ten(num / 10) + " " + one(num % 10);
        }
        else if (num >= 10)
        {
            res += twoLessThan20(num);
        }
        else
        {
            res += one(num % 10);
        }
        if (res.size() > 0 && res.back() == ' ')
            res.pop_back();
        return res;
    }
};