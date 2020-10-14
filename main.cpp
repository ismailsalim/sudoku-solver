/*
 * This programme tests that the individual functions declared in 'sudoku.h' 
 * and defined in 'sudoku.cpp' work correctly. It also provides the 
 * information reqiured for findings.txt.  
 */

#include <iostream>
#include <cstdio>
#include "sudoku.h" 

using namespace std;

int main() {

  char board[9][9];  
  /* This section illustrates the use of the pre-supplied helper functions */
  cout << "============= Pre-supplied functions =============" << "\n\n";

  cout << "Calling load_board():" << '\n';
  load_board("easy.dat", board);

  cout << '\n' << "Displaying Sudoku board with display_board():" << '\n';
  display_board(board);
  cout << "Done!" << "\n\n";

  cout << "=================== Question 1 ===================" << "\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";
  
  cout << "=================== Question 2 ===================" << "\n\n";

  load_board("easy.dat", board);
  
  /* Test should pass */
  cout << "\nPutting '1' into I8 is ";
  if (!make_move("I8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  /* Testing should fail due to duplicate in same box */
  cout << "\nPutting '7' into H6 is ";
  if (!make_move("H6", '7', board)) 
    cout << "NOT ";
  cout << "a valid move as it'd have a duplicate in the same box.The board is:" << '\n';
  display_board(board);

  /* Test should fail due to duplicate in same row */
  cout << "\nPutting '9' into D5 is ";
  if (!make_move("D5", '9', board)) 
    cout << "NOT ";
  cout << "a valid move as it'd have a duplicate in the same row. The board is:" << '\n';
  display_board(board);

  /* Test should fail due to duplicate in same column */
  cout << "\nPutting '8' into B6 is ";
  if (!make_move("B6", '8', board)) 
    cout << "NOT ";
  cout << "a valid move as it'd have a duplicate in the same column. The board is:" << '\n';
  display_board(board);

  /* Test should fail as entry already exists in cell */
  cout << "\nPutting '1' into H8 is ";
  if (!make_move("H8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move as the cell is already populated. The board is:" << '\n';
  display_board(board);

  /* Test should fail as entry is not a valid digit */
  cout << "\nPutting 'X' into H8 is ";
  if (!make_move("H8", 'X', board)) 
    cout << "NOT ";
  cout << "a valid move as the entry is not a valid digit. The board is:" << '\n';
  display_board(board);
  
  cout << "=================== Question 3 ===================" << "\n\n";
  /* Testing whether the programme saves the board succesfully */
  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << '\n';
  else
    cout << "Save board failed." << '\n';
  cout << '\n';

   cout << "=================== Question 4 ===================" << "\n\n";
  /* Checking that the programme is able to solve Sudoku board */
  load_board("easy.dat", board); // Easy board
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
   cout << '\n';

  load_board("medium.dat", board); // Hard board
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << '\n';
  
  cout << "=================== Question 5 ===================" << "\n\n";
  /* Testing if solutions exist for mystery boards */
  load_board("mystery1.dat", board); // mystery board 1
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  load_board("mystery2.dat", board); // mystery board 2
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  load_board("mystery3.dat", board); // mystery board 3
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  /* Testing the times taken to solve all solvable boards */
  load_board("mystery1.dat", board); // mystery board 1
  cout << "'Mystery1' board:" << endl;
  time_to_solve(board); 

  load_board("mystery3.dat", board); // mystery board 3
  cout << "'Mystery3' board:" << endl;
  time_to_solve(board);

  load_board("easy.dat", board); // easy board 
  cout << "'Easy' board:" << endl;
  time_to_solve(board); 

  load_board("medium.dat", board); // medium board 
  cout << "'Medium board:" << endl;
  time_to_solve(board);

  
  return 0;
}
  
