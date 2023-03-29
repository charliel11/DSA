#include "parse.h"

void parse(std::string& data_text, std::vector<VecAns>& res)
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

void parse(std::string& data_text, std::vector<VecIntAns>& res)
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

void parse(std::string& data_text, std::vector<Vec2Ans>& res)
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
            auto& temp = get<0>(res.back());
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