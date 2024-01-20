/*
Approach
https://leetcode.com/problems/maximum-elegance-of-a-k-length-subsequence/solutions/4599073/o-nlogn-greedy-solution/

1. Sort items by descending order of profit.
2. Add top K items. As we add items, keep the minimum profit per category where it has more than one element (since throwing away this element doesn't affect the #category)
3. After K iteration, if adding a new item can increase the number of categories, then do it. Throw away the min element, and add a new one.

Used data structures:
To keep the elements per category -> Category : minHeap (in profit)
To keep the min element from all minimum profits in each category -> ordered_set (ascending order in profit).

Though process:
Maxmize (total_profit + distinct_categories^2)
Two variable in optimization.
Subsequence -> sorting is allowed.
Can we do DP? optimial in K-1 cannot be connected to optimial in K since #distinct categories affect this.
T(i, j) = max el i

Can we fix something?
For that category, picking max profit is beneficial.
But dont know if we should stay in that cat or go to diff cat.

Fix profit?
Profit descending.
10 9 8 8
Get Max profit sum of K elems.
Adding an element should increase #cat, and throw away min elemen that doesn't reduce cat
Keep a map : Category -> profit pq (minHeap).
if(Cnt > 1), push to ordered set, <Cat,Min> (ascending order)
After K iteration, this set will have min numbers from each cat with more than one elem in ascending order.
Add new elem if it increases the #cat.
Otherwise,
Remove the first elem of ordered set (smallest profit with more than one elem in that category).
Go back to Cat -> pq map, pop() and if size > 1, push to ordered set.
=> If it only have one elem, Since it has the bigger profit than any other and it aslo increases the #cat, Should Keep it.
*/
class Solution
{
public:
    struct Element
    {
        int profit;
        int category;
    };
    long long findMaximumElegance(vector<vector<int>> &items, int k)
    {
        sort(items.begin(), items.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[0] > b[0]; });
        long long ans = 0;
        long long profitSum = 0;
        unordered_map<int, priority_queue<int, vector<int>, greater<int>>> catToProfits; // min heap per cat.
        auto elemComp = [](const Element &a, const Element &b)
        {
            if (a.profit < b.profit)
                return true;
            if (a.profit == b.profit)
                return a.category < b.category;
            return false;
        };
        set<Element, decltype(elemComp)> minProfits(elemComp);
        int seqSize = 0;
        for (int i = 0; i < items.size(); i++) // O(N)
        {
            if (seqSize < k)
            {
                seqSize++;
                profitSum += items[i][0];
                if (catToProfits[items[i][1]].size() > 0)
                {
                    Element curMin{catToProfits[items[i][1]].top(), items[i][1]};
                    minProfits.erase(curMin); // if we already inserted min, than erase O(logK)
                    catToProfits[items[i][1]].push(items[i][0]);
                    minProfits.insert({items[i][0], items[i][1]}); // update min to new one. O(logK)
                }
                else
                {
                    catToProfits[items[i][1]].push(items[i][0]); // add O(logK)
                }
            }
            else
            {
                // window full. Need to throw away one and add one.
                if (minProfits.empty())
                    break; // optimal since we have one elem per category
                if (catToProfits.count(items[i][1]) > 0)
                    continue; // cat already exists O(logK)

                Element victim = *minProfits.begin();
                minProfits.erase(minProfits.begin()); // erase from the set O(logK)
                catToProfits[victim.category].pop();  // victim gets erased O(logK)

                if (catToProfits[victim.category].size() >= 2)                                 // update min
                    minProfits.insert({catToProfits[victim.category].top(), victim.category}); // O(logK)

                catToProfits[items[i][1]].push(items[i][0]); // always a new one. O(logK)

                profitSum -= victim.profit;
                profitSum += items[i][0];
            }

            if (seqSize == k)
                ans = max(ans, profitSum + (long long)catToProfits.size() * (long long)catToProfits.size());
        }
        return ans;
    }
};
/*
[[4,5],[4,2],[7,4],[2,3],[5,5],[5,3],[5,11],[6,4],[9,4],[1,7],[6,12],[8,10],[5,14],[8,4]]

*/