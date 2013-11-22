#include "MPRNG.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "watcardoffice.h"
#include "nameserver.h"
#include "vendingmachine.h"
#include "config.h"
#include <iostream>

using namespace std;

MPRNG prng;

void usage(char* argv[]) {
  cout << "usage: " <<  argv[0] << " [ conﬁg-ﬁle [ random-seed > 0 ] ]" << endl;
  exit(1);
}

void uMain::main() {
  // Default values
  prng.seed(getpid());
  char* configPath = (char*)"soda.config";

  // Overload defaults from command line arguments
  switch (argc) {
    case 3:
      if (atoi(argv[2]) <= 0) {
        usage(argv);
      }
      prng.seed(atoi(argv[2]));
    case 2:
      configPath = argv[1];
  }

  // Process configuration file
  ConfigParms params;
  processConfigFile(configPath, params);

  // Create in order: printer, bank, parent, WATCard office, name server, vending machines, bottling plant, and students.
  Printer printer(params.numStudents, params.numVendingMachines, params.numCouriers);
  Bank bank(params.numStudents);
  Parent parent(printer, bank, params.numStudents, params.parentalDelay);
  WATCardOffice office(printer, bank, params.numCouriers);
  NameServer nameServer(printer, params.numVendingMachines, params.numStudents);
  VendingMachine* machines[params.numVendingMachines];

  // Create vending machines
  for (unsigned int i = 0; i < params.numVendingMachines; i++) {
    machines[i] = new VendingMachine(printer, nameServer, i, params.sodaCost, params.maxStockPerFlavour);
  }

  for (unsigned int i = 0; i < params.numVendingMachines; i++) {
    delete machines[i];
  }

}
