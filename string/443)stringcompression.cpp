/*
Challenge: compress the word in-place

First Approach)
usually starting from the end can help string manipulation(due to shifting and inserting stuff)
However, since we have to keep the letters we compressed, we cannot just use pop_back, and we should use
insert and erase. -> which will be O(N^2). Also, insert will throw out of index, if it goes over the size

WHY HARD?
No matter where I start, -> or <- direction, it will be O(N^2) if I erase the letter as I go and insert the result.
How can we avoid insert and remove, which takes O(N)??
Only way to do this is, overwriting the original string since we have to do in-place
But, what if it goes over the original size? -> won't happen because
** Compressed Word <= Non-comporessed Word **
(When solving algo, important to find "invariant", or the characteristic of something!)
ex) one-edit away, find the characteristic of each operation.

String manipulation
1) Create Buffer(create a result string) and write the answer there
2) Use Separate index(two pointers) and Overwrite to the input! - in-place
3) Use Erase or Insert Which takes O(N)... not good
*/
class Solution
{
public:
    // a a b b c c c
    // 0 1 2 3 4 5 6
    // a 2 b 2 c
    int compress(vector<char> &chars)
    {
        int N = chars.size();
        int overwriteIndex = 0;
        int curCount = 1;
        for (int i = 0; i < N; i++)
        {
            if (i != N - 1 && chars[i] == chars[i + 1])
            {
                curCount++;
            }
            else
            { // i == N-1 || chars[i] != chars[i+1]
                // write the letter
                chars[overwriteIndex++] = chars[i];
                if (curCount > 1)
                { // if count is larger than 1, write count
                    string counter = to_string(curCount);
                    for (int c = 0; c < counter.size(); c++)
                    {
                        chars[overwriteIndex++] = counter[c];
                    }
                }
                curCount = 1;
            }
        }
        chars.erase(chars.begin() + overwriteIndex, chars.end());
        return chars.size();
    }
};