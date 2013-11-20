#ifndef __STUDENT_H__
#define __STUDENT_H__

// Forward Declarations
_Cormonitor Printer;
_Task NameServer;
_Task WATCardOffice;

_Task Student {
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif
