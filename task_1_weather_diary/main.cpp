#include <iomanip>
#include <iostream>

struct TemperatureRange {
  int minimum;
  int maximum;
};

double CalculateAverage(const int temperatures[], int size) {
  long long sum = 0;
  for (int i = 0; i < size; ++i) {
    sum += temperatures[i];
  }
  return static_cast<double>(sum) / size;
}

TemperatureRange FindTemperatureRange(const int temperatures[], int size) {
  TemperatureRange range = {temperatures[0], temperatures[0]};
  for (int i = 1; i < size; ++i) {
    if (temperatures[i] < range.minimum) {
      range.minimum = temperatures[i];
    }
    if (temperatures[i] > range.maximum) {
      range.maximum = temperatures[i];
    }
  }
  return range;
}

int CountFreezingDays(const int temperatures[], int size) {
  int freezing_days = 0;
  for (int i = 0; i < size; ++i) {
    if (temperatures[i] < 0) {
      ++freezing_days;
    }
  }
  return freezing_days;
}

int main() {
  int days = 0;
  std::cin >> days;
  if (!std::cin || days <= 0) {
    return 0;
  }
  int* temperatures = new int[days];
  for (int i = 0; i < days; ++i) {
    std::cin >> temperatures[i];
  }
  const double average = CalculateAverage(temperatures, days);
  const TemperatureRange range = FindTemperatureRange(temperatures, days);
  const int freezing_days = CountFreezingDays(temperatures, days);
  std::cout << std::fixed << std::setprecision(1) << average << '\n';
  std::cout << range.minimum << ' ' << range.maximum << '\n';
  std::cout << freezing_days << '\n';
  delete[] temperatures;
  return 0;
}