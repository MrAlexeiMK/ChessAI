#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "neuralNetwork.h"

using namespace std;

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

struct properties {
    bool white_king;
    bool white_rook_right;
    bool white_rook_left;
    bool black_king;
    bool black_rook_right;
    bool black_rook_left;
    coords white_king_coords;
    coords black_king_coords;
    bool isWhite;
    vector<step> history;
    bool isChecked;
    int count_check_figs;
    int repeat;
};

class chess {
    public:
        char** pos;
        properties prop;
        vector<coords> current_figs, opposite_figs;
        vector<step> current_steps, opposite_steps;
        vector<coords> current_fields, opposite_fields;
        vector<vector<char>> isOppositeField, isCheckField;
        vector<vector<coords>> ways;
        vector<vector<double>> training_data;
        bool isVirtual;
        int MAX_STEPS;

        chess();
        chess(int max_steps);
        chess(char** start_pos);
        chess(char** start_pos, properties prop, bool virt);

        ~chess();

        void clear();
        void replay();
        void setMaxSteps(int max_steps);
        vector<coords> getFigs(string reg);
        string getStringWhitePos();
        string getStringBlackPos();
        bool containsFig(string reg, coords v);
        void printPos();
        void printSteps();
        void printPos(vector<vector<char>> p);
        vector<double> toArray();
        bool isWhite(coords v);
        bool isBlack(coords v);
        bool isDiff(coords v1, coords v2);
        bool isEqualColor(coords v1, coords v2);
        bool isDiff(step st);
        void updateFigs();
        vector<step> getStepsByFig(coords cur, bool onlyAttackFields);
        bool isCheck();
        bool isMate();
        bool isDraw();
        bool possibleStep(step st, bool onlyAttackFields);
        void updateSteps();
        string getStatus();
        bool doStep(step st);
        bool isValidStep(step st);
        step doStepAI(neuralNetwork &AI);
        void trainAI(neuralNetwork &AI);
        step notationToSteps(string notation);
};
#endif