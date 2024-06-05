class Solution
{
public:
    /*
    Counting -> Usually can be solved using DP.
    If we don't have to list all of them, there is a way to use DP to group them and count!
    If there is an independent restriction, then think about adding it as a extra axis.
    This will help us distinguish the case! EX) #Absence = 1 or 0.

    T(#Lates, #Absence, Days) = # of non failure records
    If the last character we want to append is
    'A'
        T(0, 1, Days) = SUM(T(#Lates, 0, Days - 1)) If we add 'A', it will break Late streak. But, can only do this if we have no Absence
    'L'
        T(#Lates + 1, #Absence, Days) = SUM(T(#Lates, #Absence, Days - 1)) It will add the number of Lates. So we can do this if #Lates were less than 2.
    'P'
        T(0, #Absence, Days) = SUM(T(#Lates, #Absence, Days - 1)) It will break the Late streak. No other restrictions.

    */
    int checkRecord(int n)
    {
        const int MOD = 1e9 + 7;
        vector<vector<vector<int>>> dp(3, vector<vector<int>>(2, vector<int>(n + 1, 0)));
        // # L's * # Absence * N
        if (n == 0)
            return 0;
        else if (n == 1)
            return 3;
        const string letter = "PLA";

        dp[0][0][1] = 1;
        dp[1][0][1] = 1;
        dp[0][1][1] = 1;

        for (int i = 2; i <= n; i++)
        {
            for (const char &c : letter)
            { // want to make this as a last letter
                for (int a = 0; a < 2; a++)
                { // Iterate all number of absences
                    if (a == 1 && c == 'A')
                        break; // Can only append 'A' if there is no previous absences

                    for (int numberOfL = 0; numberOfL < 3; numberOfL++)
                    { // iterate previous endings
                        if (c == 'L' && numberOfL == 2)
                            break; // cannot make due to 3 consec Late

                        if (c == 'A') // Late streak will be broken
                            dp[0][a + 1][i] = (dp[0][a + 1][i] + dp[numberOfL][a][i - 1]) % MOD;
                        else if (c == 'L')
                        {
                            dp[numberOfL + 1][a][i] = (dp[numberOfL + 1][a][i] + dp[numberOfL][a][i - 1]) % MOD;
                        }
                        else // c == 'P', Late streak will be broken
                            dp[0][a][i] = (dp[0][a][i] + dp[numberOfL][a][i - 1]) % MOD;
                    }
                }
            }
        }
        int s = 0;
        for (int r = 0; r < 3; r++)
        {
            for (int a = 0; a < 2; a++)
            {
                s = (s + dp[r][a][n]) % MOD;
            }
        }
        return s;
    }
};
