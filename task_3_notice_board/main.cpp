#include <cstring>
#include <iostream>

constexpr int kRows = 5;
constexpr int kColumns = 10;

bool IsInsideBoard(int x, int y) {
  return x >= 0 && x < kColumns && y >= 0 && y < kRows;
}

void ClearBoard(char board[kRows][kColumns]) {
  for (int y = 0; y < kRows; ++y) {
    for (int x = 0; x < kColumns; ++x) {
      board[y][x] = ' ';
    }
  }
}

bool PutCharacter(char board[kRows][kColumns], int x, int y, char character) {
  if (!IsInsideBoard(x, y)) {
    return false;
  }
  board[y][x] = character;
  return true;
}

bool PutText(char board[kRows][kColumns], int x, int y, const char text[]) {
  const int length = std::strlen(text);
  if (!IsInsideBoard(x, y) || length > kColumns - x) {
    return false;
  }
  for (int i = 0; i < length; ++i) {
    PutCharacter(board, x + i, y, text[i]);
  }
  return true;
}

void PrintBoard(const char board[kRows][kColumns]) {
  for (int y = 0; y < kRows; ++y) {
    std::cout.write(board[y], kColumns);
    std::cout << '\n';
  }
}

int main() {
  char board[kRows][kColumns];
  ClearBoard(board);
  char command[16];
  while (std::cin >> command) {
    if (std::strcmp(command, "quit") == 0) {
      break;
    }
    if (std::strcmp(command, "clear") == 0) {
      ClearBoard(board);
    } else if (std::strcmp(command, "put") == 0) {
      int x = 0;
      int y = 0;
      char character = '\0';
      std::cin >> x >> y >> character;
      if (!PutCharacter(board, x, y, character)) {
        std::cout << "error\n";
      }
    } else if (std::strcmp(command, "text") == 0) {
      int x = 0;
      int y = 0;
      char text[128];
      std::cin >> x >> y >> text;
      if (!PutText(board, x, y, text)) {
        std::cout << "error\n";
      }
    } else if (std::strcmp(command, "print") == 0) {
      PrintBoard(board);
    } else {
      std::cout << "error\n";
    }
  }
  return 0;
}
