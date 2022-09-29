#include "Lexer.h"
#include "Parser.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
	std::string fileString = "";

	// Prep fileString ------------------------------------------------------------------
	// Verify num arguments
	if(argc != 3) {		//CLion - should be 3 args (0) C:rest_of_path.exe (1) ./main (2) text_file_name.txt
		std::cerr << "Invalid number of arguments";
	}

	// Open file
	std::string fileName = argv[2];	//FIXME to run on Clion, this must be argv[2], otherwise argv[1]
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

	// Pass input to lexer and run it --------------------------------------------------
    Lexer* lexer = new Lexer();
    lexer->Run(fileString);


	// Print tokens from Lexar class in specified format
	//lexer->printTokens();

	// PROJECT 2 - Delete Comments (The Parser is set up to automatically ignore tokens, so this is not needed)
	//lexer->RemoveCommentTokens();

	// PROJECT 2 - run ParseDatalogProgram function with tokenVector
	Parser parser(lexer->getTokenVector());
	try {
		parser.ParseDatalogProgram();
		std::cout << "Success!" << std::endl;
		parser.PrintDatalog();
	} catch(std::string error) {
		std::cout << "Failure!" << std::endl;
		std::cout << "  " << error << std::endl;
	}


	// Dealocate memory
//    delete lexer;

    return 0;
}