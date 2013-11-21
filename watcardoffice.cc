#include "watcardoffice.h"
#include "watcard.h"
#include "printer.h"
#include "bank.h"
#include "MPRNG.h"

extern MPRNG prng;

WATCardOffice::WATCardOffice(Printer& prt, Bank& bank, unsigned int numCouriers) :
  NUM_COURIERS(numCouriers), printer(prt), bank(bank) {
  couriers = new WATCardOffice::Courier*[NUM_COURIERS];

}

WATCardOffice::~WATCardOffice() {
  delete[] couriers;
}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount) {
  WATCard::FWATCard newCard;
  WATCard* card = new WATCard();
  jobs.push(new Job(card, sid, amount, newCard));
  printer.print(Printer::WATCardOffice, 'C', sid, amount);
  return newCard;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
  WATCard::FWATCard newCard;
  jobs.push(new Job(card, sid, amount, newCard));
  printer.print(Printer::WATCardOffice, 'T', sid, amount);
  return newCard;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
  Job* nextJob = jobs.front();
  jobs.pop();
  return nextJob;
}

void WATCardOffice::main() {
  printer.print(Printer::WATCardOffice, 'S');
  while(true) {
    _Accept(~WATCardOffice) {
      break;
    } or _When(jobs.size() > 0) _Accept(requestWork) {
      printer.print(Printer::WATCardOffice, 'W');
    } or _Accept(transfer, create) { }
  }
  printer.print(Printer::WATCardOffice, 'F');
}


void WATCardOffice::Courier::main() {
  while (true) {
    // Get a job
    Job *job = office.requestWork();

    bank.withdraw(job->sid, job->amount);
    job->card->deposit(job->amount);

    if (prng(5) == 0) {
      delete card;
      job->result.exception(WATCardOffice::Lost());
    } else {
      job->result.delivery(job->card);
    }

    delete job;

    _Accept(~WATCardOffice::Courier) {
      break;
    } _Else {
    }
  }
}
