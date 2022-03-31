#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "structures.h"
#include "neuralNetwork.h"
#include "mcts.h"

using namespace std;

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
        map<char, vector<double>> symbolMask{
            {' ', {0.01,0.01,0.01,0.01}},
            {'0', {0.01,0.01,0.01,0.99}},
            {'1', {0.01,0.01,0.99,0.01}},
            {'2', {0.01,0.01,0.99,0.99}},
            {'3', {0.01,0.99,0.01,0.01}},
            {'4', {0.01,0.99,0.01,0.99}},
            {'5', {0.01,0.99,0.99,0.01}},
            {'6', {0.01,0.99,0.99,0.99}},
            {'7', {0.99,0.01,0.01,0.01}},
            {'8', {0.99,0.01,0.01,0.99}},
            {'9', {0.99,0.01,0.99,0.01}},
            {'a', {0.99,0.01,0.99,0.99}},
            {'b', {0.99,0.99,0.99,0.99}}
        };

        bool isVirtual;
        bool updateTrainingData = true;

        chess();
        chess(char** start_pos);
        chess(char** start_pos, properties prop, bool virt);

        ~chess();

        void clear();
        void replay();
        void fillTrainingData();
        void setUpdateTrainingData(bool ch);
        vector<coords> getFigs(string reg);
        string getStringWhitePos();
        string getStringBlackPos();
        bool containsFig(string reg, coords v);
        void printPos();
        void printSteps();
        void printPos(vector<vector<char>> p);
        vector<double> toArray();
        size_t toHash();
        size_t toHash(step st);
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
        GameStatus getStatus();
        string statusToString();
        bool doStep(step st);
        step selectBestStep(neuralNetwork &AI);
        bool isValidStep(step st);
        void simulate(neuralNetwork &AI, size_t parent);
        step doStepAI(neuralNetwork &AI, bool update = false, bool train = true);
        void trainAI(neuralNetwork& AI, size_t node, vector<vector<double>> &data, bool isWhite);
};
#endif