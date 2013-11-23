#include "bottlingplant.h"
#include "MPRNG.h"
#include "printer.h"
#include "truck.h"

extern MPRNG prng;

BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
    unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments) :
  prt(prt), nameServer(nameServer), NUM_VENDING_MACHINES(numVendingMachines), MAX_SHIPPED_PER_FLAVOUR(maxShippedPerFlavour),
  MAX_STOCK_PER_FLAVOUR(maxStockPerFlavour), TIME_BETWEEN_SHIPMENTS(timeBetweenShipments), closing(false) {
}

BottlingPlant::~BottlingPlant() {
  _Accept(getShipment) {
    delete truck;
  }
  prt.print(Printer::BottlingPlant, 'F');
}

void BottlingPlant::main() {
  prt.print(Printer::BottlingPlant, 'S');
  truck = new Truck(prt, nameServer, *this, NUM_VENDING_MACHINES, MAX_STOCK_PER_FLAVOUR);
  
  while(true) {
    shipment = prng(0, MAX_SHIPPED_PER_FLAVOUR);
    prt.print(Printer::BottlingPlant, 'G', shipment);

    yield(TIME_BETWEEN_SHIPMENTS);
    
    _Accept(~BottlingPlant) {
      closing = true;
      break;
    } or _Accept(getShipment) {
    }
  }
}

bool BottlingPlant::getShipment(unsigned int cargo[]) {
  if (!closing) {
    for (int i = 0; i < 4; ++i) {
      prt.print(Printer::BottlingPlant, 'P');
      cargo[i] = shipment;
    }
  }
  return closing;
}
