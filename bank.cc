#include "bank.h"

Bank::Bank(unsigned int numStudents) : NUM_STUDENTS(numStudents) {
  balances = new unsigned int[NUM_STUDENTS];
  sufficentBalance = new uCondition[NUM_STUDENTS];

  for (unsigned int i = 0; i < NUM_STUDENTS; i++) {
    balances[i] = 0;
  }
}

Bank::~Bank() {
  delete[] balances;
  delete[] sufficentBalance;
}

// Adds money to a bank account
void Bank::deposit(unsigned int id, unsigned int amount) {
  if (id >= NUM_STUDENTS) {
    uAbort("Invalid bank account ID");
  }

  balances[id] += amount;
  sufficentBalance[id].signal();
}

// Withdraws money from a bank account
void Bank::withdraw(unsigned int id, unsigned int amount) {
  if (id >= NUM_STUDENTS) {
    uAbort("Invalid bank account ID");
  }

  // If there is not a high enough balance, wait until there is
  while (balances[id] < amount) {
    sufficentBalance[id].wait();
  }
}
