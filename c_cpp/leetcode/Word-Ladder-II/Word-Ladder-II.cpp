#include <stdio.h>
#include <vector>
#include <unordered_set>
#include <string>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>

using namespace std;

/*
 * Run status: Accepted
 * Program Runtime:
 * 	small data: 8ms
 *	large data: 556ms 
 */
class Solution {
	vector<vector<string> > res;
	void dfs(unordered_map<string, vector<string> > &traces, 
			 vector<string> &path, string end) {
		vector<string> &pres = traces[end];
		if (pres.size() == 0) {
			path.push_back(end);
			vector<string> curPath = path;
			res.push_back(curPath);
			path.pop_back();
			return;
		}

		path.push_back(end);
		for (int i = 0; i < pres.size(); i++) {
			dfs(traces, path, pres[i]);
		}
		path.pop_back();
	}
public:
	vector<vector<string> > findLadders(string start, string end, 
									    unordered_set<string> &dict) {
		res.clear();
		if (start == end) {
			res.push_back(vector<string>(1, start));
			return res;
		}

		// swap start and end
		string tmp = start;
		start = end;
		end = tmp;

		dict.insert(start);
		dict.insert(end);
		unordered_map<string, vector<string> > traces;
		vector<string> prev;
		for (string s : dict) {
			traces[s] = prev; 
		}

		int cur = 0;
		int pre = 1;
		vector<unordered_set<string> > v(2);
		v[cur].insert(start);
		dict.erase(start);

		while (true) {
			for (unordered_set<string>::const_iterator itr = v[cur].begin(); 
				 itr != v[cur].end(); itr++) {
				string st = *itr;
				for (int i = 0; i < st.length(); i++) {
					char ch = st[i];
					for (char j = 'a'; j <= 'z'; j++) {
						if (j == ch)
							continue;
						st[i] = j;
						if (dict.find(st) != dict.end()) {
							traces[st].push_back(*itr);
							v[pre].insert(st);
						}
					}
					st[i] = ch;
				}
			}
			if (v[pre].size() == 0) {
				return res;
			}
			if (v[pre].count(end)) {
				break;
			}

			v[cur].clear();
			for (unordered_set<string>::const_iterator itr = v[pre].begin(); 
				 itr != v[pre].end(); itr++) {
				dict.erase(*itr);
			}
			cur = !cur;
			pre = !pre;
		}

		vector<string> path;
		dfs(traces, path, end);

		return res;
	}
};

void dumpRes(vector<vector<string> > res) {
	for (int i = 0; i < res.size(); i++) {
		for(int j = 0; j < res[i].size(); j++) {
			printf("%s ", res[i][j].data());
		}
		printf("\n");
	}
}

int main() {
	int n;
	Solution solution;
	
	while (true) {
		if (scanf("%d", &n) == - 1) {
			break;
		}

		vector<string> data(n);
		for (int i = 0; i < n; i++) {
			cin >> data[i];
		}
		
		unordered_set<string> dict;
		for(int i = 2; i < n; i++) {
			dict.insert(data[i]);
		}
		vector<vector<string> > res = solution.findLadders(data[0], data[1], 
													       dict);
		dumpRes(res);
	}
	return 0;
}
