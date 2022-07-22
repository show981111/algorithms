class Solution {
public:
    void dfs(vector<vector<char>>& grid, int row, int col){
        if(row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() || grid[row][col] != '1')
            return;
        grid[row][col] = '2';
        
        dfs(grid,row+1,col);
        dfs(grid,row-1,col);
        dfs(grid,row,col+1);
        dfs(grid,row,col-1);
    }
    int numIslands(vector<vector<char>>& grid) {
        int rowSize = grid.size();
        int colSize = grid[0].size();
        int count = 0;
        for(int i = 0; i < rowSize; i++){
            for(int j = 0; j < colSize; j++){
                if(grid[i][j] == '1'){
                    dfs(grid,i,j);
                    count++;
                }
            }
        }
        return count;
    }
};