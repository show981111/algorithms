class Solution
{
public:
    /*
    Face-up: Lose token[i] power, gain 1 score (at least token[i] power)
    Face-down: Get token[i] power, lose 1 score (at least 1 score)

    Maximize total score.
    Should Perform as many face-up as possible.
    Should use face-down on large token[i] value.

    Would greedy work?
    For large value, play down. For small value, play up.
    */
    int bagOfTokensScore(vector<int> &tokens, int power)
    {
        sort(tokens.begin(), tokens.end());
        int maxScore = 0;
        int l = 0;
        int r = tokens.size() - 1;
        int score = 0;
        while (l <= r)
        {
            if (power < tokens[l])
            {
                // Not enough power left. Play down
                if (score >= 1)
                {
                    power += tokens[r--];
                    score--;
                }
                else
                    break;
            }
            else
            {
                // play up
                power -= tokens[l++];
                score++;
                maxScore = score;
            }
        }
        return maxScore;
    }
};