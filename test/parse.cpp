#include <iostream>
#include <fstream>
#include <sstream>

#include "parse.h"

void parse(std::string &data_text, std::vector<VIntInt> &res)
{
    replace(data_text.begin(), data_text.end(), ',', ' ');
    stringstream ss1(data_text), ss2;
    string v, a;
    while (getline(ss1, v))
    {
        getline(ss1, a);
        res.push_back({vector<int32_t>{}, stoi(a)});
        ss2.clear();
        v = v.substr(1, v.length() - 2);
        ss2 << v;
        while (ss2 >> v)
            get<0>(res.back()).push_back(stoi(v));
    }
}

void parse(std::string &data_text, std::vector<VStrIntInt> &res)
{
    replace(data_text.begin(), data_text.end(), ',', ' ');
    replace(data_text.begin(), data_text.end(), '"', ' ');
    stringstream ss1(data_text), ss2;
    string v, i, a;
    while (getline(ss1, v))
    {
        getline(ss1, i);
        getline(ss1, a);
        res.push_back({vector<string>{}, stoi(i), stoi(a)});
        ss2.clear();
        v = v.substr(1, v.length() - 2);
        ss2 << v;
        while (ss2 >> v)
            get<0>(res.back()).push_back(v);
    }
}

void parse(std::string &data_text, std::vector<VIntIntInt> &res)
{
    replace(data_text.begin(), data_text.end(), ',', ' ');
    stringstream ss1(data_text), ss2;
    string v, i, a;
    while (getline(ss1, v))
    {
        getline(ss1, i);
        getline(ss1, a);
        res.push_back({vector<int32_t>{}, stoi(i), stoi(a)});
        ss2.clear();
        v = v.substr(1, v.length() - 2);
        ss2 << v;
        while (ss2 >> v)
            get<0>(res.back()).push_back(stoi(v));
    }
}

void parse(std::string &data_text, std::vector<VVIntInt> &res)
{
    replace(data_text.begin(), data_text.end(), ',', ' ');
    stringstream ss1(data_text), ss2;
    string v, a;
    while (getline(ss1, v))
    {
        getline(ss1, a);
        res.push_back({vector<vector<int32_t>>{}, stoi(a)});
        ss2.clear();
        v = v.substr(1, v.length() - 2);
        ss2 << v;
        while (ss2 >> v)
        {
            auto &temp = get<0>(res.back());
            if (v == "[]")
            {
                temp.push_back({});
            }
            else if (v[0] == '[')
            {
                temp.push_back({});
                temp.back().push_back(stoi(v.substr(1)));
            }
            else
                temp.back().push_back(stoi(v));
        }
    }
}

void parse(std::string &data_text, std::vector<StrStrBool> &res)
{
    stringstream ss(data_text);
    string s1, s2, a;
    while (getline(ss, s1))
    {
        getline(ss, s2);
        getline(ss, a);
        res.push_back({s1, s2, a == "true" ? true : false});
    }
}

void parse(std::string &data_text, std::vector<IntVVIntInt> &res)
{
    replace(data_text.begin(), data_text.end(), ',', ' ');
    stringstream ss1(data_text), ss2;
    string i, v, a;
    while (getline(ss1, i))
    {
        getline(ss1, v);
        getline(ss1, a);
        res.push_back({stoi(i), vector<vector<int32_t>>{}, stoi(a)});
        ss2.clear();
        v = v.substr(1, v.length() - 2);
        ss2 << v;
        while (ss2 >> v)
        {
            auto &temp = get<1>(res.back());
            if (v == "[]")
            {
                temp.push_back({});
            }
            else if (v[0] == '[')
            {
                temp.push_back({});
                temp.back().push_back(stoi(v.substr(1)));
            }
            else
                temp.back().push_back(stoi(v));
        }
    }
}

std::string readtxt(std::string path)
{
    ifstream file(path);
    if (!file.is_open())
    {
        cout << "Open file failed.";
        return 0;
    }
    vector<string> lines;
    string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();

    stringstream ss;
    for (auto &line : lines)
    {
        ss << line << "\n";
    }
    return ss.str();
}