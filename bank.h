#ifndef __BANK_H__
#define __BANK_H__

// The Bank is a monitor, which behaves like a server, that manages student-account information for all students.
// Each student’s account initially starts with a balance of $0. The parent calls deposit to endow gifts to a speciﬁc
// student. A courier calls withdraw to transfer money on behalf of the WATCard ofﬁce for a speciﬁc student. The
// courier waits until enough money has been deposited, which may require multiple deposits.

_Monitor Bank {
  const unsigned int NUM_STUDENTS;

  unsigned int* balances;
  uCondition* sufficentBalance;

  public:
    Bank( unsigned int numStudents );
    ~Bank();
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif
