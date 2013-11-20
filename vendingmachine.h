#ifndef __VENDING_MACHINE_H__
#define __VENDING_MACHINE_H__

// Forward Declarations
_Cormonitor Printer;
_Task NameServer;
Class WATCard;

_Task VendingMachine {
    void main();
  public:
    enum Flavours { ... };                 // flavours of soda (YOU DEFINE)
    enum Status { BUY, STOCK, FUNDS };     // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif
