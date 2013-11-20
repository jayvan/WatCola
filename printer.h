#ifndef __PRINTER_H__
#define __PRINTER_H__

_Cormonitor Printer {
  const unsigned int NUM_STUDENTS;
  const unsigned int NUM_VENDING_MACHINES;
  const unsigned int NUM_COURIERS;

  char* states;
  int* firstValues;
  int* secondValues;
  bool* filled;

  // communication variables
  unsigned int lid;
  char state;
  unsigned int value1;
  unsigned int value2;

  void main();
  void flush();

  public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
};

#endif
