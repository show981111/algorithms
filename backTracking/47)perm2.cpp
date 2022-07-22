//Just sorting and skipping does not work!
// ex) [0|,0,1,9] => [9,0(A)|,1,0(B)] => [9,0,1|,0] => [9,0,1,0|] (PUSHED)
//                              => [9,0,0|,1] => [9,0,0,1|] (PUSHED)
//                => [9,1|,0(A),0(B)] => [9,1,0|,0] => [9,1,0,0|] (PUSHED)
//                => [9,0(B)|,1,0(A)] => [9,0,1|,0] => [9,0,1,0|] (PUSHED) - REDUNDANT!   
// ex2) [0,1,2,0|,-1(A),1,-1(B)] => [0,1,2,-1(A),0,1,-1(B)] .... 
//                               => [0,1,2,-1(B),-1(A),1,0] ....    
//                                     CREATE REDUNDANCY by being swapped with same elem
// Key point is not swapping the same pair again!
// ex) swap 0(curIndex) <-> 1(A) then 0(curIndex) <-> 1(B) again!
//      Redundant :(
class Solution {
public: 
    void genPerms(vector<vector<int>> &ans, vector<int> &path, int curIndex){
        if(curIndex == path.size()){
            ans.push_back(path);
            return;
        }
        unordered_set<int> st;
        for(int i = curIndex; i < path.size(); i++){
            if(st.find(path[i]) != st.end())
                continue;
            st.insert(path[i]);
            swap(path[curIndex], path[i]);
            genPerms(ans,path,curIndex+1);
            swap(path[curIndex], path[i]);
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ans;
        genPerms(ans, nums,0);
        return ans;
    }
};