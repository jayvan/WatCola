#include "student.h"
#include "MPRNG.h"
#include "vendingmachine.h"
#include "printer.h"
#include "nameserver.h"
#include "watcardoffice.h"

#include "uFuture.h"


extern MPRNG prng;

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
         unsigned int maxPurchases ) : prt(prt), nameServer(nameServer),
          cardOffice(cardOffice), id(id), maxPurchases(maxPurchases) {

}

void Student::main() {
  VendingMachine::Flavours flavour = (VendingMachine::Flavours)prng(3);
  int numBottles = (prng() % maxPurchases) + 1;
  prt.print(Printer::Student, id, 'S', (int)flavour, numBottles);

  WATCard::FWATCard fcard = cardOffice.create(id, 5);

  while(numBottles > 0) {
    VendingMachine* vm = nameServer.getMachine(id);
    prt.print(Printer::Student, id, 'V', vm->getId());

    //Buy from the vending maching
    yield(prng(1, 10));
    while (true) {
      try {
        VendingMachine::Status status = vm->buy(flavour, *fcard());
        if (status == VendingMachine::STOCK) { //out of stock
          break;
        }
        else if (VendingMachine::FUNDS) { //Insufficient funds
          fcard = cardOffice.transfer(id, 5 + vm->cost(), fcard());
        }
        else {
          prt.print(Printer::Student, id, 'B', fcard()->getBalance());
          numBottles -= 1;
          break;
        }
      }
      catch(WATCardOffice::Lost) {
        prt.print(Printer::Student, id, 'L');
        fcard = cardOffice.create(id, 5);
      }
    }
  }
  if (fcard() != NULL) delete fcard();
  prt.print(Printer::Student, id, 'F');
}

