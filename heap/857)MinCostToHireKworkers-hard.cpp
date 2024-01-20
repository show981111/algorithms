/**
 *
 * When we want to optimize for Two Variable,
 * WE NEED TO FIX ONE.
 *
 * Basically, if we consider all pairs, we will get Quadratic TC.
 * However, if we fix one variable, and compute the answer, reuse this result for next iteration,
 * we can get linear/NlogN TC just like we did in Sliding Window
 *
 * Below, we identified the condition where all elements should be available for next iteration.
 * (IF w[base]/q[base] >= w[i]/q[i], we can include i_th item!)
 * Thus, we sort based on w[i]/q[i] in ascending order.
 * Set i_th item as a base, compute sum, move to i+1_th, pop smallest one, push new elem, update answer
 */
class Solution
{
public:
    /*
    Min amount money that satisfies:
    k elements/ At least min Wage + paid in ratio of quality

    Brute Force
    Per quality, suppose that quality is hired. Compute how much to pay compared to this one.
    Then, sort, get top K. -> O(N*(N+ NlogN))

    1 1 3 10 10
    8 7 3 2  2
    Choose Wage / Quality min?
        A  B  C  D E F
    Q.  q1 q2 q3
    W.  w1 w2 w3
    B's Wage = q2/q1 * w1 = q2w1/q1 => Two components of wage. Quality[i] * BASE WAGE/BASE QUALITY
    => For each BASE, traverse and compute min k-1 quality[i]. (problem: If that quality[i] has a higher minimum wage, should traverse more until we fill k-1 workers) => Worst case O(N^2)

    Should FIX BASE and compute top K-1. How to do this efficiently?
    If we sort by Quality / Wage?
    When 1 is base: q2w1/q1 >= w2, w1/q1 >= w2/q2
    IF w1/q1 >= w[i]/q[i], we can include! => BASE should have higher ratio!
    Wihtin this ordering, we should choose lowest q[i] so that we can make lowest q[i]*w1/q1 = money we have to pay for i'th worker.
    [. < . < . < . . . . .]
    Thus, sort by w[i]/q[i].
    For (1 ... n):
        Set i_th as a base.

    Previous Wage Sum = w[i] + w[i]/q[i]*(q[j_1] + q[j_(k-1)]) = w[i]/q[i]*(q[i] + q[j_1] + q[j_(k-1)])
    (PrevWageSum - w[i]) * q[i]/w[i] => previous smallest quality sum
    */
    struct Info
    {
        int quality;
        int wage;
        int idx;
    };
    double mincostToHireWorkers(vector<int> &quality, vector<int> &wage, int k)
    {
        vector<Info> workers;
        for (int i = 0; i < quality.size(); i++)
        {
            workers.push_back({quality[i], wage[i], i});
        }
        auto ratioComp = [](const Info &a, const Info &b)
        {
            double ar = a.wage / (double)a.quality;
            double br = b.wage / (double)b.quality;
            if (ar < br)
                return true;
            else if (ar == br)
                return a.idx > b.idx;
            return false;
        };

        sort(workers.begin(), workers.end(), ratioComp);
        priority_queue<int, vector<int>, less<int>> pq; // maxHeap
        int qualitySum = 0;
        // k workers using k-1_th worker as a base
        double baseRatio = (double)workers[k - 1].wage / (double)workers[k - 1].quality;
        for (int i = 0; i < k; i++)
        {
            pq.push(workers[i].quality);
            // cout << workers[i].quality << " " << workers[i].wage << " "<< (double)workers[i].wage/workers[i].quality << endl;
            qualitySum += workers[i].quality;
        }
        double ans = (double)qualitySum * baseRatio;
        for (int i = k; i < workers.size(); i++)
        {
            int curBiggestQuality = pq.top();
            pq.pop();
            pq.push(workers[i].quality);
            qualitySum = qualitySum - curBiggestQuality + workers[i].quality;
            baseRatio = (double)workers[i].wage / (double)workers[i].quality;
            ans = min(ans, (double)qualitySum * baseRatio);
        }

        return ans;
    }
};