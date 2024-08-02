// Fully Working Code

// Website used for c++ reference : https://cplusplus.com/


#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// this generates random number between l and r (l and r inclusivevector<pair<char, pair<int, int>>>)
int getRandomNumber(int l, int r) {return uniform_int_distribution<int>(l, r)(rng);}

void dfs(int curX, int curY, int dx, int dy, int homeX, int homeY, int n, int m, vector<vector<char>> board, vector<pair<char, pair<int, int>>> &singlePath, vector<vector<pair<char, pair<int, int>>>> &allPaths) {

    // curX and curY depicts the current cell of the killer
    // dx and dy depicts the current direction killer is moving in
    // newi and newj depicts new current cell after moving forward

    int newi = curX + dx, newj = curY + dy;

    if (newi == homeX && newj == homeY) { // this will check if killer reached homeCell or not
        allPaths.push_back(singlePath);
        return;
    }
    if (newi >= 0 && newi < n && newj >= 0 && newj < m) {// this if condition will make sure the soldier does not move out of the board

        if (board[newi][newj] == '.') {// if new cell is an empty cell we will simple move forward
            dfs(newi, newj, dx, dy, homeX, homeY, n, m, board, singlePath, allPaths);
        } else if (board[newi][newj] == 'S') {

            // if new cell is occupied by a soldier then we have two options either to jump over the soldier and keep moving forward or
            // kill the soldier and turn left

            singlePath.push_back({'J', {newi, newj}}); // this is the case if killer jumps

            dfs(newi, newj, dx, dy, homeX, homeY, n, m, board, singlePath, allPaths); // jumping over the soldier

            singlePath.pop_back(); // restore the previous state (backtrack) to explore all other paths

            // following if conditions are to change its directon to left of it from current direction dx and dy
            if (dx == 0 && dy == 1) {
                dx = -1, dy = 0;
            } else if (dx == -1 && dy == 0) {
                dx = 0, dy = -1;
            } else if (dx == 0 && dy == -1) {
                dx = 1, dy = 0;
            } else if (dx == 1, dy == 0) {
                dx = 0, dy = 1;
            }

            singlePath.push_back({'K', {newi, newj}}); // this is the case if killer kills the soldier and moves left

            board[newi][newj] = '.'; // this cell became empty after killer kills the soldier

            dfs(newi, newj, dx, dy, homeX, homeY, n, m, board, singlePath, allPaths); // kill soldier and turns left

            // restore the previous state (backtrack) to exlpore all other paths
            board[newi][newj] = 'S';
            singlePath.pop_back();
        }
    }
}

int main() {
    int n, m; // dimensions of the board
    cin >> n >> m;

    vector<vector<char>> board(n, vector<char>(m, '.')); // board;
    // dot represents an empty cell

    // number_of_soldiers should be less then total number of cells i.e. n*m because 1 cell must be occupied by specialized castle
    int number_of_soldiers;
    cin >> number_of_soldiers;

    set<int> st; // to check occupied cells

    for (int i = 0; i < number_of_soldiers; ++i) {

        //generating random cells for soldiers
        int randomCellNumber = getRandomNumber(1, n * m);

        while (st.count(randomCellNumber)) { // this will make sure it gives a cell which is not already occupied
            randomCellNumber = getRandomNumber(1, n * m);
        }

        st.insert(randomCellNumber);
        int posx = randomCellNumber / n, posy = (randomCellNumber % m == 0 ? m : randomCellNumber % m) - 1;
        board[posx][posy] = 'S'; // marking soldiers as S on the board
    }

    //generating random cell for specialized castle
    int randomCellNumber = getRandomNumber(1, n * m);
    while (st.count(randomCellNumber)) {
        randomCellNumber = getRandomNumber(1, n * m);
    }

    int posx = randomCellNumber / n, posy = (randomCellNumber % m == 0 ? m : randomCellNumber % m) - 1;
    board[posx][posy] = 'K'; // marking specialized castle as K on the board

    //Have a look at the board
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << board[i][j] << " ";
        } cout << endl;
    } cout << endl;

    vector<pair<char, pair<int, int>>> singlePath;// this will containe a path during dfs calls
    vector<vector<pair<char, pair<int, int>>>> allPaths; // this will contain all the paths after dfs call

    dfs(posx, posy, 0, 1, posx, posy, n, m, board, singlePath, allPaths); // running a depth first search staring from the specialized castle to explore all the possible paths on the board

    if (allPaths.size() == 0) {
        cout << "NO PATH POSSIBLE" << endl;
        return 0;
    }

    //Printing all possible paths
    int curPathNumber = 1;
    for (auto i : allPaths) {
        cout << "PATH" << curPathNumber++ << endl;
        cout << endl;
        cout << "STARTING CELL (" << posx << "," << posy << ")" << endl;
        for (auto j : i) {
            if (j.first == 'J') {
                cout << "JUMP OVER (" << j.second.first << "," << j.second.second << ")" << endl;
            } else {
                cout << "KILL AT (" << j.second.first << "," << j.second.second << "). THEN, TURN LEFT" << endl;
            }
        }
        cout << "REACHED HOME" << endl;
        cout << endl;
    }
}