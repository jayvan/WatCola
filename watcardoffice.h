#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include <queue>
#include "watcard.h"

// Forward declarations
_Monitor Bank;
_Cormonitor Printer;

_Task WATCardOffice {
    struct Job {                           // marshalled arguments and return future
        WATCard* card;        // Card to load
        unsigned int sid;     // Student to debit
        unsigned int amount;  // Amount to debit
        WATCard::FWATCard result;                   // return future

        Job(WATCard* card, unsigned int sid, unsigned int amount, WATCard::FWATCard result) :
          card(card), sid(sid), amount(amount), result(result) {}
    };

    _Task Courier {

      public:
        void main();
    };

    const unsigned int NUM_COURIERS;
    Printer& printer;
    Bank& bank;
    Courier *couriers;
    std::queue<Job*> jobs;

    void main();
  public:
    _Event Lost {};                        // uC++ exception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif
