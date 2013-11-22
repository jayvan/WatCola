#include "nameserver.h"
#include "vendingmachine.h"
#include "printer.h"

void NameServer::main() {
  // Print starting message
  printer.print(Printer::NameServer, 'S');

  while(true) {
    _Accept(~NameServer) {
      break;
    } or _When (assignedMachines >= NUM_VENDING_MACHINES) _Accept(getMachine, getMachineList) {
      // Don't let trucks or people access the list until all machines register
      // No upper bound limiting here because we'd rather hit the uAbort for
      // too many calls than have a task freeze mysteriously
    } or _Accept(VMregister) { }
  }

  // Print finishing message
  printer.print(Printer::NameServer, 'F');
}

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents) :
  NUM_VENDING_MACHINES(numVendingMachines), NUM_STUDENTS(numStudents), printer(prt)
{
  assignedMachines = 0;
  assignments = new unsigned int[NUM_STUDENTS];
  machines = new VendingMachine*[NUM_VENDING_MACHINES];

  // Distribute the students among the machines using round robin
  for (unsigned int i = 0; i < NUM_STUDENTS; i++) {
    assignments[i] = i % NUM_VENDING_MACHINES;
  }
}

NameServer::~NameServer() {
  delete[] assignments;
  delete[] machines;
}

// Assign the given vending machine to the next slot in the list of machines
void NameServer::VMregister(VendingMachine *vendingMachine) {
  if (assignedMachines >= NUM_VENDING_MACHINES) {
    uAbort("Registered too many vending machines");
  }

  printer.print(Printer::NameServer, 'R', vendingMachine->getId());
  machines[assignedMachines++] = vendingMachine;
}

// Give a student the next vending machine they should visit;
VendingMachine* NameServer::getMachine( unsigned int id ) {
  if (id < 0 || id >= NUM_STUDENTS) {
    uAbort("Invalid student ID given to getMachine");
  }

  printer.print(Printer::NameServer, 'N', id, assignments[id]);
  VendingMachine *nextMachine = machines[assignments[id]];

  // Advance the student to the next vending machine
  assignments[id] += 1;
  assignments[id] %= NUM_VENDING_MACHINES;

  return nextMachine;
}

VendingMachine** NameServer::getMachineList() {
  return machines;
}

