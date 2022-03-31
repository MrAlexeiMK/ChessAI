#include "mcts.h"
#include "logManager.h"
#include "settingsManager.h"
#include <fstream>

void mcts::init(string fileName) {
	srand((unsigned int)time(NULL));
	g.clear();
	this->fileName = fileName;
	ifstream in(settingsManager::getInstance().path + fileName);
	if (!in.good()) {
		in.open("mcts.txt");
	}
	size_t hash, parent;
	nodeInfo info;
	step st;
	while (in.peek() != EOF) {
		in >> hash >> parent >> info.visits >> info.wins >> st.from.column >> st.from.row >> st.to.column >> st.to.row;
		if (parent != 1) {
			g[parent].childs.push_back(hash);
			g[hash].parent = parent;
		}
		else g[hash].parent = 1;
		g[hash].st = st;
		g[hash].info = info;
	}
	in.close();
}

void mcts::clear(size_t root) {
	if (g[root].info.depth > settingsManager::getInstance().maxDepth) return;
	for (size_t ch : g[root].childs) {
		g[ch].info.depth = g[root].info.depth + 1;
		clear(ch);
	}
}

void mcts::add(size_t parent, size_t node, step st) {
	if (!g.count(node)) {
		g[parent].childs.push_back(node);
		g[node].parent = parent;
		g[node].st = st;
	}
}

size_t mcts::select(size_t hash) {
	if (!g.count(hash)) return 1;
	if (g[hash].childs.empty()) return 1;
	double maxx = 0;
	size_t selected = 0;
	for (size_t to : g[hash].childs) {
		double k = ucb(to);
		if (k > maxx) {
			maxx = k;
			selected = to;
		}
	}
	return selected;
}

void mcts::update(size_t node, bool win) {
	while (true) {
		g[node].info.visits++;
		if (win) g[node].info.wins++;
		win = !win;
		node = g[node].parent;
		if (node == 1) break;
	}
}

double mcts::ucb(size_t hash) {
	nodeInfo info = g[hash].info;
	return (double)info.wins / (info.visits + eps) 
		+ C * sqrt(std::log(g[g[hash].parent].info.visits - info.visits + 1) / (info.visits + eps)) 
		+ ((double)rand()/RAND_MAX)*eps;
}

void mcts::save() {
	clear();
	ofstream out(settingsManager::getInstance().path + fileName);
	for (auto it = g.begin(); it != g.end(); ++it) {
		size_t hash = it->first;
		node n = it->second;
		if (n.st.from.column == 0 && n.st.from.row == 0 && n.st.to.column == 0 && n.st.to.row == 0) continue;
		if (hash != 0 && g[hash].info.depth == 0) continue;
		out << hash << " " << n.parent << " " << n.info.visits << " " << n.info.wins << " " <<
			n.st.from.column << " " << n.st.from.row << " " << n.st.to.column << " " << n.st.to.row << endl;
	}
	out.close();
}

void mcts::log() {
	for (auto it = g.begin(); it != g.end(); ++it) {
		size_t hash = it->first;
		node n = it->second;
		logManager::writeln(vector<uint64_t> { hash, n.parent, (uint64_t)n.info.visits, (uint64_t)n.info.wins });
		for (size_t to : g[hash].childs) {
			logManager::writeln(make_pair(hash, to));
		}
	}
}