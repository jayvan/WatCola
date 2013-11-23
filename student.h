#ifndef __STUDENT_H__
#define __STUDENT_H__

// Forward Declarations
_Cormonitor Printer;
_Task NameServer;
_Task WATCardOffice;

_Task Student {
    Printer &prt;
    NameServer &nameServer;
    WATCardOffice &cardOffice;
    const unsigned int ID;
    const unsigned int MAX_PURCHASES;

    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif
