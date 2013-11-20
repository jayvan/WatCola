#ifndef __TRUCK_H__
#define __TRUCK_H__

// Forward Declarations
_Cormonitor Printer;
_Task NameServer;
_Task BottlingPlant;

_Task Truck {
    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif
