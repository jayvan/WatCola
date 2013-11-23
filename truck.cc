#include "truck.h"
#include "MPRNG.h"
#include "printer.h"
#include "nameserver.h"
#include "bottlingplant.h"
#include "vendingmachine.h"

extern MPRNG prng;

Truck::Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour) :
  prt(prt), nameServer(nameServer), plant(plant), NUM_VENDING_MACHINES(numVendingMachines), MAX_STOCK_PER_FLAVOUR(maxStockPerFlavour) {}

void Truck::main() {
  unsigned int* cargo = new unsigned int[NUM_VENDING_MACHINES];

  while (true) {
    //VendingMachine** machineList = nameServer.getMachineList();

    yield(prng(1,10));
    bool closing = plant.getShipment(cargo);

    if (closing) break;

    for (unsigned int i = 0; i < NUM_VENDING_MACHINES; ++i) {
      //unsigned int* inv = machineList[i]->inventory();
      for (int j = 0; j < 4; ++j) {

      }
    }
  }

  delete[] cargo;
}
