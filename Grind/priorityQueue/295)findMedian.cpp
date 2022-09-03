/**
 * @brief How can we track two elements in the middle??
 * => we have to divide sorted array into two parts
 * from Bottom, and from the top...
 * Since we need to maintain the sorted order and do not need to traverse
 * all elements, We can use Priority Queue!
 * We need two queues
 * one is a maxheap from the first middle (of ascending sorted arr)
 * one is a minheap from the the second middle (of ascending sorted arr)
 *
 *
 * addNum (logn)
 * findMedian (1)
 */

class MedianFinder
{
public:
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        if (small.empty() || small.top() > num)
        {
            small.push(num);
        }
        else
        { // small is not empty and small.top <= num
            big.push(num);
        }
        int S = small.size();
        int B = big.size();
        if ((S - B) > 1 || (S - B) < -1)
        {
            if (S > B)
            {
                big.push(small.top());
                small.pop();
            }
            else
            {
                small.push(big.top());
                big.pop();
            }
        }
    }

    double findMedian()
    {
        if (small.size() != big.size())
        {
            if (small.size() > big.size())
            {
                return small.top();
            }
            else
                return big.top();
        }
        else
        {
            double d = ((double)small.top() + (double)big.top()) / 2;
            return d;
        }
    }

    priority_queue<int, vector<int>, std::less<int>> small; // maxheap
    priority_queue<int, vector<int>, std::greater<int>> big;
};