#ifndef __PARENT_H__
#define __PARENT_H__

// Forward Declarations
_Cormonitor Printer;
_Monitor Bank;

// The Parent task periodically gives a random amount of money [$1, $3] to a random student. Before each gift
// is transfered, the parent yields for parentalDelay times (not random). The parent must check for a call to its
// destructor to know when to terminate. Since it must not block on this call, it is necessary to use a terminating
// Else on the accept statement. (Hence, the parent is busy waiting for the call to its destructor.)

_Task Parent {
    const unsigned int NUM_STUDENTS;
    const unsigned int PARENTAL_DELAY;

    Printer &printer;
    Bank &bank;

    void main();

  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif
