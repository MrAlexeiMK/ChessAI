using namespace std;

#include <string>
#include <fstream>
#include "math.h"
#include <sstream>
#include <algorithm>

#include "matrix.h"
#include "neuralNetwork.h"

neuralNetwork::neuralNetwork(vector<int> layers_, double lr_) {
    layers = layers_;
    len = layers_.size();
    lr = lr_;
    for(int i = 0; i < len-1; ++i) {
        W.push_back(matrix(layers[i+1], layers[i], -1/sqrt(layers[i + 1]), 1/sqrt(layers[i+1])));
    }
}

double neuralNetwork::activation_function(double x) {
    return (double)1/(1+exp(-x));
}

matrix neuralNetwork::activation_function(matrix x) {
    matrix temp(x.N, x.M);
    for(int i = 0; i < x.N; ++i) {
        for(int j = 0; j < x.M; ++j) {
            temp.data[i][j] = activation_function(x.data[i][j]);
        }
    }
    return temp;
}

void neuralNetwork::train(vector<double> input_list, vector<double> targets_list) {
    matrix targets(targets_list);
    matrix outputs(input_list);

    vector<matrix> outputs_array;
    outputs_array.push_back(outputs);
    for(int i = 0; i < len-1; ++i) {
        outputs = activation_function(W[i]*outputs);
        outputs_array.push_back(outputs);
    }
    matrix errors = targets-outputs;
    for(int i = len-2; i >= 0; --i) {
        matrix dif = (((errors * outputs_array[i + 1] * (-outputs_array[i + 1] + 1.0))) * outputs_array[i].transpose()) * lr;
        W[i] += dif;
        errors = W[i].transpose()*errors;
    }
}

vector<double> neuralNetwork::query(vector<double> inputs_list) {
    matrix inputs(inputs_list);
    matrix outputs = inputs;

    for(int i = 0; i < len-1; ++i) {
        outputs = activation_function(W[i]*outputs);
    }
    vector<double> res;
    for(int i = 0; i < outputs.N; ++i) {
        for(int j = 0; j < outputs.M; ++j) {
            res.push_back(outputs.data[i][j]);
        }
    }
    return res;
}

void neuralNetwork::train_from_csv(string path, char parser = ',', double max_num = 255.0, int epohs = 8, bool vis = true) {
    string line;
    ifstream train_data;
    train_data.open(path);

    vector<vector<double>> X_train;
    vector<vector<double>> Y_train;
    while(getline(train_data, line)) {
        replace(line.begin(), line.end(), parser, ' ');
        stringstream ss(line);
        vector<double> array, targets(layers[len-1], 0.01);
        double temp;
        ss >> temp;
        targets[(int)temp] = 0.99;
        Y_train.push_back(targets);
        while(ss >> temp) {
            array.push_back(temp);
        }
        for(int i = 0; i < array.size(); ++i) {
            array[i] = (double)((double)array[i]/max_num)*0.99 + 0.01;
        }
        X_train.push_back(array);
    }

    for(int e = 0; e < epohs; ++e) {
        for(int i = 0; i < X_train.size(); ++i) {
            if(vis) cout << 100*((double)(e*X_train.size() + (i+1))/(epohs*X_train.size())) << "%" << endl;
            train(X_train[i], Y_train[i]);
        }
    }
}

void neuralNetwork::test_from_csv(string path, char parser = ',', double max_num = 255.0, bool vis = false) {
    string line;
    ifstream test_data;
    test_data.open(path);
    int cor = 0, total = 0;
    while(getline(test_data, line)) {
        ++total;
        replace(line.begin(), line.end(), parser, ' ');
        stringstream ss(line);
        double temp;
        vector<double> inputs, outputs;
        int correct, label = 0;
        double max_number = 0;
        ss >> correct;
        while(ss >> temp) {
            inputs.push_back(temp);
        }
        for(int i = 0; i < inputs.size(); ++i) {
            inputs[i] = (double)((double)inputs[i]/max_num)*0.99 + 0.01;
        }
        outputs = query(inputs);
        for(int i = 0; i < outputs.size(); ++i) {
            if(outputs[i] > max_number) {
                max_number = outputs[i];
                label = i;
            }
        }
        if(vis) cout << label << " " << correct << endl;
        if(label == correct) ++cor;
    }
    cout << "Result: " << 100*(double)cor/total << "%" << endl;
}

void neuralNetwork::saveW(string path) {
    ofstream out(path);
    out << len << endl;
    for(int i = 0; i < len; ++i) {
        out << layers[i] << " ";
    }
    out << endl << endl;
    for(int i = 0; i < len-1; ++i) {
        out << W[i].N << " " << W[i].M << endl;
        out << W[i] << endl;
    }
    out.close();
}

void neuralNetwork::loadW(string path) {
    ifstream in(path);
    int newLen;
    in >> newLen;
    vector<int> new_layers(len);
    vector<matrix> new_W(len-1);
    for(int i = 0; i < len; ++i) {
        in >> new_layers[i];
        if(new_layers[i] == 0) throw std::invalid_argument("Invalid length");
    }
    if (layers == new_layers) {
        len = newLen;
        layers = new_layers;
        for (int i = 0; i < len - 1; ++i) {
            in >> new_W[i];
        }
        W = new_W;
    }
    in.close();
}

void neuralNetwork::clearW() {
    W.clear();
    for(int i = 0; i < len-1; ++i) {
        W.push_back(matrix(layers[i+1], layers[i], 0, 1/sqrt(layers[i+1])));
    }
}