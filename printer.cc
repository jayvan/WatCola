#include "printer.h"
#include <iostream>

using namespace std;

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
  NUM_STUDENTS(numStudents),
  NUM_VENDING_MACHINES(numVendingMachines),
  NUM_COURIERS(numCouriers),
  NUM_STATES(5 + NUM_STUDENTS + NUM_VENDING_MACHINES + NUM_COURIERS)
{
  states.resize(NUM_STATES);
  firstValues.resize(NUM_STATES);
  secondValues.resize(NUM_STATES);
  filled.assign(NUM_STATES, false);

  resume();
}

Printer::~Printer() {
  flush();
}

void Printer::main() {
  // Header

  // Fixed headings
  cout << "Parent\tWATOff\tNames\tTruck\tPlant";

  // Students
  for (unsigned int i = 0; i < NUM_STUDENTS; i++) {
    cout << "\tStud" << i;
  }

  // Machines
  for (unsigned int i = 0; i < NUM_VENDING_MACHINES; i++) {
    cout << "\tMach" << i;
  }

  // Couriers
  for (unsigned int i = 0; i < NUM_COURIERS; i++) {
    cout << "\tCour" << i;
  }

  cout << endl;

  // Dashes for heading
  for (unsigned int i = 0; i < NUM_STATES; i++) {
    cout << "*******\t";
  }

  cout << endl;

  suspend();

  while (true) {
    // If we're overwriting a value or if the task is finishing flush the buffer
    if (filled[lid] || state == 'F') {
      flush();
    }

    // For finishing, print an F in the finishers column and dashes in every other column
    if (state == 'F') {
      for (unsigned int i = 0; i < NUM_STATES; i++) {
        if (i == lid) {
          cout << 'F' << "\t";
        } else {
          cout << " ... \t";
        }
      }
      cout << endl;
    } else {
      states[lid] = state;
      firstValues[lid] = value1;
      secondValues[lid] = value2;
      filled[lid] = values + 1;
    }

    suspend();
  }
}

void Printer::flush() {
  for (unsigned int i = 0; i < NUM_STATES; i++) {
    if (filled[i]) {
      cout << (char)states[i];
    }

    if (filled[i] >= 2) {
      cout << firstValues[i];
    }

    if (filled[i] >= 3) {
      cout << "," << secondValues[i];
    }

    cout << "\t";

    firstValues[i] = 0;
    secondValues[i] = 0;
    states[i] = ' ';
    filled[i] = false;
  }

  cout << endl;
}

void Printer::doPrint(Kind kind, unsigned int lid, char state, char values, int value1, int value2) {

  if (kind == Parent) {
    lid = 0;
  } else if (kind == WATCardOffice) {
    lid = 1;
  } else if (kind == NameServer) {
    lid = 2;
  } else if (kind == Truck) {
    lid = 3;
  } else if (kind == BottlingPlant) {
    lid = 4;
  } else if (kind == Student) {
    lid += 5;
  } else if (kind == Vending) {
    lid += 5 + NUM_STUDENTS;
  } else if (kind == Courier) {
    lid += 5 + NUM_STUDENTS + NUM_VENDING_MACHINES;
  } else {
    uAbort("Invalid 'kind' passed to printer");
  }

  Printer::lid = lid;
  Printer::state = state;
  Printer::value1 = value1;
  Printer::value2 = value2;
  Printer::values = values;

  resume();
}

void Printer::print( Kind kind, char state ) {
  doPrint(kind, 0, state, 0, 0, 0);
}

void Printer::print( Kind kind, char state, int value1 ) {
  doPrint(kind, 0, state, 1, value1, 0);
}

void Printer::print( Kind kind, char state, int value1, int value2 ) {
  doPrint(kind, 0, state, 2, value1, value2);
}

void Printer::print( Kind kind, unsigned int lid, char state ) {
  doPrint(kind, lid, state, 0, 0, 0);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
  doPrint(kind, lid, state, 1, value1, 0);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
  doPrint(kind, lid, state, 2, value1, value2);
}

