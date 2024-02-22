class Solution
{
public:
    /*
    Two heaps O(NlogN). Worst case O(NM)
    1. When we assign meetings to the room, should be ordered in start_time, so that we can put earlier meeting first
        => Sort meetings based on start time
    2. In the case of no available rooms, should find "earliest" available room and assign the meeting to that room
        => need an ordered container, end_time ascending order
    3. If multiple rooms available at the same time -> Assign "smallest" Id room.
        => need an ordered container, room_id ascending order
    */
    struct Room
    {
        int room = -1;
        unsigned long end = 0;
    };
    struct History
    {
        int cnt = 0;
        unsigned long end = 0;
    };
    int mostBooked(int n, vector<vector<int>> &meetings)
    {
        sort(meetings.begin(), meetings.end(), [](vector<int> &a, vector<int> &b)
             { return a[0] < b[0]; });
        vector<History> rooms(n);
        int r = 0, rCount = 0;

        auto comp = [](const Room &a, const Room &b)
        {
            if (a.end < b.end)
                return true;
            else if (a.end == b.end)
                return a.room < b.room;
            return false;
        };

        priority_queue<int, vector<int>, greater<int>> freeRooms; // rooms that are available at that time
        set<Room, decltype(comp)> st(comp);                       // min heap for end time & tie break with roomId
        for (int i = 0; i < n; i++)
        {
            freeRooms.push(i);
        }
        for (auto &meeting : meetings)
        {
            int assignTo = -1;
            unsigned long startTime = meeting[0];
            unsigned long duration = meeting[1] - meeting[0];

            // based on current meeting start time, update freeRooms
            while (!st.empty() && st.begin()->end <= meeting[0])
            {
                int roomId = st.begin()->room;
                st.erase(st.begin());
                freeRooms.push(roomId);
            }

            if (!freeRooms.empty())
            {
                // no delay, will pop the smallest roomId
                assignTo = freeRooms.top();
                freeRooms.pop();
            }
            else
            {
                // Should delay the meeting
                Room t = *st.begin(); // earliest available room
                st.erase(st.begin());
                assignTo = t.room;
                startTime = t.end; // schedule earliest as possible
            }

            // assign and update end_time and counts.
            rooms[assignTo].end = startTime + duration;
            rooms[assignTo].cnt++;
            // update set
            st.insert(Room{assignTo, rooms[assignTo].end});

            // Update the answer
            if (rCount < rooms[assignTo].cnt)
            {
                r = assignTo;
                rCount = rooms[assignTo].cnt;
            }
            else if (rCount == rooms[assignTo].cnt)
            {
                r = min(r, assignTo);
            }
        }

        return r;
    }
};

/*
Brute-force O(NM)

1. manually iterate rooms, get the earliest one or avilable room
*/
class Solution
{
public:
    struct Room
    {
        int room = -1;
        unsigned long end = 0;
    };
    struct History
    {
        int cnt = 0;
        unsigned long end = 0;
    };
    int mostBooked(int n, vector<vector<int>> &meetings)
    {
        sort(meetings.begin(), meetings.end(), [](vector<int> &a, vector<int> &b)
             { return a[0] < b[0]; });
        vector<History> rooms(n);
        int r = 0, rCount = 0;

        for (auto &meeting : meetings)
        {
            int assignTo = -1;
            unsigned long startTime = meeting[0];
            unsigned long duration = meeting[1] - meeting[0];
            int earliestAvailableRoom = 0;
            int earliestStartTime = rooms[0].end;
            for (int i = 0; i < n; i++)
            {
                if (rooms[i].end <= meeting[0])
                {
                    // doesn't have to delay the meeting. Assign to the lowest room_id
                    assignTo = i;
                    break;
                }
                else
                {
                    if (earliestStartTime > rooms[i].end)
                    {
                        earliestStartTime = rooms[i].end;
                        earliestAvailableRoom = i;
                    }
                }
            }
            // Need to delay. Assign meeting to the earliest available one.
            if (assignTo == -1)
            {
                assignTo = earliestAvailableRoom;
                startTime = earliestStartTime;
            }
            rooms[assignTo].cnt++;
            rooms[assignTo].end = startTime + duration;

            // Update the answer
            if (rCount < rooms[assignTo].cnt)
            {
                r = assignTo;
                rCount = rooms[assignTo].cnt;
            }
            else if (rCount == rooms[assignTo].cnt)
            {
                r = min(r, assignTo);
            }
        }

        return r;
    }
};
