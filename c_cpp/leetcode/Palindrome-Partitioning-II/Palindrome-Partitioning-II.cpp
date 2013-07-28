#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_LEN = 10000;

class Solution {
private:
	void initPalindrome(vector<vector<bool> > &p, string s) {
		int len = s.length();
		for (int i = 0; i < len; i++) {
			p[i].resize(len - i + 1); 
			p[i][0] = p[i][1] = true;
		}
		
		const char *data = s.data();
		for (int j = 2; j <= len; j++) {	
			for (int i = 0; i + j <= len; i++) {
				if(data[i] == data[i + j - 1] && p[i + 1][j - 2]) 
					p[i][j] = true;
			}
		}
	}

public:
	int minCut(string s) {
		int len = s.length();
		vector<vector<bool> > p(len);
		initPalindrome(p, s);

		vector<int> F(len + 1);
		F[0] = F[1] = 0;
		for (int i = 2; i <= len; i++) {
			if (p[0][i]) {
				F[i] = 0;
				continue;
			}

			int t = i - 1;
			for (int j = 1; j < i; j++) {
				if (p[j][i - j]) {
					if (F[j] + 1 < t)
						t = F[j] + 1;
				}
				else {
					if (F[j] + i - j < t)
						t = F[j] + i - j;
				}
			}
			F[i] = t;
		}
		return F[len];
	}
};

int main() {
	string s;
	Solution solution;
	char tmp[MAX_LEN + 1];

	while (scanf("%s", tmp) != -1) {
		printf("%s\n", tmp);
		s = string(tmp);

		int res = solution.minCut(s);
		printf("res: %d\n", res);
	}
}
