#ifndef __VENDING_MACHINE_H__
#define __VENDING_MACHINE_H__

#include "watcard.h"

// Forward Declarations
_Cormonitor Printer;
_Task NameServer;
class WATCard;

_Task VendingMachine {
    Printer& printer;
    NameServer &nameServer;
    const unsigned int ID;
    const unsigned int SODA_COST;
    const unsigned int MAX_STOCK_PER_FLAVOUR;

    unsigned int* stock;
    bool restocking;

    void main();
  public:
    enum Flavours { BLACKBERRY_CIDER = 0, BUBBLE_TEA = 1, SRI_RACHA = 2, COLD_CHOCOLATE = 3 };                 // flavours of soda (YOU DEFINE)
    enum Status { BUY, STOCK, FUNDS };     // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    ~VendingMachine();
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif
