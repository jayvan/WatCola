#include "bottlingplant.h"
#include "MPRNG.h"
#include "truck.h"

extern MPRNG prng;

BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
    unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments) :
  prt(prt), nameServer(nameServer), NUM_VENDING_MACHINES(numVendingMachines), MAX_SHIPPED_PER_FLAVOUR(maxShippedPerFlavour),
  MAX_STOCK_PER_FLAVOUR(maxStockPerFlavour), TIME_BETWEEN_SHIPMENTS(timeBetweenShipments) {}

void BottlingPlant::main() { //TODO Do this
  Truck* truck = new Truck(prt, nameServer, *this, NUM_VENDING_MACHINES, MAX_STOCK_PER_FLAVOUR);
  yield(TIME_BETWEEN_SHIPMENTS);
}

bool BottlingPlant::getShipment(unsigned int cargo[]) { //TODO: Do this
  return true;
}
