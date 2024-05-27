#include <stdio.h>

#define UNASSIGNED 0
#define N 9

// Function to check if a number is safe to place in a cell
int isSafe(int grid[N][N], int row, int col, int num) {
  // Check row and column for num
  for (int i = 0; i < N; i++) {
    if (grid[row][i] == num || grid[i][col] == num) {
      return 0;
    }
  }

  // Check subgrid for num
  int startRow = row - row % 3;
  int startCol = col - col % 3;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (grid[startRow + i][startCol + j] == num) {
        return 0;
      }
    }
  }

  return 1;
}
// Function to find an unassigned cell
int findUnassigned(int grid[N][N], int* row, int* col) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (grid[i][j] == UNASSIGNED) {
        *row = i;
        *col = j;
        return 1;
      }
    }
  }

  return 0;
}

// Function to solve the Sudoku puzzle
int solveSudoku(int grid[N][N]) {
  int row, col;

  // Find an unassigned cell
  if (!findUnassigned(grid, &row, &col)) {
    return 1; // Puzzle solved
  }

  // Try possible numbers for the unassigned cell
  for (int num = 1; num <= N; num++) {
    if (isSafe(grid, row, col, num)) {
      grid[row][col] = num;

      // Recursively solve the puzzle with the placed number
      if (solveSudoku(grid)) {
        return 1;
      }

      // Backtrack if placement doesn't lead to a solution
      grid[row][col] = UNASSIGNED;
    }
  }

  // If no number is safe for the cell, return false
  return 0;
}



// Function to print the Sudoku grid
void printSudoku(int grid[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%d ", grid[i][j]);
    }
    printf("\n");
  }
}

int main() {
  // Sample Sudoku grid to be solved
  int grid[N][N];

  printf("Enter the elements of the sudoku:\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
           
            scanf("%d", &grid[i][j]);
        }
    }


  if (solveSudoku(grid)) {
    printf("Solved Sudoku:\n");
    printSudoku(grid);
  } else {
    printf("No solution found\n");
  }

  return 0;
}
