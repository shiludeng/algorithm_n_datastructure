#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int MAX_LEN = 10000;

/*
 * Run Status: Accepted
 * Program Runtime:
 * 	small data: 4ms
 *	large data: 100ms
 */
class Solution {

	struct Data {
		int row;
		int col;
		Data(int row, int col): row(row), col(col) {

		}
		Data *next;
	};

private:
	void bfs(vector<vector<char> > board, vector<vector<bool> > &visited, 
			 int row, int col) {

		int dir[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
		int height = board.size();
		int width = board[0].size();

		queue<Data> bfsqueue;
		while (!bfsqueue.empty()) {
			bfsqueue.pop();
		}
		bfsqueue.push(Data(row, col));
		while (!bfsqueue.empty()) {
			Data point = bfsqueue.front();
			bfsqueue.pop();
			if (!visited[point.row][point.col])
				visited[point.row][point.col] = true;
			for (int i = 0; i < 4; i++) {
				int row = point.row + dir[i][0];
				int col = point.col + dir[i][1];	 
				if (row >= 0 && row < height && col >= 0 && col < width) {
					if (!visited[row][col] && board[row][col] == 'O') {
						bfsqueue.push(Data(row, col));
						visited[row][col] = true;
					}
				}
			}
		}
	}


public:
	void solve(vector<vector<char> > &board) {
		int height = board.size();
		if (0 == height) 
			return;

		int width = board[0].size();
		if (0 == width) 
			return;

		vector<vector<bool> > visited(height);
		vector<Data> flipPoints;
		flipPoints.clear();
		for (int i = 0; i < height; i++) {
			visited[i].resize(width);
			for (int j = 0; j < width; j++) {
				visited[i][j] = false;
				if (board[i][j] == 'O') {
					flipPoints.push_back(Data(i, j));
				}
			}
		}

		for (int i = 0; i < width; i++) {
			if (board[0][i] == 'O' && !visited[0][i]) 
				bfs(board, visited, 0, i);
			if (board[height - 1][i] == 'O' && !visited[height - 1][i])
				bfs(board, visited, height - 1, i);
		}

		for (int i = 0; i < height; i++) {
			if (board[i][0] == 'O' && !visited[i][0]) 
				bfs(board, visited, i, 0);
			if (board[i][width - 1] == 'O' && !visited[i][width - 1])
				bfs(board, visited, i, width - 1);
		}

		for (int i = 0; i < flipPoints.size(); i++) {
			Data point = flipPoints[i];
			if (!visited[point.row][point.col]) {
				board[point.row][point.col] = 'X';
			}
		}
	}
};

int main() {
	Solution solution;
	char tmp[MAX_LEN + 1];
	int row, col;
	vector<vector<char> > board;

	while (scanf("%d %d", &row, &col) != -1) {
		board.resize(row);
		for(int i = 0; i < row; i++) {
			board[i].resize(col);
			scanf("%s", tmp);
			for (int j = 0; j < col; j++) {
				board[i][j] = tmp[j];
			}
		}

		for(int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				printf("%c", board[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		solution.solve(board);
		for(int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				printf("%c", board[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
}
