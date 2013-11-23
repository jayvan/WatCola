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
  //Randomly pick a favourite flavour
  VendingMachine::Flavours flavour = (VendingMachine::Flavours)prng(3);
  //Randomly pick a number of bottles to buy
  int numBottles = (prng() % MAX_PURCHASES) + 1;
  //Start message
  prt.print(Printer::Student, ID, 'S', (int)flavour, numBottles);

  //Create a new watcard
  WATCard::FWATCard fcard = cardOffice.create(ID, 5);
  //Get a vending machine from the name server
  VendingMachine* vm = nameServer.getMachine(ID);
  prt.print(Printer::Student, ID, 'V', vm->getId()); //Print vending machine id
  
  //While there are still bottles left to buy
  while(numBottles > 0) {
    //Wait a random amount of time before buying from a machine
    yield(prng(1, 10));
    //Keep trying to buy from the machine
    while (true) {
      try {
        //Attempt to buy from the machine
        VendingMachine::Status status = vm->buy(flavour, *fcard());
        if (status == VendingMachine::STOCK) { //If out of stock
          vm = nameServer.getMachine(ID); //Get a new machine
          prt.print(Printer::Student, ID, 'V', vm->getId()); //print its id
          break; //
        }
        else if (status == VendingMachine::FUNDS) { //If insufficient funds
          //Transfer 5 + the cost of soda on the WATCard
          fcard = cardOffice.transfer(ID, 5 + vm->cost(), fcard());
        }
        else { //If buying is successful
          //Print bought successful message with card's current balance
          prt.print(Printer::Student, ID, 'B', fcard()->getBalance());
          numBottles -= 1; //Decrement the number of bottles left to buy
          break; //
        }
      }
      catch(WATCardOffice::Lost) { //If the card is lost during the transaction
        prt.print(Printer::Student, ID, 'L'); //Print lost message
        fcard = cardOffice.create(ID, 5); //Create a new WATCard with a balance of $5
      }
    }
  }
  delete fcard(); //Destroy WATCard
  prt.print(Printer::Student, ID, 'F'); //Finish message
}

