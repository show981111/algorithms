/**
 *
 * Observation:
 * Divide sections in to decreasing section / equal section / increasing section
 * Should increase/decrease #candies for non-equal section.
 *
 * Use Two pass in different directions because we do not know how many times it will decrease!
 * and Take a MAX!
 */

class Solution
{
public:
    // strict decreasing, strict increasing section => should dec/inc the candy
    //
    int candy(vector<int> &ratings)
    {
        int totalCandies = 0;
        // 3 3 2 1 0 1 2 3 3 2 1 0 1 2 3
        // 1 4 3 2 1 2 3 4 3 3 2 1 2 3 4
        vector<int> candies(ratings.size(), 1);
        candies[0] = 1;
        // L -> R, search increasing seq
        for (int i = 1; i < ratings.size(); i++)
        {
            if (ratings[i] > ratings[i - 1])
            {
                candies[i] = candies[i - 1] + 1; // min satisfying candies
            }                                    // else keep it as 1.
        }

        for (int i = ratings.size() - 2; i >= 0; i--)
        {
            if (ratings[i] > ratings[i + 1])
            {
                candies[i] = max(candies[i], candies[i + 1] + 1);
            } // else leave it
        }

        for (int c : candies)
        {
            totalCandies += c;
        }
        return totalCandies;
    }
};

/**
 * ONE PASS
 *
 * Identify which computation is getting overlapped.
 * Be consistent and keep the invariant.
 *  EX) In all cases, leave the last element for next step
 * Then, comupte the last element from the next step!
 */

class Solution
{
public:
    // Checking inc/dec/monotone sections
    // Leave the last one from the section because we do not know it will
    // be in inc/dec/monotone

    /**
    For increasing section, starting point will always be 1 (cause its local minima)
    For dec section, starting point should at least be the length of that section.
        It could be bigger than that if it was the end of the increasing section.
        Ex)   1 2 3 4 3
        Candy 1 2 3 4 1 (decreasing section 4-3, but we should give out 4 at first 4 not 2)
    For monotone same as dec.
        EX) 1 2 3 4 4
            1 2 3 4 1 (monotone section 4-4, but we should give out 4 at first 4 not 1)
    */
    int candy(vector<int> &ratings)
    {
        int totalCandies = 0;
        int curCandy = 1;

        for (int i = 0; i < ratings.size() - 1;)
        {
            int left = i;
            if (ratings[i] < ratings[i + 1])
            {
                // if increasing
                while (i + 1 < ratings.size() && ratings[i] < ratings[i + 1])
                {
                    i++;
                }
                int ws = i - left + 1;
                // starting point of inc section is always 1
                totalCandies += (ws) * (ws + 1) / 2 - ws; // leave last one
                curCandy = ws;
            }
            else if (ratings[i] == ratings[i + 1])
            {
                while (i + 1 < ratings.size() && ratings[i] == ratings[i + 1])
                {
                    i++;
                }
                int ws = i - left + 1;
                if (curCandy > 1)
                { // If starting point should be bigger than 1, adjust
                    totalCandies += curCandy - 1;
                }
                totalCandies += ws - 1;
                curCandy = 1; // last one is always 1
            }
            else if (ratings[i] > ratings[i + 1])
            {
                // if dec
                while (i + 1 < ratings.size() && ratings[i] > ratings[i + 1])
                {
                    i++;
                }
                int ws = i - left + 1;
                if (curCandy > ws)
                { // if starting point is bigger than windowSize, adjust
                    totalCandies += curCandy - ws;
                }
                totalCandies += (ws) * (ws + 1) / 2 - 1; // leave last one
                curCandy = 1;                            // last one is always 1
            }
        }
        totalCandies += curCandy; // add last one
        return totalCandies;
    }
};