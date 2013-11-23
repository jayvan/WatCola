#ifndef __BOTTLING_PLANT_H__
#define __BOTTLING_PLANT_H__

// Forward Declarations
_Task NameServer;
_Cormonitor Printer;

_Task BottlingPlant {
    Printer &prt;
    NameServer &nameServer;
    const unsigned int NUM_VENDING_MACHINES;
    const unsigned int MAX_SHIPPED_PER_FLAVOUR;
    const unsigned int MAX_STOCK_PER_FLAVOUR;
    const unsigned int TIME_BETWEEN_SHIPMENTS; 

    void main();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    bool getShipment( unsigned int cargo[] );
};

#endif
