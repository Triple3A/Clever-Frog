#include <iostream>
#include <vector>

using namespace std;

const int POSSIBLE_MOVES = 4;
const string can = "Insane!";
const string cant = "Bad map configuration!";

int row_delta[] = {2, 0, -2, 0};
int col_delta[] = {0, -2, 0, 2};
string movee = "DLUR";
int neighbor_row_delta[] = {1, 0, -1, 0};
int neighbor_col_delta[] = {0, -1, 0, 1};
vector <int> row_moves;
vector <int> col_moves;
vector <char> moves;
void push(int row, int col, char mov)
{
    row_moves.push_back(row);
    col_moves.push_back(col);
    moves.push_back(mov);
}

void pop()
{
    row_moves.pop_back();
    col_moves.pop_back();
    moves.pop_back();
}
bool find_tour(string table[], int rows, int columns, int curr_row, int curr_col, int num_o)
{
    if(num_o == 1)
        return true;
    int new_row, new_col;
    int neighbor_row, neighbor_col;
    if(table[curr_row][curr_col] == 'o')
    {
        for(int i = 0; i < POSSIBLE_MOVES; i++)
        {
            new_row = curr_row + row_delta[i];
            new_col = curr_col + col_delta[i];
            neighbor_row = curr_row + neighbor_row_delta[i];
            neighbor_col = curr_col + neighbor_col_delta[i];
            if(new_row < 0 || new_row >= rows || new_col < 0 || new_col >= columns)
                continue;
            if(table[new_row][new_col] != '#')
                continue;
            if(table[neighbor_row][neighbor_col] != 'o')
                continue;
            table[curr_row][curr_col] = '#';
            table[neighbor_row][neighbor_col] = '#';
            table[new_row][new_col] = 'o';
            push(curr_row + 1, curr_col + 1, movee[i]);
            for(int i = 0; i < rows; i++)
                for(int j = 0; j < columns; j++)
                    if(find_tour(table, rows, columns, i, j, num_o - 1))
                        return true;
            table[curr_row][curr_col] = 'o';
            table[neighbor_row][neighbor_col] = 'o';
            table[new_row][new_col] = '#';
            pop();
        }
        return false;
    }
    return false;
}

int number_o(string table[], int rows, int columns)
{
    int num_o = 0;
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
            if(table[i][j] == 'o')
                num_o++;
    return num_o;
}

bool solve(string table[], int rows, int columns, int init_row, int init_col, int num_o)
{
    if(find_tour(table, rows, columns, init_row, init_col, num_o))
    {
        cout << can << endl;
        for(int i = 0; i < row_moves.size(); i++)
        {
            cout << row_moves[i] << ' ';
            cout << col_moves[i] << ' ';
            cout << moves[i] << endl;
        }
        return true;
    }
    return false;
}
int main()
{
    int h, w;
    cin >> h >> w;
    string table[h];
    for(int i = 0; i < h; i++)
        cin >> table[i];
    int num_o = number_o(table, h, w);
    for(int row = 0; row < h; row++)
        for(int col = 0; col < w; col++)
            if(solve(table, h, w, row, col, num_o))
                return 0;
    cout << cant << endl;
    return 0;
}
