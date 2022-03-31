#include "chess.h"
#include "settingsManager.h"
#include "logManager.h"
#include <time.h>
#include <functional>

void merge(vector<pair<pair<double, step>, vector<double>>>& arr, int l, int m, int r, bool reverse = false) {
    vector<pair<pair<double, step>, vector<double>>> temp;
    int i = l;
    int j = m + 1;
    int k = l;
    while (k <= r) {
        if ((i <= m && (j > r || ((!reverse && arr[i].first.first < arr[j].first.first) || (reverse && arr[i].first.first > arr[j].first.first))))) {
            temp.push_back(arr[i]);
            ++i;
        }
        else if (j <= r) {
            temp.push_back(arr[j]);
            ++j;
        }
        ++k;
    }
    for (size_t i = 0; i < temp.size(); ++i) arr[l + i] = temp[i];
}

void merge_sort(vector<pair<pair<double, step>, vector<double>>>& arr, int l, int r, bool reverse = false) {
    if (l >= r) {
        return;
    }
    merge_sort(arr, l, (r + l) / 2, reverse);
    merge_sort(arr, (r + l) / 2 + 1, r, reverse);
    merge(arr, l, (r + l) / 2, r, reverse);
}

chess::chess() {
    srand((unsigned int)time(NULL));
    pos = new char*[8];
    for (int i = 0; i < 8; ++i) {
        pos[i] = new char[8];
        for (int j = 0; j < 8; ++j) {
            pos[i][j] = defaultPos[i][j];
        }
    }
    coords king1 = {7, 4}, king2 = {0, 4};
    vector<step> st;
    isVirtual = false;
    prop = {0, false, false, false, false, false, false, king1, king2, true, st, false, 0, 0};
    fillTrainingData();
    updateFigs();
    updateSteps();
}

chess::chess(char** start_pos) {
    srand((unsigned int)time(NULL));
    pos = new char* [8];
    for (int i = 0; i < 8; ++i) {
        pos[i] = new char[8];
        for (int j = 0; j < 8; ++j) {
            pos[i][j] = start_pos[i][j];
        }
    }
    coords king1 = {7, 4}, king2 = {0, 4};
    vector<step> st;
    isVirtual = false;
    prop = {0, false, false, false, false, false, false, king1, king2, true, st, false, 0, 0};
    fillTrainingData();
    updateFigs();
    updateSteps();
}

chess::chess(char** start_pos, properties props, bool virt = false) {
    pos = new char* [8];
    for (int i = 0; i < 8; ++i) {
        pos[i] = new char[8];
        for (int j = 0; j < 8; ++j) {
            pos[i][j] = start_pos[i][j];
        }
    }
    isVirtual = virt;
    prop = props;
    if (!isVirtual) {
        srand((unsigned int)time(NULL));
        updateFigs();
        updateSteps();
        fillTrainingData();
    }
}

chess::~chess() {
    clear();
}

void chess::clear() {
    for (int i = 0; i < 8; ++i) {
        delete[] pos[i];
    }
    delete[] pos;
}

void chess::fillTrainingData() {
    for (int i = 0; i < settingsManager::getInstance().historySteps; ++i) {
        training_data.push_back(toArray());
    }
}

void chess::setUpdateTrainingData(bool ch) {
    updateTrainingData = ch;
}

void chess::replay() {
    pos = new char* [8];
    for (int i = 0; i < 8; ++i) {
        pos[i] = new char[8];
        for (int j = 0; j < 8; ++j) {
            pos[i][j] = defaultPos[i][j];
        }
    }
    coords king1 = { 7, 4 }, king2 = { 0, 4 };
    vector<step> st;
    isVirtual = false;
    prop = {0, false, false, false, false, false, false, king1, king2, true, st, false, 0, 0 };
    training_data.clear();
    fillTrainingData();
    updateFigs();
    updateSteps();
}

void chess::printPos() {
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            cout << pos[i][j] << " ";
        }
        cout << endl;
    }
}

void chess::printPos(vector<vector<char>> p) {
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            cout << p[i][j] << " ";
        }
        cout << endl;
    }
}

void chess::printSteps() {
    cout << current_steps.size() << endl;
    for (step st : current_steps) {
        cout << st.from.row << " " << st.from.column << " -> " << st.to.row << " " << st.to.column << endl;
    }
}

string chess::getStringWhitePos() {
    string res = "";
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            res += pos[i][j];
        }
    }
    return res;
}

string chess::getStringBlackPos() {
    string res = "";
    for (int i = 7; i >= 0; --i) {
        for (int j = 7; j >= 0; --j) {
            res += pos[i][j];
        }
    }
    return res;
}

bool chess::containsFig(string reg, coords v) {
    for (char c : reg) {
        if (pos[v.row][v.column] == c) return true;
    }

    return false;
}

vector<coords> chess::getFigs(string reg) {
    vector<coords> res;
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            if(reg.find(pos[i][j]) != string::npos) {
                res.push_back({i, j});
            }
        }
    }
    return res;
}

size_t chess::toHash() {
    hash<string> hasher;
    string s = "";
    for (step st : prop.history) {
        s += to_string(st.from.column) + to_string(st.from.row) + to_string(st.to.column) + to_string(st.to.row);
    }
    return s == "" ? 0 : hasher(s);
}

size_t chess::toHash(step st) {
    hash<string> hasher;
    string s = "";
    for (step st : prop.history) {
        s += to_string(st.from.column) + to_string(st.from.row) + to_string(st.to.column) + to_string(st.to.row);
    }
    s += to_string(st.from.column) + to_string(st.from.row) + to_string(st.to.column) + to_string(st.to.row);
    return hasher(s);
}

vector<double> chess::toArray() {
    vector<double> res;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            for (double d : symbolMask[pos[i][j]]) {
                res.push_back(d);
            }
        }
    }
    return res;
}

bool chess::isWhite(coords v) {
    string reg = "6789ab";
    if(reg.find(pos[v.row][v.column]) != string::npos) {
        return true;
    }
    return false;
}

bool chess::isBlack(coords v) {
    string reg = "012345";
    if(reg.find(pos[v.row][v.column]) != string::npos) {
        return true;
    }
    return false;
}

bool chess::isDiff(coords v1, coords v2) {
    return (isWhite(v1) && isBlack(v2)) || (isWhite(v2) && isBlack(v1));
}

bool chess::isEqualColor(coords v1, coords v2) {
    return (isWhite(v1) && isWhite(v2)) || (isBlack(v1) && isBlack(v2));
}

bool chess::isDiff(step st) {
    return (isWhite(st.from) && isBlack(st.to)) || (isWhite(st.to) && isBlack(st.from));
}

void chess::updateFigs() {
    current_figs.clear();
    opposite_figs.clear();
    if (prop.isWhite) current_figs.push_back(prop.white_king_coords);
    else current_figs.push_back(prop.black_king_coords);
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            coords v = {i, j};
            if (current_figs[0] == v) continue;
            if ((prop.isWhite && isWhite(v)) || (!prop.isWhite && isBlack(v))) current_figs.push_back(v);
            else if ((!prop.isWhite && isWhite(v)) || (prop.isWhite && isBlack(v))) opposite_figs.push_back(v);
        }
    }
}

bool chess::possibleStep(step st, bool onlyAttackFields = false) {
    if(st.to.row < 0 || st.to.row > 7 || st.to.column < 0 || st.to.column > 7) return false;
    if(st.from.row < 0 || st.from.row > 7 || st.from.column < 0 || st.from.column > 7) return false;
    if (onlyAttackFields) return true;
    char fig_from = pos[st.from.row][st.from.column];
    char fig_to = pos[st.to.row][st.to.column];
    //log << st.from.row << " " << st.from.column << " -> " << st.to.row << " " << st.to.column << " : " << endl;
    if (prop.isChecked && fig_from != '5' && fig_from != 'b') {
        if (!isCheckField[st.to.row][st.to.column] || prop.count_check_figs > 1) return false;
    }
    //log << "1" << endl;
    coords vec = { 0, 0 };
    if (ways[st.from.row][st.from.column] != vec) {
        vec = ways[st.from.row][st.from.column];
        if (vec.row == 0) {
            if (st.from.row != st.to.row) return false;
        }
        else if (vec.column == 0) {
            if (st.from.column != st.to.column) return false;
        }
        else {
            int i = (st.to.row - st.from.row) / vec.row;
            if (st.to.column != st.from.column + i * vec.column) return false;
        }
    }
    step last = {{-1, -1}, {-1, -1}};
    if(!prop.history.empty()) {
        last = prop.history[prop.history.size()-1];
    }
    if(fig_from == '6') {
        if(st.from.column == st.to.column) {
            if(abs(st.to.row - st.from.row) == 1 && fig_to == ' ') return true;
            if(abs(st.to.row - st.from.row) == 2 && st.from.row == 6 && pos[st.to.row+1][st.to.column] == ' ' && fig_to == ' ') return true;
        }
        else if(abs(st.to.row - st.from.row) == 1 && abs(st.to.column - st.from.column) == 1 && fig_to == ' ' && pos[st.to.row+1][st.to.column] == '0' && last.to.row == st.to.row+1 && last.to.column == st.to.column && last.from.row == st.to.row-1 && st.to.column == last.from.column) return true;
        else if(isDiff(st)) return true;
        return false;
    }

    else if(fig_from == '0') {
        if(st.from.column == st.to.column) {
            if(abs(st.to.row - st.from.row) == 1 && fig_to == ' ') return true;
            if(abs(st.to.row - st.from.row) == 2 && st.from.row == 1 && pos[st.to.row-1][st.to.column] == ' ' && fig_to == ' ') return true;
        }
        else if(abs(st.to.row - st.from.row) == 1 && abs(st.to.column - st.from.column) == 1 && fig_to == ' ' && pos[st.to.row-1][st.to.column] == '6' && last.to.row == st.to.row-1 && last.to.column == st.to.column && last.from.row == st.to.row+1 && last.from.column == st.to.column) return true;
        else if(isDiff(st)) return true;
        return false;
    }

    else if(fig_from == 'b' && abs(st.from.column-st.to.column) >= 2) {
        if(!prop.white_rook_right && st.to.column-st.from.column == 2 && st.to.column-1 >= 0 && st.to.column + 1 < 8 && pos[st.to.row][st.to.column+1] == '7' && pos[st.to.row][st.to.column-1] == ' ' && fig_to == ' ') {
            if(isOppositeField[st.to.row][st.to.column-1]) return false;
            if(isOppositeField[st.to.row][st.to.column]) return false;
            return true;
        }
        else if(!prop.white_rook_left && st.from.column-st.to.column == 2 && st.from.column-4 >= 0 && pos[st.from.row][st.from.column-4] == '7' && pos[st.from.row][st.from.column-3] == ' ' && pos[st.from.row][st.from.column-2] == ' ' && pos[st.from.row][st.from.column-1] == ' ' && fig_to == ' ') {
            if (isOppositeField[st.from.row][st.from.column-2]) return false;
            if (isOppositeField[st.from.row][st.from.column-1]) return false;
            return true;
        }
        return false;
    }

    else if(fig_from == '5' && abs(st.from.column-st.to.column) >= 2) {
        if(!prop.black_rook_right && st.to.column-st.from.column == 2 && st.to.column-1 >= 0 && st.to.column + 1 < 8 && pos[st.to.row][st.to.column+1] == '1' && pos[st.to.row][st.to.column-1] == ' ' && fig_to == ' ') {
            if (isOppositeField[st.to.row][st.to.column-1]) return false;
            if (isOppositeField[st.to.row][st.to.column]) return false;
            return true;
        }
        else if (!prop.black_rook_left && st.from.column - st.to.column == 2 && st.from.column - 4 >= 0 && pos[st.from.row][st.from.column - 4] == '1' && pos[st.from.row][st.from.column - 3] == ' ' && pos[st.from.row][st.from.column - 2] == ' ' && pos[st.from.row][st.from.column - 1] == ' ' && fig_to == ' ') {
            if (isOppositeField[st.from.row][st.from.column - 2]) return false;
            if (isOppositeField[st.from.row][st.from.column - 1]) return false;
            return true;
        }
        return false;
    }

    if(fig_to == ' ' || isDiff(st)) {
        if (fig_from == '5' || fig_from == 'b') {
            if (isOppositeField[st.to.row][st.to.column]) return false;
        }
        return true;
    }
    return false;
}

vector<step> chess::getStepsByFig(coords cur, bool onlyAttackFields = false) {
    vector<step> steps;

    char fig = pos[cur.row][cur.column];

    if(fig == '6' || fig == '0') {
        int ind = -1;
        if(fig == '0') ind = 1;
        if (!onlyAttackFields) {
            if (possibleStep({ cur, {cur.row + ind, cur.column} })) {
                steps.push_back({ cur, {cur.row + ind, cur.column} });
            }
            if (possibleStep({ cur, {cur.row + 2 * ind, cur.column} })) {
                steps.push_back({ cur, {cur.row + 2 * ind, cur.column} });
            }
        }
        if(possibleStep({cur, {cur.row+ind, cur.column+1}}, onlyAttackFields)) {
            steps.push_back({cur, {cur.row+ind, cur.column+1}});
            if (onlyAttackFields && isDiff({ cur, {cur.row + ind, cur.column + 1} })) {
                if (containsFig("5b", { cur.row + ind, cur.column + 1 })) {
                    isCheckField[cur.row][cur.column] = true;
                    prop.count_check_figs += 1;
                }
            }
        }
        if(possibleStep({cur, {cur.row+ind, cur.column-1}}, onlyAttackFields)) {
            steps.push_back({cur, {cur.row+ind, cur.column-1}});
            if (onlyAttackFields && isDiff({ cur, {cur.row + ind, cur.column - 1} })) {
                if (containsFig("5b", { cur.row + ind, cur.column - 1 })) {
                    isCheckField[cur.row][cur.column] = true;
                    prop.count_check_figs += 1;
                }
            }
        }
    }
    else if(fig == '1' || fig == '7' || fig == '3' || fig == '9' || fig == '4' || fig == 'a') {
        vector<coords> inds;
        if(fig == '1' || fig == '7') {
            vector<coords> temp {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
            inds = temp;
        }
        else if(fig == '3' || fig == '9') {
            vector<coords> temp {{1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
            inds = temp;
        }
        else {
            vector<coords> temp {{1, 1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}};
            inds = temp;
        }
        for(coords v : inds) {
            int a = v.row, b = v.column;
            while(true) {
                if (cur.row + a < 0 || cur.row + a > 7 || cur.column + b < 0 || cur.column + b > 7) break;
                bool can = possibleStep({ cur, {cur.row + a, cur.column + b} }, onlyAttackFields);
                if (isCheck()) {
                    if (can) {
                        steps.push_back({ cur, {cur.row + a, cur.column + b} });
                    }
                    else if (pos[cur.row + a][cur.column + b] != ' ') break;
                }
                else if (!can) {
                    break;
                }
                else {
                    steps.push_back({ cur, {cur.row + a, cur.column + b} });
                }
                if (isDiff({ cur, {cur.row + a, cur.column + b} })) {
                    bool king = false;
                    if (onlyAttackFields && containsFig("5b", { cur.row + a, cur.column + b })) {
                        king = true;
                        int c = a;
                        int d = b;
                        while (true) {
                            if (c == v.row && d == v.column) break;
                            c -= v.row;
                            d -= v.column;
                            isCheckField[cur.row+c][cur.column+d] = true;
                        }
                        isCheckField[cur.row][cur.column] = true;
                        prop.count_check_figs += 1;
                    }
                    if(!king) break;
                }
                if (onlyAttackFields && isEqualColor(cur, {cur.row+a, cur.column+b})) break;
                a+=v.row;
                b+=v.column;
            }
        }
    }
    else if(fig == '2' || fig == '8') {
        vector<coords> inds {{-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {-2, -1}, {-2, 1}, {2, -1}, {2, 1}};
        for(coords v : inds) {
            if(possibleStep({cur, {cur.row+v.row, cur.column+v.column}}, onlyAttackFields)) {
                steps.push_back({cur, {cur.row+v.row, cur.column+v.column}});
                if (onlyAttackFields && isDiff({ cur, {cur.row + v.row, cur.column + v.column} })) {
                    if (containsFig("5b", { cur.row + v.row, cur.column + v.column })) {
                        isCheckField[cur.row][cur.column] = true;
                        prop.count_check_figs += 1;
                    }
                }
            }
        }
    }
    else if(fig == '5' || fig == 'b') {
        vector<coords> inds {{1, 1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        for(coords v : inds) {
            if(possibleStep({cur, {cur.row+v.row, cur.column+v.column}}, onlyAttackFields)) {
                steps.push_back({cur, {cur.row+v.row, cur.column+v.column}});
            }
        }
        if (!onlyAttackFields) {
            if (!prop.isChecked) {
                if ((fig == '5' && !prop.black_king) || (fig == 'b' && !prop.white_king)) {
                    if (possibleStep({ cur, {cur.row, cur.column + 2} })) {
                        steps.push_back({ cur, {cur.row, cur.column + 2} });
                    }
                    if (possibleStep({ cur, {cur.row, cur.column - 2} })) {
                        steps.push_back({ cur, {cur.row, cur.column - 2} });
                    }
                }
            }

            for (coords v : inds) {
                int a = v.row, b = v.column;
                coords empty = { -1, -1 };
                coords found_fig = empty;
                bool ch = false;
                while (true) {
                    coords to = { cur.row + a, cur.column + b };
                    if (to.row < 0 || to.row > 7 || to.column < 0 || to.column > 7) break;
                    if (isEqualColor(cur, to)) {
                        if (found_fig != empty) break;
                        found_fig = to;
                    }
                    else if (isDiff(cur, to)) {
                        if (found_fig == empty) break;
                        if (abs(v.row) + abs(v.column) == 1) {
                            if (containsFig("a417", to)) {
                                ch = true;
                            }
                        }
                        else {
                            if (containsFig("a439", to)) {
                                ch = true;
                            }
                        }
                        break;
                    }
                    a += v.row; b += v.column;
                }
                if (ch && found_fig != empty) {
                    ways[found_fig.row][found_fig.column] = v;
                }
            }
        }
    }
    return steps;
}

void chess::updateSteps() {
    current_steps.clear();
    opposite_steps.clear();
    current_fields.clear();
    opposite_fields.clear();
    isOppositeField.assign(8, vector<char>(8, false));
    isCheckField.assign(8, vector<char>(8, false));
    ways.assign(8, vector<coords>(8, {0, 0}));
    prop.isChecked = false;
    prop.count_check_figs = 0;
    map<pair<int, int>, char> used;

    for (coords v : opposite_figs) {
        vector<step> got_steps = getStepsByFig(v, true);
        for (step st : got_steps) {
            opposite_steps.push_back(st);
        }
    }
    prop.isChecked = (prop.count_check_figs > 0);
    for (step st : opposite_steps) {
        if (!used[make_pair(st.to.row, st.to.column)]) {
            opposite_fields.push_back(st.to);
            isOppositeField[st.to.row][st.to.column] = true;
            used[make_pair(st.to.row, st.to.column)] = true;
        }
    }
    used.clear();

    for (coords v : current_figs) {
        vector<step> got_steps = getStepsByFig(v, false);
        for (step st : got_steps) {
            current_steps.push_back(st);
        }
    }
    for (step st : current_steps) {
        if (!used[make_pair(st.to.row, st.to.column)]) {
            current_fields.push_back(st.to);
            used[make_pair(st.to.row, st.to.column)] = true;
        }
    }

}

bool chess::isCheck() {
    if (prop.isChecked) return true;
    return false;
}

bool chess::isMate() {
    if (isCheck()) {
        if (current_steps.empty()) return true;
    }
    return false;
}

bool chess::isDraw() {
    if (!isCheck()) {
        if (current_steps.empty()) return true;
    }
    return false;
}

GameStatus chess::getStatus() {
    if (isDraw() || prop.repeat >= 6 || prop.stepCounter > settingsManager::getInstance().maxSteps || (current_figs.size() == 1 && opposite_figs.size() == 1)) {
        current_steps.clear();
        return GameStatus::DRAW;
    }
    if (isMate()) {
        if (prop.isWhite) return GameStatus::BLACK;
        return GameStatus::WHITE;
    }
    return GameStatus::GAME;
}

string chess::statusToString() {
    GameStatus status = getStatus();
    if (status == GameStatus::WHITE) return "white";
    else if (status == GameStatus::BLACK) return "black";
    else if (status == GameStatus::DRAW) return "draw";
    else return "game";
}

bool chess::isValidStep(step st) {
    for (step cur : current_steps) {
        if (cur == st) {
            return true;
        }
    }
    return false;
}

bool chess::doStep(step st) {
    if(isVirtual || isValidStep(st)) {
        coords fr = st.from;
        coords to = st.to;
        char temp1 = pos[fr.row][fr.column];
        char temp2 = pos[to.row][to.column];
        pos[fr.row][fr.column] = ' ';
        pos[to.row][to.column] = temp1;

        if(temp1 == '0' || temp1 == '6') {
            if(to.row == 0 || to.row == 7) {
                if(temp1 == '6') pos[to.row][to.column] = 'a';
                else pos[to.row][to.column] = '4';
            }
            else if(abs(to.row-fr.row) == 1 && abs(to.column-fr.column) == 1 && temp2 == ' ') {
                if(temp1 == '6') pos[to.row+1][to.column] = ' ';
                else pos[to.row-1][to.column] = ' ';
            }
        }
        else if(temp1 == 'b') {
            if (!prop.white_king) {
                if (to.column - fr.column == 2) {
                    char temp3 = pos[to.row][to.column + 1];
                    pos[to.row][to.column + 1] = ' ';
                    pos[to.row][to.column - 1] = temp3;
                }
                else if (fr.column - to.column == 2) {
                    char temp3 = pos[fr.row][fr.column - 4];
                    pos[fr.row][fr.column - 4] = ' ';
                    pos[to.row][to.column + 1] = temp3;
                }
            }
            prop.white_king = true;
            prop.white_king_coords.row = to.row;
            prop.white_king_coords.column = to.column;
        }
        else if(temp1 == '5') {
            if (!prop.black_king) {
                if (to.column - fr.column == 2) {
                    char temp3 = pos[to.row][to.column + 1];
                    pos[to.row][to.column + 1] = ' ';
                    pos[to.row][to.column - 1] = temp3;
                }
                else if (fr.column - to.column == 2) {
                    char temp3 = pos[fr.row][fr.column - 4];
                    pos[fr.row][fr.column - 4] = ' ';
                    pos[to.row][to.column + 1] = temp3;
                }
            }
            prop.black_king = true;
            prop.black_king_coords.row = to.row;
            prop.black_king_coords.column = to.column;
        }
        else if(temp1 == '7') {
            if(fr.row == 7 && fr.column == 0 && !prop.white_rook_left) {
                prop.white_rook_left = true;
            }
            else if(fr.row == 7 && fr.column == 7 && !prop.white_rook_right) {
                prop.white_rook_right = true;
            }
        }
        else if(temp1 == '1') {
            if(fr.row == 0 && fr.column == 0 && !prop.black_rook_left) {
                prop.black_rook_left = true;
            }
            else if(fr.row == 0 && fr.column == 7 && !prop.black_rook_right) {
                prop.black_rook_right = true;
            }
        }
        prop.stepCounter++;
        prop.isWhite = !prop.isWhite;
        prop.history.push_back(st);
        updateFigs();
        if (!isVirtual) {
            if (prop.history.size() > 3) {
                if (st == prop.history[prop.history.size() - 4]) {
                    prop.repeat++;
                }
                else prop.repeat = 0;
            }
            updateSteps();
            if (updateTrainingData) {
                training_data.push_back(toArray());
                training_data.erase(training_data.begin());
            }
        }
        return true;
    }
    return false;
}

step chess::selectBestStep(neuralNetwork &AI) {
    double maxQ = 0;
    step res{};
    for (step st : current_steps) {
        chess virt_game(pos, prop, true);
        virt_game.doStep(st);
        vector<double> inputs;
        for (size_t i = 1; i < training_data.size(); ++i) {
            inputs.insert(inputs.end(), training_data[i].begin(), training_data[i].end());
        }
        vector<double> last = virt_game.toArray();
        inputs.insert(inputs.end(), last.begin(), last.end());
        vector<double> outputs = AI.query(inputs);
        double Q = outputs[0];
        if (!prop.isWhite) Q = 1 - Q;
        if (Q > maxQ) {
            maxQ = Q;
            res = st;
        }
    }
    if (maxQ == 0) throw exception("step not found");
    return res;
}

void chess::simulate(neuralNetwork& AI, size_t parent) {
    mcts& tree = mcts::getInstance();
    if (current_steps.empty()) return;
    for (step st : current_steps) {
        size_t hash = toHash(st);
        tree.add(parent, hash, st);
    }
    for (int i = 0; i < settingsManager::getInstance().simulations; ++i) {
        int r = rand()%tree.g[parent].childs.size();
        size_t child = tree.g[parent].childs[r];
        step st = tree.g[child].st;
        chess game(pos, prop);
        game.doStep(st);
        bool isWhite = game.prop.isWhite;
        vector<vector<double>> data(game.training_data);
        game.setUpdateTrainingData(false);

        int depth = 0;
        while (game.getStatus() == GameStatus::GAME && depth < settingsManager::getInstance().depth) {
            game.doStep(game.selectBestStep(AI));
            ++depth;
        }

        if (game.getStatus() == GameStatus::WHITE || game.getStatus() == GameStatus::BLACK) {
            GameStatus status = game.getStatus();
            bool win = ((status == GameStatus::WHITE && isWhite) ||
                (status == GameStatus::BLACK && !isWhite));
            tree.update(child, win);
            trainAI(AI, child, data, isWhite);
        }
    }
}

void chess::trainAI(neuralNetwork& AI, size_t node, vector<vector<double>> &data, bool isWhite) {
    nodeInfo info = mcts::getInstance().g[node].info;
    if (info.visits > 0) {
        double K = (double)info.wins / (info.visits + eps);
        if (!isWhite) K = 1 - K;
        vector<double> train;
        for (vector<double> v : data) {
            train.insert(train.end(), v.begin(), v.end());
        }
        AI.train(train, vector<double>{K});
    }
}

step chess::doStepAI(neuralNetwork &AI, bool updateTree, bool train) {
    mcts& tree = mcts::getInstance();
    size_t hash = toHash();
    size_t next = tree.select(hash);
    if(train) trainAI(AI, hash, training_data, prop.isWhite);
    if (updateTree) {
        if (next == 1) {
            simulate(AI, hash);
            next = tree.select(hash);
        }
        if (next != 1) {
            step st = tree.g[next].st;
            doStep(st);
            return st;
        }
    }
    else {
        step st = selectBestStep(AI);
        doStep(st);
        return st;
    }
    throw exception("step not found");
    return {};
}

bool coords::operator== (const coords& other) {
    return (row == other.row && column == other.column);
}

bool coords::operator!= (const coords& other) {
    return (row != other.row || column != other.column);
}

bool step::operator== (const step& other) {
    return (from == other.from && to == other.to);
}