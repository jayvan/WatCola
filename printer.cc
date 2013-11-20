#include "printer.h"
#include <iostream>

using namespace std;

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
  NUM_STUDENTS(numStudents), NUM_VENDING_MACHINES(numVendingMachines), NUM_COURIERS(numCouriers) {

  states = new char[1];
  firstValues = new int[1];
  secondValues = new int[1];
  filled = new bool[1];

  for (unsigned int i = 0; i < 0; i++) {
    filled[i] = false;
  }

  resume();
}

Printer::~Printer() {
  flush();
  delete[] states;
  delete[] firstValues;
  delete[] secondValues;
  delete[] filled;
}
