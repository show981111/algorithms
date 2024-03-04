class Solution
{
public:
    vector<vector<int> > intervalIntersection(vector<vector<int> > &firstList, vector<vector<int> > &secondList)
    {
        vector<vector<int> > res;
        auto fIter = firstList.begin();
        auto sIter = secondList.begin();
        while (fIter != firstList.end() && sIter < secondList.end())
        {

            if ((*fIter)[0] <= (*sIter)[0])
            {
                if ((*fIter)[1] < (*sIter)[0])
                { // no intersection
                    i++;
                }
                else if ((*fIter)[1] <= (*sIter)[1])
                {
                    res.push_back({(*sIter)[0], (*fIter)[1]});
                    i++; // firstList one interval is closed
                }
                else
                { // (*fIter)[1] > (*sIter)[1]
                    res.push_back({(*sIter)[0], (*sIter)[1]});
                    j++; // secList an interval is closed
                }
            }
            else
            { // (*fIter)[0] > (*sIter)[0]
                if ((*sIter)[1] < (*fIter)[0])
                {
                    j++;
                }
                else if ((*fIter)[1] <= (*sIter)[1])
                {
                    res.push_back({(*fIter)[0], (*fIter)[1]});
                    i++; // firstList one interval is closed
                }
                else
                { // (*fIter)[1] > (*sIter)[1]{
                    res.push_back({(*fIter)[0], (*sIter)[1]});
                    j++; // secList an interval is closed
                }
            }
        }
        return res;
    }
};