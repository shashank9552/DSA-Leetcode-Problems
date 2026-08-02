class Solution {
public:
    bool row[9][10] = {};
    bool col[9][10] = {};
    bool box[9][10] = {};

    bool solve(vector<vector<char>>& board) {

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {

                if (board[i][j] != '.')
                    continue;

                int b = (i / 3) * 3 + (j / 3);

                for (int d = 1; d <= 9; d++) {

                    if (row[i][d] || col[j][d] || box[b][d])
                        continue;

                    board[i][j] = d + '0';
                    row[i][d] = col[j][d] = box[b][d] = true;

                    if (solve(board))
                        return true;

                    board[i][j] = '.';
                    row[i][d] = col[j][d] = box[b][d] = false;
                }

                return false;
            }
        }

        return true;
    }

    void solveSudoku(vector<vector<char>>& board) {

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {

                if (board[i][j] == '.')
                    continue;

                int d = board[i][j] - '0';
                int b = (i / 3) * 3 + (j / 3);

                row[i][d] = true;
                col[j][d] = true;
                box[b][d] = true;
            }
        }

        solve(board);
    }
};