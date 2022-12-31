class NestedIterator
{
public:
    vector<NestedInteger> items;
    vector<int> linear;
    int index;
    NestedIterator(vector<NestedInteger> &nestedList)
    {
        items = nestedList;
        helper(items, 0, linear);
        index = 0;
    }

    int next()
    {
        return linear[index++];
    }

    bool hasNext()
    {
        if (index < linear.size())
            return true;
        return false;
    }

    void helper(vector<NestedInteger> &items, int itemIndex, vector<int> &linear)
    {
        if (items.size() <= itemIndex)
            return;
        if (items[itemIndex].isInteger())
        {
            int curVal = items[itemIndex].getInteger();
            linear.push_back(curVal);
            // we found the integer
        }
        else
        {
            // if its list, start from 0 of that list
            helper(items[itemIndex].getList(), 0, linear);
        }
        // at this point, we finished filling previous elements

        helper(items, itemIndex + 1, linear);
        // go to next valid integer
    }
};

/**
 * @brief
 *
 */

class NestedIterator
{
public:
    typedef vector<NestedInteger>::iterator NestIter;
    stack<pair<NestIter, NestIter>> iters;
    NestedIterator(vector<NestedInteger> &nestedList)
    {
        iters.push({nestedList.begin(), nestedList.end()});
    }

    int next()
    {
        isNextValid(); // find the integer value
        int v = iters.top().first->getInteger();
        iters.top().first++;
        return v;
    }

    bool hasNext()
    {
        return isNextValid();
    }
    // go deep until we find the valid integer value
    bool isNextValid()
    {
        while (!iters.empty())
        {
            if (iters.top().first == iters.top().second)
            { // if it is empty, pop and go to next
                iters.pop();
            }
            else
            {
                auto t = iters.top();
                // if its int, return true
                if (t.first->isInteger())
                    return true;
                // if its list, push that list!!
                // important... when we push the nested List,
                // we should !!forward the cursor!!, so that when we come back,
                // we should start from the next one.
                iters.top().first++;
                iters.push({t.first->getList().begin(), t.first->getList().end()});
            }
        }
        return false;
    }
};
