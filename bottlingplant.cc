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
  _Accept(getShipment) { //Wait for the truck to get its final shipment
    delete truck;
  }
  prt.print(Printer::BottlingPlant, 'F'); //Print finish message
}

void BottlingPlant::main() {
  prt.print(Printer::BottlingPlant, 'S'); //Print start message
  //Create the truck
  truck = new Truck(prt, nameServer, *this, NUM_VENDING_MACHINES, MAX_STOCK_PER_FLAVOUR);
  
  while(true) {
    int total = 0; //Total number of bottles produced
    for (int i = 0; i < 4; ++i) {
      //Create a random amount of bottles for each flavour
      shipment[i] = prng(0, MAX_SHIPPED_PER_FLAVOUR);
      total += shipment[i]; //Add it to the totals
    }
    prt.print(Printer::BottlingPlant, 'G', total); //Print shipment message

    yield(TIME_BETWEEN_SHIPMENTS); //Wait the given time between shipments
    
    _Accept(~BottlingPlant) { //When the destructor is called
      closing = true; //notify the truck the the plant is closing
      break; //finish the main method
    } or _Accept(getShipment) { //Wait for the truck to get the shipment before producing another 
    }
  }
}

bool BottlingPlant::getShipment(unsigned int cargo[]) {
  if (!closing) { //if the plant is not closing
    prt.print(Printer::BottlingPlant, 'P'); //Print shipment message
    for (int i = 0; i < 4; ++i) { //Fill up the cargo 
      cargo[i] = shipment[i];
    }
  }
  return closing;
}
