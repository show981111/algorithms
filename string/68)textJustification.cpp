/**
 * Do stuff in sequence.
 */

class Solution
{
public:
    vector<string> fullJustify(vector<string> &words, int maxWidth)
    {
        vector<string> ans;
        vector<string> cur;
        int curLength = 0;
        int i = 0;
        int from = 0;
        for (i = 0; i < words.size();)
        {
            if (curLength + words[i].size() <= maxWidth)
            {
                cur.push_back(words[i]);
                curLength += words[i].size() + 1;
                i++;
            }
            else
            {
                // finish previous line & Distribute spaces
                int totalSpaces = maxWidth - curLength + cur.size(); // last space

                int gaps = cur.size() - 1;
                int residue = gaps == 0 ? 0 : totalSpaces % gaps;
                string line = "";
                for (int j = 0; j < cur.size(); j++)
                {
                    line += cur[j];
                    int spaceCnt = gaps == 0 ? totalSpaces : totalSpaces / gaps;
                    if (j == cur.size() - 1 && j != 0)
                    {
                        continue;
                    }
                    if (residue > 0)
                    {
                        spaceCnt++;
                        residue--;
                    }
                    for (int sz = 0; sz < spaceCnt; ++sz)
                        line.push_back(' ');
                }
                ans.emplace_back(line);

                // need to change the line
                cur.clear();
                curLength = 0;
            }
        }
        // process last line
        string lastLine = "";
        for (auto &w : cur)
        {
            lastLine += w;
            if (lastLine.size() < maxWidth)
                lastLine.push_back(' ');
        }
        while (lastLine.size() < maxWidth)
            lastLine.push_back(' ');
        ans.emplace_back(lastLine);
        return ans;
    }
};