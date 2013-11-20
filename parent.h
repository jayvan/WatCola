#ifndef __PARENT_H__
#define __PARENT_H__

// Forward Declarations
_Cormonitor Printer;
_Monitor Bank;

_Task Parent {
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif
