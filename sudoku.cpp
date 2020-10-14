/*
 * This programme contains the implementation code for all the functions 
 * that are used for the Sudoku solver problem.
 * Consult 'sudoku.h' for a more detailed explanation of each function. 
 */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <chrono>
#include "sudoku.h"

using namespace std;

/* Start of implementation to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << '\n';
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << '\n';
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
}

void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}
/* End of implementation */

/* Start of implementation to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}
/* End of implementation */

/* Start of implementation to check if Sudoku board is complete */
bool is_complete(const char board[9][9]) {
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      char entry = board[row][col];
      if (!is_valid_digit(entry)){ // re-using digit validity checker for make_move(...)
	return false;
      }
    }
  }
  return true;
}
/* End of implementation */

/* Start of implementation for making a move */
bool make_move(const char position[], const char digit, char board[9][9]) {
  int row = position[0] - 65, col = position[1] - 49; // type casting and arithmetic according to ASCII
  bool valid_move = is_valid_move(row, col, digit, board);
  if (valid_move) {
    board[row][col] = digit;
    return true;
  }				     
  return false;
}

bool is_valid_move(const int row, const int col, const char digit, const char board[9][9]) {
  if (is_valid_digit(digit) && position_in_range(row, col) &&
      cell_empty(row, col, board) && not_in_row(row, digit, board) &&
      not_in_col(col, digit, board) &&  not_in_box(row, col, digit, board))
    return true; // all six criteria must be satisfied according to Sudoku
  return false;
}

bool is_valid_digit(const char digit) {
  if (digit >= '1' && digit <= '9') // also excludes any other non-numeric character representations 
    return true;
  return false;
}

bool position_in_range(const int row, const int col) {
  if (row >= 0 && col < 9)
    return true;
  return false;
}

bool cell_empty(const int row, const int col, const char board[9][9]) {
  if (board[row][col] == '.') // empty cell of board represented by '.' 
    return true;
  return false;
}

bool not_in_row(const int row, const char digit, const char board[9][9]) {
  for (int col = 0; col < 9; col++) {
    if (digit == board[row][col])
      return false;
  }
  return true;
}

bool not_in_col(const int col, const char digit, const char board[9][9]) {
  for (int row = 0; row < 9; row++) {
    if (digit == board[row][col])
      return false;
  }
  return true;
}
    
bool not_in_box(const int row, const int col, const char digit, const char board[9][9]) {
  int box_row_origin = row - (row % 3), box_col_origin = col - (col % 3); // top left cell of the box associated with the given position 
  for (int row_index = 0; row_index < 3; row_index++) {
    for (int col_index = 0; col_index < 3; col_index++) {
      if (digit == board[box_row_origin + row_index][box_col_origin + col_index])
	return false;
    }
  }
  return true;
}
/* End of implementation */    

/* Start of implmentation for saving board into a file */
bool save_board(const char filename[], const char board[9][9]) {
  ofstream out(filename);
  int row = 0;
  while (row < 9) { 
    for (int col = 0; col < 9; col++)
      out.put(board[row][col]);
    out.put('\n'); // new line for every 9 entries saved to file (starts a new row for board)
    row++;
  }
  out.close();
  return out.fail() ? false : true; // checks flag settiing of output stream 
}
/* End of implmentation */

/* Start of implementation for solving the board */
bool solve_board(char board[9][9]) {
  if (is_complete(board)) // board must be solved if it is full due to make_move(...) criteria
    return true;
  for (int row = 0; row < 9; row++) { // iterate across the board until an empty cell is found
    for (int col = 0; col < 9; col++) { 
      if (cell_empty(row, col, board)) {
	char position[2];
	position[0] = row + 65; // type casting and arithmetic according to ASCII
	position[1] = col + 49;
	for (char entry = '1'; entry <= '9'; entry++) { // attempt to make move in empty cell using all digits from 1 to 9 
	  bool valid_move = make_move(position, entry, board); 
	  if (valid_move) {  // if move is valid, move onto next cell and keep trying
	    if (solve_board(board))  
	      return true;
	    board[row][col] = '.'; // otherwise revert cell to empty
	  }
	}
	return false;
      }
    }
  }
  assert(false && "reaches end of function, which should never happpen"); 
}

void time_to_solve(char board[9][9]){
  auto timer_start = std::chrono::high_resolution_clock::now(); // start internal timer chrono object
  solve_board(board);                                           
  auto timer_end  = std::chrono::high_resolution_clock::now(); // end internal timer as soon as board is solved 
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer_start).count();
  cout << "Takes " << duration << " microseconds to solve.\n\n";
}
/* End of implementation */
  
