#ifndef __PARSE_H__
#define __PARSE_H__

#include <algorithm>
#include <tuple>

using namespace std;

using VecAns = tuple<vector<int32_t>, int32_t>; 
using VecIntAns = tuple<vector<int32_t>, int64_t, int32_t>; // {inputs, answer}

void parse(std::string& data_text, std::vector<VecAns>& res)
{
    replace(data_text.begin(), data_text.end(), ',', ' ');
    stringstream ss1(data_text), ss2;
    string s;
    string a;
    while (getline(ss1, s))
    {
        getline(ss1, a);
        res.push_back({vector<int>{}, stoi(a)});
        ss2.clear();
        s = s.substr(1, s.length() - 2);
        ss2 << s;
        while (ss2 >> s)
            get<0>(res.back()).push_back(stoi(s));
    }
}

#endif