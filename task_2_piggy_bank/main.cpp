#include <cstdio>
#include <cstring>
#include <iostream>

using Operation = bool (*)(int& balance, int argument);

bool Deposit(int& balance, int amount) {
  if (amount <= 0) {
    return false;
  }
  balance += amount;
  return true;
}

bool Withdraw(int& balance, int amount) {
  if (amount <= 0 || amount > balance) {
    return false;
  }
  balance -= amount;
  return true;
}

bool PrintBalance(int& balance, int /* argument */) {
  std::cout << balance << '\n';
  return true;
}

bool Reset(int& balance, int /* argument */) {
  balance = 0;
  return true;
}

bool DoubleBalance(int& balance, int /* argument */) {
  balance *= 2;
  return true;
}

struct Command {
  const char* name;
  Operation operation;
  bool takes_argument;
};

int main() {
  const Command commands[] = {
      {"deposit", Deposit, true},
      {"withdraw", Withdraw, true},
      {"balance", PrintBalance, false},
      {"reset", Reset, false},
      {"double", DoubleBalance, false},
  };
  const int command_count = sizeof(commands) / sizeof(commands[0]);
  int balance = 0;
  char line[128];
  while (std::cin.getline(line, sizeof(line))) {
    char command_name[32];
    int argument = 0;
    char extra = '\0';
    const int item_count =
        std::sscanf(line, "%31s %d %c", command_name, &argument, &extra);
    if (item_count == 1 && std::strcmp(command_name, "stop") == 0) {
      break;
    }
    const Command* selected_command = nullptr;
    for (int i = 0; i < command_count; ++i) {
      if (item_count >= 1 &&
          std::strcmp(command_name, commands[i].name) == 0) {
        selected_command = &commands[i];
        break;
      }
    }
    bool success = selected_command != nullptr;
    if (success) {
      const int expected_items = selected_command->takes_argument ? 2 : 1;
      success = item_count == expected_items;
    }
    if (success) {
      success = selected_command->operation(balance, argument);
    }
    if (!success) {
      std::cout << "error\n";
    }
  }
  return 0;
}