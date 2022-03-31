#ifndef MCTS_H
#define MCTS_H

#define C 1

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "structures.h"
#include "neuralNetwork.h"

using namespace std;

class mcts {
public:
	map<size_t, node> g;
	string fileName;

	static mcts& getInstance() {
		static mcts instance;
		return instance;
	}

	void add(size_t parent, size_t node, step st);
	void update(size_t node, bool win);
	size_t select(size_t hash);
	double ucb(size_t hash);
	void log();
	void init(string fileName);
	void clear(size_t root = 0);
	void save();
private:
	static mcts* instance;
	mcts() {}
	~mcts() {}

	mcts(mcts const&) = delete;
	mcts& operator=(mcts const&) = delete;
};

#endif