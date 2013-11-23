#include "vendingmachine.h"
#include "nameserver.h"
#include "watcard.h"
#include "printer.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour) :
  printer(prt), nameServer(nameServer), ID(id), SODA_COST(sodaCost), MAX_STOCK_PER_FLAVOUR(maxStockPerFlavour)
{
  restocking = false;
  for (unsigned int i = 0; i < 4; i++) {
    stock[i] = 0;
  }
}

void VendingMachine::main() {
  // Print starting message
  printer.print(Printer::Vending, ID, 'S');

  // Register with the name server
  nameServer.VMregister(this);

  while (true) {
    _Accept(~VendingMachine) {
      break;
    } or _When(!restocking) _Accept(buy, inventory) {
    } or _Accept(restocked) {
      // Accept any time to detect incorrect behaviour rather than blocking mysteriously
    }
  }

  // Print finished message
  printer.print(Printer::Vending, ID, 'F');
}

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ) {
  if (stock[flavour] == 0) {
    return STOCK;
  } else if (card.getBalance() < SODA_COST) {
    return FUNDS;
  }

  card.withdraw(SODA_COST);
  stock[flavour]--;

  // Print that student bought a soda
  printer.print(Printer::Vending, ID, 'B', (unsigned int)flavour, stock[flavour]);

  return BUY;
}

unsigned int* VendingMachine::inventory() {
  restocking = true;

  // Print restocking message
  printer.print(Printer::Vending, ID, 'r');

  return stock;
}

void VendingMachine::restocked() { //TODO: Do this
  if (!restocking) {
    uAbort("Vending machine marked as restocked without ever starting stocking");
  }

  restocking = false;

  // Print restocked message
  printer.print(Printer::Vending, ID, 'R');
}

unsigned int VendingMachine::cost() {
  return SODA_COST;
}

unsigned int VendingMachine::getId() {
  return ID;
}
