#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
 * Run Status: Accepted
 * Program Runtime:
 * 	small data: 8ms 
 *	large data: 88ms
 */
class Solution {
public:
	int longestConsecutive(vector<int> &num) {
		unordered_set<int> nodup;
		int len = num.size();
		for (int i = 0; i < len; i++) {
			nodup.insert(num[i]);
		}

		unordered_map<int, int> start;
		unordered_map<int, int> end;
		for (int n : nodup) {
			bool foundStart = (start.find(n + 1) != start.end());
			bool foundEnd = (end.find(n - 1) != end.end());
			if (foundStart && foundEnd) {
				int endLen = end[n - 1];
				int startLen = start[n + 1];
				start.erase(n + 1);
				end.erase(n - 1);
				start[n - endLen] = endLen + startLen + 1;
				end[n + startLen] = endLen + startLen + 1;
			} else if (foundStart) {
				start[n] = start[n + 1] + 1;
				end[n + start[n + 1]]++;
				start.erase(n + 1);
			} else if (foundEnd) {
				end[n] = end[n - 1] + 1;
				start[n - end[n - 1]]++;
				end.erase(n - 1);	
			} else {
				start[n] = 1;
				end[n] = 1;
			}
		}
		
		int res = -1;
		for (auto& x : start) {
			if (x.second > res)
				res = x.second;
		}
		return res;
	}
};

int main() {
	Solution solution;
	int n;
	while (scanf("%d", &n) != -1) {
		vector<int> num(n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &num[i]);
		}
		int res = solution.longestConsecutive(num);
		printf("%d\n", res);
	}
	return 0;
}
