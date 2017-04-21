#include <iostream>
#include <stdlib.h>

using namespace std;

int map[9][9] = {0};

int check_row(int pos) {
    int flag[10] = {-1};
    memset(flag, -1, sizeof(flag));
    int row = pos / 9;
    int col = pos % 9;
    for (int i = 0; i <= col; ++i) {
        if (flag[map[row][i]] == 0) {
            return -1;
        } else {
            flag[map[row][i]] = 0;
        }
    }
    return 0;
}

int check_col(int pos) {
    int flag[10] = {-1};
    memset(flag, -1, sizeof(flag));
    int row = pos / 9;
    int col = pos % 9;
    for (int i = 0; i <= row; ++i) {
        if (flag[map[i][col]] == 0) {
            return -1;
        } else {
            flag[map[i][col]] = 0;
        }
    }
    return 0;
}

int check_grid(int pos) {
    int flag[10] = {-1};
    memset(flag, -1, sizeof(flag));
    int grid_row = (pos / 9) / 3;
    int grid_col = (pos % 9) / 3;
    int start_row = grid_row * 3;
    int start_col = grid_col * 3;
    int end_row = pos / 9;
    int end_col = pos % 9;
    for (int i = start_row; i <= end_row; ++i) {
        int last_col = (i < end_row) ? (grid_col * 3 + 2) : end_col;
        for (int j = start_col; j <= last_col; ++j) {
            if (flag[map[i][j]] == 0) {
                return -1;
            } else {
                flag[map[i][j]] = 0;
            }
        }
    }
    return 0;
}

int check_diagonal(int pos) {
    if (pos % 10 == 0) {
        int flag[10] = {-1};
        memset(flag, -1, sizeof(flag));
        int row = pos / 9;
        for (int i = 0; i <= row; ++i) {
            if (flag[map[i][i]] == 0) {
                return -1;
            } else {
                flag[map[i][i]] = 0;
            }
        }
    }
    if (pos % 8 == 0 && pos < 80) {
        int flag[10] = {-1};
        memset(flag, -1, sizeof(flag));
        int row = pos / 9;
        for (int i = 0; i <= row; ++i) {
            if (flag[map[i][8 - i]] == 0) {
                return -1;
            } else {
                flag[map[i][8 - i]] = 0;
            }
        }
    }
    return 0;
}

int check(int pos) {
    if (pos < 0) {
        return 0;
    }

    if (check_row(pos) < 0) {
        //cout << "check row failed " << pos << std::endl;
        return -1;
    }

    if (check_col(pos) < 0) {
        //cout << "check_col failed " << pos << std::endl;
        return -1;
    }

    if (check_grid(pos) < 0) {
        //cout << "check_grid failed " << pos << std::endl;
        return -1;
    }

    if (check_diagonal(pos) < 0) {
        //cout << "check_diagonal failed " << pos << std::endl;
        return -1;
    }
    
    //cout << "check  success " << pos << std::endl;
    return 0;
}

int output_row_sep() {
    for (int i = 0; i < 9; ++i) {
        if (i == 0) {
            cout << "-";
        }
        cout << "----";
    }
    cout << endl;
}

int output_row_sep(int row) {
    for (int i = 0; i < 9; ++i) {
        if (i == 0) {
            cout << "|";
        }
        cout << " " << map[row][i] << " |";
    }
    cout << std::endl;
}

int output() {
    for (int i = 0; i < 9; ++i) {
        if (i == 0) {
            output_row_sep();
        }
        output_row_sep(i);
        output_row_sep();
    }
    return 0;
}

void dfs(int pos) {
    //cout << "start " << pos << std::endl;
    if (pos > 0 && check(pos - 1) < 0) {
        //output();
        return;
    }

    if (pos == 81) {
        output();
        return;
    }

    //cout << "mid " << pos << std::endl;
    for (int i = 1; i <= 9; ++i) {
        map[pos / 9][pos % 9] = i;
        dfs(pos + 1);
        map[pos / 9][pos % 9] = 0;
    }
    return;
}

int main() {
    dfs(0);
    return 0;
}
