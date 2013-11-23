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
  prt.print(Printer::Truck, 'S'); //Print starting message 
  //Get the vending machine list from the name server
  VendingMachine** machineList = nameServer.getMachineList();
  unsigned int* cargo = new unsigned int[4]; //Create an array to store cargo for each flavour

  //While there are shipments to perform
  while (true) {
    yield(prng(1,10)); //Go to Tim Hortons

    bool closing = plant.getShipment(cargo); //Get the shipment from the plant
    if (closing) break; //If the plant is closing, then stop all deliveries

    int total = 0;
    for (int i = 0; i < 4; ++i) {
      total += cargo[i]; //Add up the total number bottles in the shipment
    }
    prt.print(Printer::Truck, 'P', total); //Print the number of bottles being shipped

    // If the plant hasn't produced any bottles, request a new batch
    if (total == 0) {
      continue;
    }

    //For each vending machine
    for (unsigned int i = 0; i < NUM_VENDING_MACHINES; ++i) {
      //Get the inventory from the current vending machine
      unsigned int* inventory = machineList[i]->inventory();

      //Get the id from the current machine
      int id = machineList[i]->getId();
      //Print the delivery at the current vending machine
      prt.print(Printer::Truck, 'd', id, total);
      
      //number of slots in the machine that are unfilled at the end of the delivery
      int unstocked = 0; 
      for (int j = 0; j < 4; ++j) { //For each flavour
        int beforeStock = inventory[j]; //Number of bottles before stocking
        //Fill the slot up to the maximum stock per flavour
        inventory[j] = std::min(MAX_STOCK_PER_FLAVOUR, inventory[j] + cargo[j]);
        //Add up the number of unfilled slots
        unstocked += MAX_STOCK_PER_FLAVOUR - inventory[j];
        //Get the number of bottles that were stocked
        int diff = inventory[j] - beforeStock;
        //Subtract the difference off the cargo and the total sum of bottles
        cargo[j] -= diff;
        total -= diff;
      }

      if (unstocked > 0) { //If there are slots unstocked
        //Print the unstocked message with the number of unstocked slots
        prt.print(Printer::Truck, 'U', id, unstocked);
      }
      //Print a finished delivery message
      prt.print(Printer::Truck, 'D', id, total);
      machineList[i]->restocked(); //indicate to the machine that the restocking is finished

      if (total == 0) { //If the truck has no more bottles
        break; //End the delivery cycle
      }
    }
  }

  prt.print(Printer::Truck, 'F'); //Print finished message
  delete[] cargo;
}
