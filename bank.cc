#include "bank.h"
#include <vector>

Bank::Bank(unsigned int numStudents) : NUM_STUDENTS(numStudents) {
  balances.assign(NUM_STUDENTS, 0);
  sufficentBalance = new uCondition[NUM_STUDENTS];
}

Bank::~Bank() {
  delete[] sufficentBalance;
}

// Adds money to a bank account
void Bank::deposit(unsigned int id, unsigned int amount) {
  if (id < 0 || id >= NUM_STUDENTS) {
    uAbort("Invalid bank account ID");
  }

  balances[id] += amount;
  sufficentBalance[id].signal();
}

// Withdraws money from a bank account
void Bank::withdraw(unsigned int id, unsigned int amount) {
  if (id < 0 || id >= NUM_STUDENTS) {
    uAbort("Invalid bank account ID");
  }

  // If there is not a high enough balance, wait until there is
  while (balances[id] < amount) {
    sufficentBalance[id].wait();
  }
}
