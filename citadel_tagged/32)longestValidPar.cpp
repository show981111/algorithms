/**
 * Deque!
 */

class Solution
{
public:
    int add(char x)
    {
        if (x == '(')
            return 1;
        return -1;
    }
    struct Par
    {
        int open;
        int close;
    };
    int longestValidParentheses(string s)
    {
        // brute force O(N^3) check all substrings.
        int start = 0, end = 0;
        int maxLength = 0;
        deque<Par> pars;

        while (start < s.size())
        {
            while (start < s.size() && start == ')') // cannot start with closed one
            {
                start++;
            }
            // start == '('
            end = start;

            deque<Par> closedPars; // in order to record contiguous closed pairs
            while (end < s.size())
            {
                if (s[end] == '(')
                    pars.push_back(Par{end, -1});
                else
                { // ')'
                    if (pars.empty())
                        break;
                    pars.back().close = end;
                    // closedPars.push_back(pars.back());
                    maxLength = max(maxLength, pars.back().close - pars.back().open + 1);
                    while (!closedPars.empty() && closedPars.back().open > pars.back().open &&
                           closedPars.back().close < pars.back().close) // If previously closed par gets dominated by currently closed par ex) (())
                    {
                        closedPars.pop_back(); // pop it and push the larger dominating par.
                    }
                    closedPars.push_back(pars.back());
                    pars.pop_back();
                }
                end++;
            }
            // end >= s.size() or s[end] is a closing parenthesis that is not matching

            int prevOpened = -1;
            int prevClosed = -1;
            while (closedPars.size() > 0)
            {
                if (prevClosed == -1 || prevClosed + 1 < closedPars.front().open)
                { // can't concatenate, not contiguous
                    prevOpened = closedPars.front().open;
                    prevClosed = closedPars.front().close;
                }
                else if (prevClosed + 1 == closedPars.front().open)
                {
                    prevClosed = closedPars.front().close; // can concatenate. Contiguous
                }
                closedPars.pop_front();
                if (prevClosed != -1)
                    maxLength = max(maxLength, prevClosed - prevOpened + 1);
            }

            pars.clear();
            start = end + 1;
        }

        return maxLength;
    }
};

/**
 * Optimized using stack.
 *
 * Key observation:
 *  After we clear the open par when we faced the ')',
 *  If we look at the top of the stack, then it tells us where does the contiguous par started.
 *  Why?
 *  If all parenthesis after the top one got cleared, that means this parenthesis started from top one's index + 1.
 *  The reason is, there is no unbalanced ')' inserted after that top one. (we update stack index if there is too many ')' because we know
 *                                                                          we cannot build a contiguous pars with overly closed pairs )
 */
class Solution
{
public:
    int longestValidParentheses(string s)
    {
        // brute force O(N^3) check all substrings.
        int start = 0, end = 0;
        int maxLength = 0;
        vector<int> openPars; // store the index of open parenthesis
        // contiguous parenthesis can start from after the back of this arry
        openPars.push_back(-1); // for simplicity, add buffer -1. (contiguous par can start from 0 index)

        while (start < s.size())
        {
            while (start < s.size() && start == ')') // cannot start with closed one
            {
                openPars[0] = start; // update the possible index of starting parenthesis
                                     // There is no way contiguous parenthesis start from unbalanced ')'
                start++;
            }
            end = start;

            while (end < s.size())
            {
                if (s[end] == '(')
                {
                    openPars.push_back(end); // push open par
                }
                else
                {
                    if (openPars.size() == 1)
                    { // unbalanced close
                        openPars[0] = end;
                        break;
                    }
                    else
                    {
                        openPars.pop_back(); // this par get matched
                        maxLength = max(maxLength, end - openPars.back());
                        // Every open pars in stack is not unbalanced, which means no over close pars
                        // this means, all pars can be matched in the future.
                        // If we cleared all openPars from previous open par,
                        // that means parenthesis started from the next index of previous open Par.
                        // => Contiguous par can start from the "next index of previous open par!"
                    }
                }
                end++;
            }

            start = end + 1;
        }

        return maxLength;
    }
};