#ifndef __NAME_SERVER_H__
#define __NAME_SERVER_H__

// Forward Declarations
_Cormonitor Printer;
_Task VendingMachine;

_Task NameServer {
    const unsigned int NUM_VENDING_MACHINES;
    const unsigned int NUM_STUDENTS;
    Printer &printer;

    unsigned int* assignments;
    VendingMachine** machines;

    unsigned int assignedMachines;

    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif
