#include "watcardoffice.h"
#include "watcard.h"
#include "printer.h"
#include "bank.h"
#include "MPRNG.h"

extern MPRNG prng;

WATCardOffice::WATCardOffice(Printer& prt, Bank& bank, unsigned int numCouriers) :
  NUM_COURIERS(numCouriers), printer(prt), bank(bank)
{
  closed = false;
  couriers = new WATCardOffice::Courier*[NUM_COURIERS];

  for(unsigned int i = 0; i < NUM_COURIERS; i++) {
    couriers[i] = new Courier(i, *this, printer, bank);
  }
}

WATCardOffice::~WATCardOffice() {
  closed = true;

  // Accept final requests for work
  while (true) {
    _Accept(requestWork) {

    } _Else {
      break;
    }
  }

  // Delete couriers
  for(unsigned int i = 0; i < NUM_COURIERS; i++) {
    delete couriers[i];
  }

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
  if (closed) {
    return NULL;
  }

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
  printer.print(Printer::Courier, ID, 'S');

  while (true) {
    // Get a job
    Job *job = office.requestWork();

    // If there are no more jobs then quit
    if (job == NULL) {
      break;
    }

    printer.print(Printer::Courier, ID, 't', job->sid, job->amount);
    bank.withdraw(job->sid, job->amount);
    printer.print(Printer::Courier, ID, 'T', job->sid, job->amount);

    job->card->deposit(job->amount);

    if (prng(5) == 0) {
      delete job->card;
      job->result.exception(new WATCardOffice::Lost());
    } else {
      job->result.delivery(job->card);
    }

    delete job;

    _Accept(WATCardOffice::~Courier) {
      break;
    } _Else {
    }
  }

  printer.print(Printer::Courier, ID, 'F');
}
