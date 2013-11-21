#ifndef __PRINTER_H__
#define __PRINTER_H__

_Cormonitor Printer {
  public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    ~Printer();
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
  private:
    const unsigned int NUM_STUDENTS;
    const unsigned int NUM_VENDING_MACHINES;
    const unsigned int NUM_COURIERS;
    const unsigned int NUM_STATES;

    char* states;
    int* firstValues;
    int* secondValues;
    char* filled;

    // communication variables
    unsigned int lid;
    char state;
    unsigned int value1;
    unsigned int value2;
    char values;

    void main();
    void flush();

    void doPrint(Kind kind, unsigned int lid, char state, char values, int value1, int value2);
};

#endif
