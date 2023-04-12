#pragma once

#include <deque>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

namespace st {
namespace pattern_matching {
/*
https://leetcode.com/problems/simplify-path/description/

"/home/../foo/" => /foo
*/
string simplifyPath(string path) {
    size_t n = path.size();
    deque<string> st;
    string name;
    name.reserve(n);

    for (size_t i = 1; i < n; i++) {
        if (path[i] == '/')
            continue;

        while (i < n && path[i] != '/') {
            name.push_back(path[i]);
            ++i;
        }

        if (name.size() > 0) {
            if (name == "..") {
                if (!st.empty())
                    st.pop_back();
            } else if (name != ".")
                st.emplace_back(name);
            name.clear();
        }
    }

    name.clear();
    while (!st.empty()) {
        name.push_back('/');
        name += st.front();
        st.pop_front();
    }
    return name.empty() ? "/" : name;
}

/*
https://leetcode.com/problems/removing-stars-from-a-string/description/
*/
string removeStars(string s) {
    string res;
    res.reserve(s.size());
    for (char &c : s) {
        if (c != '*') {
            res.push_back(c);
        } else {
            res.pop_back();
        }
    }
    return res;
}

/*
https://leetcode.com/problems/valid-parentheses/description/
*/
bool isValid(string s) {
    unordered_map<char, char> brackets = {{'{', '}'}, {'[', ']'}, {'(', ')'}};
    stack<char> stack;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '{' || s[i] == '[' || s[i] == '(')
            stack.push(s[i]);
        else {
            if (stack.empty())
                return false;
            else if (brackets[stack.top()] != s[i])
                return false;
            else
                stack.pop();
        }
    }
    return stack.empty();
}

} // namespace pattern_matching
} // namespace st