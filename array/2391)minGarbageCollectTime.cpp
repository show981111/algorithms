class Solution
{
public:
    /*
    Since two other trucks can't do anything, each truck is totally independent.
    Sum of min time for each truck will be the global minimum.

    Key point is, when im traveling at i, you don't know if we should go further
    to collect the garbage since we dont have the information about last occurence of each garbage type.
    If we do 2-pass (record last garbage occurence per type + counting time)
    If we do 1-pass: Record trip time. If we collect at i_th house, we add trip time. Then reset triptime = 0.
    This way, we can delay adding the triptime until we actually encounter the garbage to collect.
    */
    int garbageCollection(vector<string> &garbage, vector<int> &travel)
    {
        int totalTime = 0;
        int pTripTime = 0, gTripTime = 0, mTripTime = 0;
        // trip time of each garbage type from last collected house.

        for (int i = 0; i < garbage.size(); i++)
        {
            // collect
            int pCnt = 0, gCnt = 0, mCnt = 0;
            for (char &g : garbage[i])
            {
                if (g == 'G')
                {
                    gCnt++;
                }
                else if (g == 'M')
                    mCnt++;
                else
                    pCnt++;
            }
            // record
            if (gCnt > 0)
            {
                totalTime += gCnt + gTripTime;
                gTripTime = 0; // reset to since we already added the trip time.
            }
            if (mCnt > 0)
            {
                totalTime += mCnt + mTripTime;
                mTripTime = 0;
            }
            if (pCnt > 0)
            {
                totalTime += pCnt + pTripTime;
                pTripTime = 0;
            }
            // move
            if (i != garbage.size() - 1)
            {
                gTripTime += travel[i];
                mTripTime += travel[i];
                pTripTime += travel[i];
            }
        }

        return totalTime;
    }
};