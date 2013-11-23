#include "vendingmachine.h"
#include "watcard.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour) : 
  prt(prt), nameServer(nameServer), ID(id), SODA_COST(sodaCost), MAX_STOCK_PER_FLAVOUR(maxStockPerFlavour) {

}

void VendingMachine::main() { //TODO: Do this
  _Accept(~VendingMachine) { }
}

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ) { //TODO: Do this
  return STOCK;
}

unsigned int* VendingMachine::inventory() { //TODO: Do this
  return NULL;
}

void VendingMachine::restocked() { //TODO: Do this

}

unsigned int VendingMachine::cost() {
  return SODA_COST;
}

unsigned int VendingMachine::getId() {
  return ID;
}
