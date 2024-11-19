#include <iostream>
#include <ctime>
using namespace std;

int rows, cols;
int solutionCount = 0;

void displayBoard(int **grid)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      cout << grid[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

bool isValidPlacement(int **grid, int x, int y)
{
  int knightMoves[8][2] = {
      {-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};

  for (int i = 0; i < 8; i++)
  {
    int newX = x + knightMoves[i][0];
    int newY = y + knightMoves[i][1];

    if (newX >= 0 && newX < rows && newY >= 0 && newY < cols)
    {
      if (grid[newX][newY] == 1)
      {
        return false;
      }
    }
  }
  return true;
}

void solveKnights(int **grid, int knightsRemaining, int x, int y)
{
  if (knightsRemaining == 0)
  {
    solutionCount++;
    cout << "Solution " << solutionCount << ":" << endl;
    displayBoard(grid);
    return;
  }

  if (x >= rows)
    return;

  if (y >= cols)
  {
    solveKnights(grid, knightsRemaining, x + 1, 0);
    return;
  }

  int remainingCells = (rows * cols) - (x * cols + y);
  if (remainingCells < knightsRemaining)
    return;

  if (isValidPlacement(grid, x, y))
  {
    grid[x][y] = 1;
    solveKnights(grid, knightsRemaining - 1, x, y + 1);
    grid[x][y] = 0;
  }

  solveKnights(grid, knightsRemaining, x, y + 1);
}

int main()
{
  double startTime, endTime, elapsedTime;
  cout << "Enter dimensions of the board (rows and columns): ";
  cin >> rows >> cols;

  int **grid = new int *[rows];
  for (int i = 0; i < rows; i++)
  {
    grid[i] = new int[cols];
  }

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      grid[i][j] = 0;
    }
  }

  cout << "Enter the number of knights to place: ";
  int knights;
  cin >> knights;

  startTime = (double)clock();
  solveKnights(grid, knights, 0, 0);
  endTime = (double)clock();
  elapsedTime = (endTime - startTime) / CLOCKS_PER_SEC;

  if (solutionCount == 0)
  {
    cout << "No solutions exist!" << endl;
  }
  else
  {
    cout << "Total solutions found: " << solutionCount << endl;
  }
  cout << "Total time taken: " << elapsedTime << " seconds" << endl;

  for (int i = 0; i < rows; i++)
  {
    delete[] grid[i];
  }
  delete[] grid;

  return 0;
}
