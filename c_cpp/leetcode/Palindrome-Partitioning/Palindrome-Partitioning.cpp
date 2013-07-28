#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_LEN = 10000;

/*
 * Run Status: Accepted
 * Program Runtime:
 * 	small data: 8ms
 *	large data: 52ms
 */
class Solution {

	struct Data {
		string data;
		Data *next;
	};

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

	void updateVector(vector<vector<Data*> > &F, int i, int j, string s) {
		vector<Data*> v(F[j]);
		if (F[j].size() == 0) {
			Data *data = new Data;
			data->next = NULL;
			data->data = s;
			F[i].push_back(data);
		} else {
			for (int k = 0; k < F[j].size(); k++) {
				Data *data = new Data;
				data->next = F[j][k];
				data->data = s;
				F[i].push_back(data);
			}
		}
	}

public:
	vector<vector<string> > partition(string s) {
		int len = s.length();
		vector<vector<bool> > palindrome(len);	
		initPalindrome(palindrome, s);

		vector<vector<Data*> > F(len + 1);
		Data *data = new Data;
		data->next = NULL;
		data->data = string(s, len -1);
		F[len - 1].push_back(data);
		for (int i = len - 2; i >= 0; i--) {
			for (int j = len - i; j >= 1; j--) {
				if (palindrome[i][j])
					updateVector(F, i, i + j, string(s, i, j));
			}
		}
		
		vector<vector<string> > res;
		for (int i = 0; i < F[0].size(); i++) {
			Data *head = F[0][i];	
			vector<string> v;
			while (head) {
				v.push_back(head->data);	
				head = head->next;
			}
			res.push_back(v);
		}
		return res;
	}
};

int main() {
	string s;
	Solution solution;
	char tmp[MAX_LEN + 1];

	while (scanf("%s", tmp) != -1) {
		printf("%s\n", tmp);
		s = string(tmp);

		vector<vector<string> > res = solution.partition(s);
		printf("[\n");
		for (int i = 0; i < res.size(); i++) {
			printf("\t[");
			for (int j = 0; j < res[i].size(); j++) {
				printf("\"%s\"", res[i][j].data());
				if (j != res[i].size() - 1)
					printf(",");
			}
			printf("]");
			if (i != res.size() - 1)
				printf(",");
			printf("\n");
		}
		printf("]\n");
	}
}
