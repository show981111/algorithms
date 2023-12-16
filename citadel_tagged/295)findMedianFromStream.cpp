/**
 * Greater: > so descending -> MinHeap
 * Less: < so ascending -> MaxHeap
 *
 * Keep two heaps. One for smaller half(maxHeap), one for bigger half(minHeap)
 * Get median by take the biggest from smaller half and smallest from bigger half.
 * If the size is odd, just take one from the heap which has a bigger size.
 *
 * Rebalance the heap everytime we push the element.
 * If the size difference is more than 1, than move one elem from one to the other
 * to balance them!
 */

class MedianFinder
{
public:
    priority_queue<int, vector<int>, less<int>> maxHeap;    // smaller half
    priority_queue<int, vector<int>, greater<int>> minHeap; // bigger half
    MedianFinder()
    {
    }

    void rebalance()
    {
        if (maxHeap.size() >= minHeap.size() + 2)
        {
            // cout << maxHeap.top() << " ";
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if (maxHeap.size() + 2 <= minHeap.size())
        {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    void addNum(int num)
    {
        if (minHeap.empty() || minHeap.top() > num)
            maxHeap.push(num);
        else
            minHeap.push(num);
        rebalance();
    }

    double findMedian()
    {
        int totalSize = maxHeap.size() + minHeap.size();
        if (totalSize % 2 == 0)
        {
            return ((double)(minHeap.top() + maxHeap.top())) / 2;
        }
        else
        {
            return minHeap.size() > maxHeap.size() ? minHeap.top() : maxHeap.top();
        }
    }
};
