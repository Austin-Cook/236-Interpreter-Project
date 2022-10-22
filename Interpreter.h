//
// Created by austi_eef6ewn on 10/20/2022.
//

#ifndef PROJECT1_STARTER_CODE_INTERPRETER_H
#define PROJECT1_STARTER_CODE_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
public:
	Interpreter(DatalogProgram datalogProgram);
private:
	Database database;
};


#endif //PROJECT1_STARTER_CODE_INTERPRETER_H
