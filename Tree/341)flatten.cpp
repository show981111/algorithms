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

/**
 * hasNext() doesn't change the result even tho it is applied multiple times.
 */

class NestedIterator
{
public:
    typedef vector<NestedInteger>::iterator NestIterator;
    struct Range
    {
        NestIterator cur;
        NestIterator end;
        // Since we don't have an access to original array, cant tell if it is an end.
    };
    vector<Range> iters;
    int cur; // If there is a get current operation, we can just return this.
    NestedIterator(vector<NestedInteger> &nestedList)
    {
        iters.push_back({nestedList.begin(), nestedList.end()});
    }

    int next()
    {
        getInt();
        cur = iters.back().cur->getInteger();
        forwardIter();
        return cur;
    }

    bool hasNext()
    {
        return getInt();
    }

    // Get the integer of current iters state.
    // Return true if we can get an integer, false if not
    bool getInt()
    {
        while (!iters.empty())
        {
            if (iters.back().cur == iters.back().end)
            {
                iters.pop_back();
                if (!iters.empty())
                    iters.back().cur++;
            }
            else
            {
                if (iters.back().cur->isInteger())
                    return true;
                auto &l = iters.back().cur->getList();
                iters.push_back({l.begin(), l.end()});
            }
        }
        if (!iters.empty())
            return true;
        return false;
    }

    // Forward iters state.
    void forwardIter()
    {
        getInt();
        while (!iters.empty())
        {
            iters.back().cur++;
            while (!iters.empty() && iters.back().cur == iters.back().end)
            {
                iters.pop_back();
                if (!iters.empty())
                    iters.back().cur++;
            }
            if (!iters.empty())
                getInt();
            // cout << "FOrwarded. Current Int is at " <<
            return;
        }
    }
};
