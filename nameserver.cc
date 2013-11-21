#include "nameserver.h"
#include "vendingmachine.h"

void NameServer::main();
    
NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );

void NameServer::VMregister( VendingMachine *vendingmachine );

VendingMachine* NameServer::getMachine( unsigned int id ) { //TODO: Do this
  return NULL;
}

VendingMachine** NameServer::getMachineList() { //TODO: Do this
  return NULL;
}
