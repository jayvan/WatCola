#ifndef __BOTTLING_PLANT_H__
#define __BOTTLING_PLANT_H__

// Forward Declarations
_Task NameServer;
_Cormonitor Printer;

_Task BottlingPlant {
    void main();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    bool getShipment( unsigned int cargo[] );
};

#endif
