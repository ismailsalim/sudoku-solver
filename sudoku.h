/* 
 * 
 * This programme contains the declarations for the functions used in sudoku.cpp.
 * These functions enable a user to:
 * - Load a data file that represents an incomplete Sudoku board.
 * - Display the Sudoku board with more a friendlier layout.
 * - Enter a digit into an empty cell of the board.
 * - Save a modified board as a .txt file.
 * - Test whether an incomplete Sudoku board is solvable. 
 */

/* ------------------ START OF FUNCTION DECLARATIONS ------------------------- */

#ifndef SUDOKU_H
#define SUDOKU_h

/* 
 * Reads in characters from the file with name <filename> into the 
 * 9 x 9 character array Sudoku board.
 */
void load_board(const char* filename, char board[9][9]);

/*
 * Displays a 9 x 9 character array board in a friendly layout familiar
 * to Sudoku players.
 */
void display_board(const char board[9][9]);

/* 
 * Takes a 9 x 9 character array board and returns true if all board positions 
 * are occupied by digits, and false otherwise.
 */
bool is_complete(const char board[9][9]);

/*
 * Takes a 9 x 9 character array board, a two-character string representing a
 * position on the board, and a character denoting the digit to be placed in the given
 * position, and attempts to accordingly place a digit onto the Sudoku board.
 * Returns true if the move is valid, and stores the digit in the 2D array that is
 * passed in. Otherwise returns false, and does not change the 2D array.
 */
bool make_move(const char position[], const char digit, char board[9][9]);

/* 
 * Checks if the move attempted by make_move(...) is valid according to the criteria
 * of Sudoku. Returns true is ALL SIX criteria (specified below) are satisfied, and false
 * otherwise.
 */
bool is_valid_move(const int row, const int col, const char digit, const char board[9][9]);

/*
 * (Criterium 1) Returns true if the digit inputted into make_move(...) is numerical
 * AND greater or equal to 1 and less than or equal to 9, and false otherwise. 
 */
bool is_valid_digit(const char digit);

/*
 * (Criterium 2) Returns true if the position of the digit inputted into make_move(...)
 * is within the bounds of the Sudoku board, and false otherwise.  
 */
bool position_in_range(const int row, const int col);

/*
 * (Criterium 3) Returns true if the position that is inputted into make_move(...) 
 * represents an emtpy cell of the Sudoku board, and false otherwise. 
 */
bool cell_empty(const int row, const int col, const char board[9][9]);

/* 
 * (Criterum 4) Returns true if the digit that is inputted into make_move(...) does
 * not appear in the same ROW of the Sudoku board as the inputted position,and 
 * false otherwise. 
 */ 
bool not_in_row(const int row, const char digit, const char board[9][9]);

/* 
 * (Criterum 5) Returns true if the digit that is inputted into make_move(...) does
 * not appear in the same COLUMN of the Sudoku board as the inputted position, and 
 * false otherwise. 
 */ 
bool not_in_col(const int col,  const char digit, const char board[9][9]);

/* 
 * (Criterum 6) Returns true if the digit that is inputted into make_move(..) does
 * not appear in the same 3 x 3 box as the inputted position, and false otherwise.
 */ 
bool not_in_box(const int row, const int col, const char digit, const char board[9][9]);

/*
 * Saves a 9 x 9 character array board as <filename>.dat which represents the board with
 * the same formatting as the file from which the 9 x 9 board is loaded from. Returns
 * true if saving is successful, and false otherwise.
 */
bool save_board(const char filename[], const char board[9][9]);

/*
 * Takes a 9 x 9 character array board and tests if it is solvable. Returns true if 
 * it's solvable, and false otherwise.
 */ 
bool solve_board(char board[9][9]);

/* 
 * Takes a 9 x 9 character array board and displays the time taken for Sudoku board to be
 * solved according to solve_board(...).
 */
void time_to_solve(char board[9][9]);

#endif /* SUDOKU_H */
