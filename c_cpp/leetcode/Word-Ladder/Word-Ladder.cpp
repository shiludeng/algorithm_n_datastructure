#include <stdio.h>
#include <vector>
#include <unordered_set>
#include <string>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

/*
 * Run status: Accepted
 * Program Runtime:
 * 	small data: 12ms
 *	large data:  620ms
 */
class Solution {
public:
	int ladderLength(string start, string end, unordered_set<string> &dict) {
		if (0 == start.compare(end))
			return 1;

		vector<unordered_set<string> > switches(2);
		int cur = 0, pre = 1;	
		switches[cur].insert(start);
		dict.insert(end);

		int distance = 1;
		while (true) {
			for (auto& x : switches[cur]) {
				string st = x;
				for (int i = 0; i < st.length(); i++) {
					char ch = st[i];
					for (char j = 'a'; j <= 'z'; j++) {
						if (j == ch)
							continue;
						st[i] = j;
						if (0 == st.compare(end)) {
							return distance + 1;
						}
						if (dict.find(st) != dict.end()) {
							dict.erase(st);
							switches[pre].insert(st);
						}
					}
					st[i] = ch;
				}
			}
			if (switches[pre].size() == 0)
				break;

			switches[cur].clear();
			distance++;
			cur = !cur;
			pre = !pre;
		}
		return 0;
	}
};

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
		int res = solution.ladderLength(data[0], data[1], dict);
		printf("%d\n", res);
	}
}
