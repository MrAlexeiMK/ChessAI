#ifndef NEURAL_H
#define NEURAL_H

#include <string>
#include <vector>
#include "matrix.h"

using namespace std;

class neuralNetwork {
    public:
        vector<int> layers;
        double lr;
        int len;
        vector<matrix> W;

        neuralNetwork(vector<int> layers, double lr);

        double activation_function(double x);
        matrix activation_function(matrix x);
        void train(vector<double> input_list, vector<double> targets_list);
        vector<double> query(vector<double> input_list);
        void train_from_csv(string path, char parser, double max_num, int epohs, bool vis);
        void test_from_csv(string path, char parser, double max_num, bool vis);
        void saveW(string path);
        void loadW(string path);
        void clearW();
};

#endif