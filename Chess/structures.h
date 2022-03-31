#ifndef STRUCTURES_H
#define STRUCTURES_H

#define eps 1e-3

enum GameType {
	SINGLE,
	AI,
	TRAIN
};

enum GameStatus {
    GAME,
    WHITE,
    BLACK,
    DRAW
};

class coords {
public:
    int row;
    int column;
    bool operator== (const coords& other);
    bool operator!= (const coords& other);
};

class step {
public:
    coords from;
    coords to;
    bool operator== (const step& other);
};

struct nodeInfo {
    long long wins = 0;
    long long visits = 0;
    int depth = 0;
};

struct node {
    std::vector<size_t> childs;
    size_t parent;
    step st;
    nodeInfo info;
};

const char defaultPos[8][8] = {
        {'1','2','3','4','5','3','2','1'},
        {'0','0','0','0','0','0','0','0'},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {'6','6','6','6','6','6','6','6'},
        {'7','8','9','a','b','9','8','7'}
};

struct properties {
    int stepCounter;
    bool white_king;
    bool white_rook_right;
    bool white_rook_left;
    bool black_king;
    bool black_rook_right;
    bool black_rook_left;
    coords white_king_coords;
    coords black_king_coords;
    bool isWhite;
    std::vector<step> history;
    bool isChecked;
    int count_check_figs;
    int repeat;
};

#endif