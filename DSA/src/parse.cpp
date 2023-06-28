#include <DSA/Node.h>
#include <DSA/parse.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdint.h>
#include <string>

/*
[1,1,1,null,1,null,null,1,1,null,1]
*/
void parse_test_case(string &text, TreeNode *&res) {
  stringstream ss;
  text = text.substr(1, text.length() - 2);
  ss << text;

  queue<TreeNode *> q;
  ss >> text; // root
  res = new TreeNode(stoi(text));
  q.push(res);

  string left, right;
  while (ss >> left && ss >> right) {
    TreeNode *cur = q.front();
    q.pop();
    if (left != "null") {
      cur->left = new TreeNode(stoi(left));
      q.push(cur->left);
    }
    if (right != "null") {
      cur->right = new TreeNode(stoi(right));
      q.push(cur->right);
    }
  }
}

/*
[7,9,6,6,7,8,3,0,9,5]
*/
void parse_test_case(string &text, ListNode *&res) {
  vector<int32_t> tmp;
  parse_test_case(text, tmp);
  if (tmp.empty())
    return;
  res = new ListNode(tmp[0]);
  ListNode *cur = res;
  for (size_t i = 1; i < tmp.size(); ++i) {
    cur->next = new ListNode(tmp[i]);
    cur = cur->next;
  }
}

/*
[[1,2,3],[4,5,6]]
*/
void parse_test_case(string &text, vector<vector<int32_t>> &res) {
  stringstream ss;
  text = text.substr(1, text.length() - 2);
  ss << text;
  while (ss >> text) {
    auto &tmp = res;
    if (text == "[]" || text == "]") {
      // tmp.push_back({});
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
void parse_test_case(string &text, vector<string> &res) {
  stringstream ss;
  text = text.substr(1, text.length() - 2);
  ss << text;
  while (ss >> text)
    res.push_back(text);
}

void parse_test_case(string &text, string &res) {
  stringstream ss;
  ss << text;
  ss >> res;
}

void parse_test_case(string &text, bool &res) { res = text == "true" ? true : false; }

// [true, false]
void parse_test_case(string &text, vector<bool> &res) {
  stringstream ss;
  text = text.substr(1, text.length() - 2);
  ss << text;
  while (ss >> text)
    res.push_back(text == "true" ? true : false);
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
    replace(line.begin(), line.end(), ',', ' ');
    replace(line.begin(), line.end(), '"', ' ');
    if (line.back() == '\r') {
      line.pop_back();
    };
    lines.push_back(line);
  }
  file.close();

  stringstream ss;
  for (auto &line : lines) {
    ss << line << "\n";
  }
  return ss.str();
}
