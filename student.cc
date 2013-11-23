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
          cardOffice(cardOffice), ID(id), MAX_PURCHASES(maxPurchases) {

}

void Student::main() {
  VendingMachine::Flavours flavour = (VendingMachine::Flavours)prng(3);
  int numBottles = (prng() % MAX_PURCHASES) + 1;
  prt.print(Printer::Student, ID, 'S', (int)flavour, numBottles);

  WATCard::FWATCard fcard = cardOffice.create(ID, 5);
  VendingMachine* vm = nameServer.getMachine(ID);
  prt.print(Printer::Student, ID, 'V', vm->getId());
  
  while(numBottles > 0) {
    //Buy from the vending maching
    yield(prng(1, 10));
    while (true) {
      try {
        VendingMachine::Status status = vm->buy(flavour, *fcard());
        if (status == VendingMachine::STOCK) { //out of stock
          vm = nameServer.getMachine(ID);
          prt.print(Printer::Student, ID, 'V', vm->getId());
          break;
        }
        else if (VendingMachine::FUNDS) { //Insufficient funds
          fcard = cardOffice.transfer(ID, 5 + vm->cost(), fcard());
        }
        else {
          prt.print(Printer::Student, ID, 'B', fcard()->getBalance());
          numBottles -= 1;
          break;
        }
      }
      catch(WATCardOffice::Lost) {
        prt.print(Printer::Student, ID, 'L');
        fcard = cardOffice.create(ID, 5);
      }
    }
  }
  delete fcard();
  prt.print(Printer::Student, ID, 'F');
}

