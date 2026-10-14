#include <cstring>
#include <iostream>
#include <new>

int main() {
  int layers = 0;
  int rows = 0;
  int columns = 0;
  std::cin >> layers >> rows >> columns;
  if (!std::cin || layers <= 0 || rows <= 0 || columns <= 0) {
    return 0;
  }
  int*** temperatures = new int**[layers];
  for (int layer = 0; layer < layers; ++layer) {
    temperatures[layer] = new int*[rows];
    for (int row = 0; row < rows; ++row) {
      temperatures[layer][row] = new int[columns];
      for (int column = 0; column < columns; ++column) {
        std::cin >> temperatures[layer][row][column];
      }
    }
  }
  const std::size_t row_size = columns * sizeof(int);
  const std::size_t snapshot_size = layers * rows * row_size;
  void* snapshot = ::operator new(snapshot_size);
  unsigned char* snapshot_cursor = static_cast<unsigned char*>(snapshot);
  for (int layer = 0; layer < layers; ++layer) {
    for (int row = 0; row < rows; ++row) {
      std::memcpy(snapshot_cursor, temperatures[layer][row], row_size);
      snapshot_cursor += row_size;
      std::memset(temperatures[layer][row], 0, row_size);
    }
  }
  snapshot_cursor = static_cast<unsigned char*>(snapshot);
  for (int layer = 0; layer < layers; ++layer) {
    for (int row = 0; row < rows; ++row) {
      std::memcpy(temperatures[layer][row], snapshot_cursor, row_size);
      snapshot_cursor += row_size;
    }
  }
  long long sum = 0;
  for (int layer = 0; layer < layers; ++layer) {
    std::cout << "Layer " << layer << ":\n";
    for (int row = 0; row < rows; ++row) {
      for (int column = 0; column < columns; ++column) {
        if (column > 0) {
          std::cout << ' ';
        }
        std::cout << temperatures[layer][row][column];
        sum += temperatures[layer][row][column];
      }
      std::cout << '\n';
    }
  }
  std::cout << "Sum: " << sum << '\n';
  ::operator delete(snapshot);
  for (int layer = 0; layer < layers; ++layer) {
    for (int row = 0; row < rows; ++row) {
      delete[] temperatures[layer][row];
    }
    delete[] temperatures[layer];
  }
  delete[] temperatures;
  return 0;
}