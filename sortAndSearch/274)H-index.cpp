/**
 *
 * Find H-index: at least "h" papers has at least "h" citations.
 *
 * 1. Brute-force: For each citation v, count the number of papers that has at least "v" citations
 * 2. Sort + linear search:
 *      Sort, number of papers with at least "citations[i]" citation is just "citations.size() - i"
 *      Should be careful because #papers can be a base of h-index too. ex) [10,10,10] -> H-index is 3.
 *
 *      (a) If #paper < citation => H-index = #paper.
 *          All papers has at least "v" number of citations.(since we only counted at least "v")
 *          Since #paper < v, at least #paper number of paper has a citations with #paper < v.
 *          ex) [10,10,10]
 *      (b) If citation < #paper => H-index = citation
 *          We have #paper number of papers with at least "citation".
 *          ex) [3,3,3,3]
 *      Conclusion: For each citation c, H-index = min(#paper with at least c citations, c);
 *
 * 3. Sort + binsearch
 *      In (a) case, We can go left since #paper is the bottleneck, we should increasae #paper
 *                   If we go right, we just lower #paper and increase citation, so it will not #paper < citation equality => No possible improvement.
 *      In (b) case, we can go right since citation is the bottleneck, should increase citation
 *                   If we go left in this case, we just lower the citation, and increase the #paper (array size - i) -> no possibility of getting a better h-index
 */
class Solution
{
public:
    int hIndex(vector<int> &citations)
    {
        // Brute force O(N^2) => For each citation, count how many citations are there at least

        sort(citations.begin(), citations.end());
        int h = 0;
        for (int i = 0; i < citations.size(); i++)
        {
            int paperAtLeastCur = citations.size() - i;
            h = max(h, min(citations[i], paperAtLeastCur));
        }
        return h;
    }
};

/**
 * Advanced: Using BinSearch
 */
class Solution
{
public:
    void binSearch(vector<int> &citations, int left, int right, int &h)
    {
        if (left > right)
            return;

        int mid = left + (right - left) / 2;

        int citation = citations[mid];
        int paperAtLeastCur = citations.size() - mid;

        if (citation <= paperAtLeastCur)
        {
            // h index can be citation -> go higher
            h = max(h, citation);
            return binSearch(citations, mid + 1, right, h);
        }
        else // paperAtLeastCur < citation
        {
            // Lacks paper to make h-index be citation
            // at least #paperAtLeastCur number of paper has #paperAtLeastCur < citation as a citation
            // So, can get #paperAtLeastCur for h-index.
            // h-index <= paperAtLeastCur < citation
            h = max(h, paperAtLeastCur);
            return binSearch(citations, left, mid - 1, h);
        }
    }
    int hIndex(vector<int> &citations)
    {
        // Brute force O(N^2) => For each citation, count how many citations are there at least

        sort(citations.begin(), citations.end());
        int h = 0;

        binSearch(citations, 0, citations.size() - 1, h);
        return h;
    }
};