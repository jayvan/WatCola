#ifndef __TRUCK_H__
#define __TRUCK_H__

// Forward Declarations
_Cormonitor Printer;
_Task NameServer;
_Task BottlingPlant;

_Task Truck {
    Printer &prt;
    NameServer &nameServer;
    BottlingPlant &plant;
    const unsigned int NUM_VENDING_MACHINES;
    const unsigned int MAX_STOCK_PER_FLAVOUR;

    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif
