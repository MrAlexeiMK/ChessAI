#include "chess.h"
#include <bitset>
#include <time.h>
#include <algorithm>

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
    for (int i = 0; i < temp.size(); ++i) arr[l + i] = temp[i];
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
    srand(time(NULL));
    pos = new char*[8];
    for (int i = 0; i < 8; ++i) {
        pos[i] = new char[8];
        for (int j = 0; j < 8; ++j) {
            pos[i][j] = defaultPos[i][j];
        }
    }
    coords king1 = {7, 4}, king2 = {0, 4};
    vector<step> st;
    MAX_STEPS = 1000;
    isVirtual = false;
    prop = {false, false, false, false, false, false, king1, king2, true, st, false, 0, 0};
    updateFigs();
    updateSteps();
}

chess::chess(int max_steps) {
    srand(time(NULL));
    pos = new char* [8];
    for (int i = 0; i < 8; ++i) {
        pos[i] = new char[8];
        for (int j = 0; j < 8; ++j) {
            pos[i][j] = defaultPos[i][j];
        }
    }
    coords king1 = { 7, 4 }, king2 = { 0, 4 };
    vector<step> st;
    MAX_STEPS = max_steps;
    isVirtual = false;
    prop = { false, false, false, false, false, false, king1, king2, true, st, false, 0, 0 };
    updateFigs();
    updateSteps();
}

chess::chess(char** start_pos) {
    srand(time(NULL));
    pos = new char* [8];
    for (int i = 0; i < 8; ++i) {
        pos[i] = new char[8];
        for (int j = 0; j < 8; ++j) {
            pos[i][j] = start_pos[i][j];
        }
    }
    coords king1 = {7, 4}, king2 = {0, 4};
    vector<step> st;
    MAX_STEPS = 1000;
    isVirtual = false;
    prop = {false, false, false, false, false, false, king1, king2, true, st, false, 0, 0};
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
    MAX_STEPS = 1000;
    if (!isVirtual) {
        srand(time(NULL));
        updateFigs();
        updateSteps();
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

void chess::setMaxSteps(int max_steps) {
    MAX_STEPS = max_steps;
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
    prop = { false, false, false, false, false, false, king1, king2, true, st, false, 0, 0 };
    training_data.clear();
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

vector<double> chess::toArray() {
    vector<double> res(82 * 7, 0.01);
    string reg = "012346789a";
    int len = reg.size();
    string temp;
    int num = 0;
    for (int i = 0; i < len; ++i) {
        num = 8 * 7 * i;
        vector<coords> c = getFigs(string(1, reg[i]));
        for (coords v : c) {
            temp = bitset< 7 >(8 * v.row + v.column + 1).to_string();
            for (char c : temp) {
                if (c == '0') res[num] = 0.01;
                else res[num] = 0.99;
                ++num;
            }
        }
    }
    num = 80 * 7;
    for (coords v : getFigs("b")) {
        temp = bitset< 7 >(8 * v.row + v.column + 1).to_string();
        for (char c : temp) {
            if (c == '0') res[num] = 0.01;
            else res[num] = 0.99;
            ++num;
        }
    }
    for (coords v : getFigs("5")) {
        temp = bitset< 7 >(8 * v.row + v.column + 1).to_string();
        for (char c : temp) {
            if (c == '0') res[num] = 0.01;
            else res[num] = 0.99;
            ++num;
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

string chess::getStatus() {
    if (prop.repeat >= 6 || training_data.size() > MAX_STEPS || (current_figs.size() == 1 && opposite_figs.size() == 1)) {
        current_steps.clear();
        return "draw";
    }
    if (isDraw()) return "draw";
    if (isMate()) {
        if (prop.isWhite) return "black";
        return "white";
    }
    return "ingame";
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

        prop.isWhite = !prop.isWhite;
        updateFigs();
        if (!isVirtual) {
            if (prop.history.size() > 3) {
                if (st == prop.history[prop.history.size() - 4]) {
                    prop.repeat++;
                }
                else prop.repeat = 0;
            }
            prop.history.push_back(st);
            updateSteps();
            training_data.push_back(toArray());
        }

        return true;
    }
    return false;
}

step chess::notationToSteps(string nt) {
    map<char, int> conv; map<char, string> conv2;
    conv['a'] = 0; conv['b'] = 1; conv['c'] = 2; conv['d'] = 3; conv['e'] = 4; conv['f'] = 5; conv['g'] = 6; conv['h'] = 7;
    conv2['K'] = "5b"; conv2['Q'] = "4a"; conv2['N'] = "28"; conv2['R'] = "17"; conv2['B'] = "39";
    coords nul = { -1, -1 };
    coords from = nul, to = nul;
    string target = "";
    if (nt == "O-O" || nt == "O-O-O") {
        target = "5b";
    }
    else if (nt.size() == 2) {
        to = {8-(nt[1]-'0'), conv[nt[0]]};
    }
    else if (nt.size() == 3) {
        target += nt[0];
        to = { 8 - (nt[2] - '0'), conv[nt[1]] };
    }
    else if (nt.size() == 4) {

    }
    for (step st : current_steps) {
        if (containsFig(target, st.from)) {

        }
    }
    return { from, to };
}

step chess::doStepAI(neuralNetwork &AI) {
    double eps = 0.15;
    vector<pair<pair<double, step>, vector<double>>> arr;
    for (step st : current_steps) {
        chess virt_game(pos, prop, true);
        virt_game.doStep(st);
        vector<double> inputs(virt_game.toArray());
        vector<double> outputs = AI.query(inputs);
        double Q = outputs[0];
        arr.push_back(make_pair(make_pair(Q, st), inputs));
    }
    if (!arr.empty()) {
        vector<pair<pair<double, step>, vector<double>>> best_steps;
        if (prop.isWhite) {
            merge_sort(arr, 0, arr.size() - 1, true);
        }
        else {
            merge_sort(arr, 0, arr.size() - 1, false);
        }
        for (auto p : arr) {
            if (abs(p.first.first - arr[0].first.first) > eps) break;
            best_steps.push_back(p);
        }
        int i = rand() % best_steps.size();
        doStep(best_steps[i].first.second);
        return best_steps[i].first.second;
    }
}

void chess::trainAI(neuralNetwork& AI) {
    string status = getStatus();
    double K = 0.5;
    if (status == "white") {
        K = 0.99;
    }
    else if (status == "black") {
        K = 0.01;
    }
    for (int i = 0; i < training_data.size(); ++i) {
        AI.train(training_data[i], vector<double>{K});
    }
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