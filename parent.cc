#include "parent.h"
#include "bank.h"
#include "printer.h"
#include "MPRNG.h"

extern MPRNG prng;

Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay) :
  NUM_STUDENTS(numStudents), PARENTAL_DELAY(parentalDelay), printer(prt), bank(bank) {

}

void Parent::main() {
  // Print that we're starting
  printer.print(Printer::Parent, 'S');

  while(true) {
    // Give between 1 and 3 dollars
    unsigned int amount = prng(1,3);

    // Give to a random student
    unsigned int bankAccount = prng(NUM_STUDENTS - 1);

    // Yield PARENTAL_DELAY times
    yield(PARENTAL_DELAY);

    // Give the money
    printer.print(Printer::Parent, 'D', bankAccount, amount);
    bank.deposit(bankAccount, amount);

    // Accept destructor
    _Accept(~Parent) {
      break;
    } _Else {
      // Continue Happily
    }
  }

  // Print finished state
  printer.print(Printer::Parent, 'F');
}
