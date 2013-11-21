#include "vendingmachine.h"
#include "watcard.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour) : 
  prt(prt), nameServer(nameServer), id(id), sodaCost(sodaCost), maxStockPerFlavour(maxStockPerFlavour) {

}

void VendingMachine::main() { //TODO: Do this

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
  return sodaCost;
}

unsigned int VendingMachine::getId() {
  return id;
}
