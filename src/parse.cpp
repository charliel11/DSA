#include <fstream>
#include <iostream>
#include <sstream>

#include <parse.h>

/*
[1,2,3,4,5,6]
*/
void read(string &text, vector<int32_t> &res) {
    stringstream ss;
    replace(text.begin(), text.end(), ',', ' ');
    text = text.substr(1, text.length() - 2);
    ss << text;
    while (ss >> text)
        res.push_back(stoi(text));
}

/*
[[1,2,3],[4,5,6]]
*/
void read(string &text, vector<vector<int32_t>> &res) {
    stringstream ss;
    replace(text.begin(), text.end(), ',', ' ');
    text = text.substr(1, text.length() - 2);
    ss << text;
    while (ss >> text) {
        auto &tmp = res;
        if (text == "[]") {
            tmp.push_back({});
        } else if (text[0] == '[') {
            tmp.push_back({});
            tmp.back().push_back(stoi(text.substr(1)));
        } else
            tmp.back().push_back(stoi(text));
    }
}

/*
["123", "345"]
*/
void read(string &text, vector<string> &res) {
    replace(text.begin(), text.end(), ',', ' ');
    replace(text.begin(), text.end(), '"', ' ');
    stringstream ss;
    text = text.substr(1, text.length() - 2);
    ss << text;
    while (ss >> text)
        res.push_back(text);
}

void read(string &text, int32_t &res) { res = stoi(text); }
void read(string &text, int64_t &res) { res = stoll(text); }
void read(string &text, string &res) { res = text; }
void read(string &text, bool &res) { res = text == "true" ? true : false; }

void parse(std::string &data_text, std::vector<VIntInt> &res) {
    stringstream ss(data_text);
    string v, a;
    while (getline(ss, v), getline(ss, a)) {
        res.push_back({vector<int32_t>{}, stoi(a)});
        read(v, get<0>(res.back()));
    }
}

void parse(std::string &data_text, std::vector<VStrIntInt> &res) {
    stringstream ss(data_text);
    string v, i, a;
    while (getline(ss, v) && getline(ss, i) && getline(ss, a)) {
        res.push_back({vector<string>{}, stoi(i), stoi(a)});
        read(v, get<0>(res.back()));
    }
}

void parse(std::string &data_text, std::vector<VIntIntInt> &res) {
    stringstream ss(data_text);
    string v, i, a;
    while (getline(ss, v) && getline(ss, i) && getline(ss, a)) {
        res.push_back({vector<int32_t>{}, stoi(i), stoi(a)});
        read(v, get<0>(res.back()));
    }
}

void parse(std::string &data_text, std::vector<VVIntInt> &res) {
    stringstream ss(data_text);
    string v, a;
    while (getline(ss, v) && getline(ss, a)) {
        res.push_back({vector<vector<int32_t>>{}, stoi(a)});
        read(v, get<0>(res.back()));
    }
}

void parse(std::string &data_text, std::vector<StrStrBool> &res) {
    stringstream ss(data_text);
    string s1, s2, a;
    while (getline(ss, s1) && getline(ss, s2) && getline(ss, a)) {
        res.push_back({s1, s2, a == "true" ? true : false});
    }
}

void parse(std::string &data_text, std::vector<StrInt> &res) {
    stringstream ss(data_text);
    string s, a;
    while (getline(ss, s) && getline(ss, a)) {
        if (s[0] == '"')
            res.push_back({s.substr(1, s.size() - 2), stoi(a)});
        else
            res.push_back({s, stoi(a)});
    }
}

void parse(std::string &data_text, std::vector<IntVVIntInt> &res) {
    stringstream ss(data_text);
    string i, v, a;
    while (getline(ss, i) && getline(ss, v) && getline(ss, a)) {
        res.push_back({stoi(i), vector<vector<int32_t>>{}, stoi(a)});
        read(v, get<1>(res.back()));
    }
}

void parse(std::string &data_text, std::vector<VIntVIntIntVInt> &res) {
    stringstream ss(data_text);
    string v1, v2, i, v3;
    while (getline(ss, v1) && getline(ss, v2) && getline(ss, i) && getline(ss, v3)) {
        res.push_back({vector<int32_t>{}, vector<int32_t>{}, stoll(i), vector<int32_t>{}});
        read(v1, get<0>(res.back()));
        read(v2, get<1>(res.back()));
        read(v3, get<3>(res.back()));
    }
}

void parse(std::string &data_text, std::vector<VIntVIntIntInt> &res) {
    stringstream ss(data_text);
    string v1, v2, i1, i2;
    while (getline(ss, v1) && getline(ss, v2) && getline(ss, i1) && getline(ss, i2)) {
        res.push_back({});
        read(v1, get<0>(res.back()));
        read(v2, get<1>(res.back()));
        read(i1, get<2>(res.back()));
        read(i2, get<3>(res.back()));
    }
}

std::string readtxt(std::string path) {
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Open file failed.";
        return 0;
    }
    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    stringstream ss;
    for (auto &line : lines) {
        ss << line << "\n";
    }
    return ss.str();
}