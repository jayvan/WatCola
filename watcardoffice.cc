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
  // Mark the office as closed so requestWork knows to return NULL jobs
  closed = true;

  // Accept final requests for work, give the couriers NULL jobs
  for (unsigned int i = 0; i < NUM_COURIERS; i++) {
    _Accept(requestWork) {
    }
  }

  // Delete couriers
  for(unsigned int i = 0; i < NUM_COURIERS; i++) {
    delete couriers[i];
  }

  delete[] couriers;

  // Print that we're done
  printer.print(Printer::WATCardOffice, 'F');
}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount) {
  WATCard::FWATCard newCard;

  // Create a new Watcard
  WATCard* card = new WATCard();

  // Schedule a courier to load the card
  jobs.push(new Job(card, sid, amount, newCard));

  // Print that the task is queued
  printer.print(Printer::WATCardOffice, 'C', sid, amount);

  return newCard;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
  WATCard::FWATCard newCard;
  // Schedule a courier to load the card
  jobs.push(new Job(card, sid, amount, newCard));

  // Print that the task is queued
  printer.print(Printer::WATCardOffice, 'T', sid, amount);

  return newCard;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
  // If the office is closed return NULL
  if (closed) {
    return NULL;
  }

  // Get the next job
  Job* nextJob = jobs.front();
  jobs.pop();
  return nextJob;
}

void WATCardOffice::main() {
  // Print that we're starting
  printer.print(Printer::WATCardOffice, 'S');

  while(true) {
    _Accept(~WATCardOffice) {
      break;
    } or _When(jobs.size() > 0) _Accept(requestWork) {
      // Print that we've given a job
      printer.print(Printer::WATCardOffice, 'W');
    } or _Accept(transfer, create) { }
  }

}


void WATCardOffice::Courier::main() {
  // Print that we're starting
  printer.print(Printer::Courier, ID, 'S');

  while (true) {
    // Get a job
    Job *job = office.requestWork();

    // If there are no more jobs then quit
    if (job == NULL) {
      break;
    }

    // Print that we're fetching funds
    printer.print(Printer::Courier, ID, 't', job->sid, job->amount);

    // Get the funds
    bank.withdraw(job->sid, job->amount);

    // Print that we've got the funds
    printer.print(Printer::Courier, ID, 'T', job->sid, job->amount);

    // Deposit the funds
    job->card->deposit(job->amount);

    // Lose the watcard with probability 1 in 6
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

  // Print that we're done
  printer.print(Printer::Courier, ID, 'F');
}
