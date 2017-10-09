#include <iostream>
#include <stdlib.h>

using namespace std;

const int ROW_NUM = 4;
const int COL_NUM = 5;

int maze[4][5] = {
    0, 1, 0, 1, 0,
    0, 0, 0, 1, 0,
    0, 1, 0, 0, 0,
    0, 0, 0, 1, 0,
};

int dir[4][2] = {
    {1, 0}, {0, -1}, {-1, 0}, {0, 1}
};

int output_row_sep() {
    for (int i = 0; i < COL_NUM; ++i) {
        if (i == 0) {
            cout << "-";
        }
        cout << "----";
    }
    cout << endl;
}

int output_row_sep(int row) {
    for (int i = 0; i < COL_NUM; ++i) {
        if (i == 0) {
            cout << "|";
        }
        cout << " " << maze[row][i] << " |";
    }
    cout << std::endl;
}

int output() {
    for (int i = 0; i < ROW_NUM; ++i) {
        if (i == 0) {
            output_row_sep();
        }
        output_row_sep(i);
        output_row_sep();
    }
    return 0;
}

bool dfs(int row, int col) {
    //cout << row << " " << col << std::endl;
    if (row < 0 || row > ROW_NUM - 1 || col < 0 || col > COL_NUM - 1) {
        return false;
    }

    if (maze[row][col] == 1) {
        return false;
    }

    if (row == ROW_NUM - 1 && col == COL_NUM -1) {
        output();
        return true;
    }

    //cout << "mid " << pos << std::endl;
    for (int i = 0; i < 4; ++i) {
        int next_row = row + dir[i][0];
        int next_col = col + dir[i][1];
        int tmp = maze[next_row][next_col];
        if (tmp == 2 || tmp == 1) {
            continue;
        }
        maze[next_row][next_col] = 2;
        if (dfs(next_row, next_col))  {
            return true;
        }
        maze[next_row][next_col] = tmp;
    }
    return false;
}

int main() {
    output();
    maze[0][0] = 2;
    if (!dfs(0, 0)) {
        std::cout << "no path found!\n";
    }
    return 0;
}

