// https://leetcode-cn.com/problems/number-of-valid-move-combinations-on-chessboard/
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    enum ChessKind {
        Rook,
        Queen,
        Bishop
    };
    struct Move {
        int x;
        int y;
        int moves;
        int dx;
        int dy;
    };
    struct Chess {
        int x;
        int y;
        ChessKind kind;
        vector<Move> possible_moves;
        Move cur_move;
    };
    int rook_dir[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};
    int queen_dir[8][2] = {{-1,0},{-1,-1},{-1,1},{0,1},{0,-1},{1,1},{1,0},{1,-1}};
    int bishop_dir[4][2] = {{-1,1},{-1,-1},{1,-1},{1,1}};
    vector<Chess> all_chess;
    int n;
    int ans;
    
    void dfs(int depth) {
        if (depth < n) {
            Chess &chess = all_chess[depth];
            for (int i = 0;i < chess.possible_moves.size();i++) {
                chess.cur_move = chess.possible_moves[i];
                dfs(depth+1);
            }
        } else {
            // check ans
            bool valid = true;
            for (int i = 0;i < n && valid;i++) {
                for (int j = i + 1;j < n && valid;j++) {
                    int max_moves = max(all_chess[i].cur_move.moves, all_chess[j].cur_move.moves);
                    for (int k = 0;k <= max_moves;k++) {
                        int x1 = all_chess[i].x + all_chess[i].cur_move.dx * min(all_chess[i].cur_move.moves, k);
                        int y1 = all_chess[i].y + all_chess[i].cur_move.dy * min(all_chess[i].cur_move.moves, k);
                        int x2 = all_chess[j].x + all_chess[j].cur_move.dx * min(all_chess[j].cur_move.moves, k);
                        int y2 = all_chess[j].y + all_chess[j].cur_move.dy * min(all_chess[j].cur_move.moves, k);
                        if (x1 == x2 && y1 == y2) {
                            valid = false;
                            break;
                        }
                    }
                }
            }
            if (valid) {
                ans ++;
            }
        }
        return;
    }
    
    int countCombinations(vector<string>& pieces, vector<vector<int>>& positions) {
        n = pieces.size();
        ans = 0;
        for (int i = 0;i < n;i++) {
            Chess c;
            c.x = positions[i][0];
            c.y = positions[i][1];
            
            Move m;
            m.x = c.x;
            m.y = c.y;
            m.moves = 0;
            m.dx = m.dy = 0;
            c.possible_moves.push_back(m);
            
            int (*dir)[2] = NULL;
            int dir_size = 0;
            if (pieces[i] == "rook") {
                c.kind = ChessKind::Rook;
                dir = rook_dir;
                dir_size = 4;
            } else if (pieces[i] == "queen") {
                c.kind = ChessKind::Queen;
                dir = queen_dir;
                dir_size = 8;
            } else {
                c.kind = ChessKind::Bishop;
                dir = bishop_dir;
                dir_size = 4;
            }
            
            for (int j = 0;j < dir_size;j++) {
                int dx = dir[j][0];
                int dy = dir[j][1];
                for (int k = 1;;k++) {
                    Move m;
                    m.x = c.x + dx*k;
                    m.y = c.y + dy*k;
                    if (m.x <= 0 || m.y <= 0 || m.x >= 9 || m.y >= 9) {
                        break;
                    }
                    m.moves = k;
                    m.dx = dx;
                    m.dy = dy;
                    c.possible_moves.push_back(m);
                }
            }
            all_chess.push_back(c);
        }
        dfs(0);
        
        return ans;
    }
};