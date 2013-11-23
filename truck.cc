#include "truck.h"
#include "MPRNG.h"
#include "printer.h"
#include "nameserver.h"
#include "bottlingplant.h"
#include "vendingmachine.h"
#include <algorithm>

extern MPRNG prng;

Truck::Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour) :
  prt(prt), nameServer(nameServer), plant(plant), NUM_VENDING_MACHINES(numVendingMachines), MAX_STOCK_PER_FLAVOUR(maxStockPerFlavour) {}

void Truck::main() {
  prt.print(Printer::Truck, 'S');
  VendingMachine** machineList = nameServer.getMachineList();
  unsigned int* cargo = new unsigned int[4];

  while (true) {
    yield(prng(1,10));

    bool closing = plant.getShipment(cargo);
    if (closing) break;

    int total = 0;
    for (int i = 0; i < 4; ++i) {
      total += cargo[i];
    }
    prt.print(Printer::Truck, 'P', total);

    for (unsigned int i = 0; i < NUM_VENDING_MACHINES; ++i) {
      unsigned int* inventory = machineList[i]->inventory();
      int id = machineList[i]->getId();
      prt.print(Printer::Truck, 'd', id, total); 

      int unstocked = 0;
      for (int j = 0; j < 4; ++j) {
        int oldVal = inventory[i];
        inventory[j] = std::min(MAX_STOCK_PER_FLAVOUR, inventory[j] + cargo[j]);
        unstocked += MAX_STOCK_PER_FLAVOUR - inventory[j];
        int diff = inventory[j] - oldVal;
        cargo[j] -= diff;
        total -= diff;
      }

      if (unstocked > 0) {
        prt.print(Printer::Truck, 'U', id, unstocked);
      }
      prt.print(Printer::Truck, 'D', id, total);
      machineList[i]->restocked();
      
      if (total == 0) {
        break;
      }

    }
  }

  prt.print(Printer::Truck, 'F');
  delete[] cargo;
}
