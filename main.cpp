#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <iostream>
#include <fstream>

#include "Database.h"	// Only for testing
#include "Graph.h"		// Only for testing

enum mode {
	RUN = 0,
	TEST = 1
};

int main(int argc, char** argv) {
	mode currentMode = RUN;

	if(currentMode == RUN) {
		std::string fileString = "";

		// Prep fileString ------------------------------------------------------------------
		// Verify num arguments
		if(argc != 3) {		//FIXME Lab Machines - 2 args, CLion - 3 args :: (0) C:rest_of_path.exe (1) ./main (2) text_file_name.txt
			std::cerr << "Invalid number of arguments" << std::endl;
		}

		// Open file
		std::string fileName = argv[2];	//FIXME Lab Machines - argv[1], Clion - argv[2]
		std::ifstream textFile(fileName);
		if(textFile.fail()) {
			std::cerr << "Failed";
		}

		/* Fill fileString with chars from text
		 * This does not read in EOF - it pushes it on the end
		 */
		if(!textFile.fail()) {	//Only if the file opened up
			while(textFile.peek() != EOF) {
				fileString.push_back(textFile.get());
			}
			fileString.push_back(EOF);
		}

		// PROJECT 1
		// Pass input to lexer and run it --------------------------------------------------
		Lexer* lexer = new Lexer();
		lexer->Run(fileString);

		// Print tokens from Lexer class in specified format
//		lexer->printTokens();

		// PROJECT 2 - run ParseDatalogProgram function with tokenVector
		Parser parser(lexer->getTokenVector());
		try {
			parser.ParseDatalogProgram();
//			std::cout << "Success!" << std::endl;		// Project 2 Standard Output
//			parser.PrintDatalog();
		} catch(std::string error) {
			std::cout << "Failure!" << std::endl;
			std::cout << "  " << error;
		}

		// PROJECT 3 4, and 5 - Pass DatalogProgram object into a new Interpreter to create the Relations
		Interpreter interpreter(parser.getDatalog());

//		// DELETEME
//		Graph optimizationDependencyGraphs(parser.getDatalog().getRuleVector());
//		std::vector<std::set<int>> SCCs = optimizationDependencyGraphs.getSCCs();

		// Deallocate memory
		delete lexer;
	} else {
		Database database;
		database.testDatabaseClasses();
	}

    return 0;
}