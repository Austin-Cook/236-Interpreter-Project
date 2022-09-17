#include "Lexer.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
	std::string fileString = "";

	// Prep fileString ------------------------------------------------------------------
	// Verify num arguments
	if(argc != 2) {											// Should be 3 args (0) C:rest_of_path.exe (1) ./main (2) text_file_name.txt
		std::cerr << "Invalid number of arguments";
	}

	// Open file
	std::string fileName = argv[1];	//FIXME to run on Clion, this must be argv[2], otherwise argv[1]
	std::ifstream textFile(fileName);
	if(textFile.fail()) {
		std::cerr << "Failed";
	}

	/* Fill fileString with chars from text
	 * This does not read in EOF - actually it does (look at last line)
	 */

	if(!textFile.fail()) {	//Only if the file opened up
		while(textFile.peek() != EOF) {
			fileString.push_back(textFile.get());
		}
		fileString.push_back(EOF);	//FIXME this adds EOF to the end of my string but this might not be the right approach
	}

	// Pass input to lexer and run it --------------------------------------------------
    Lexer* lexer = new Lexer();
    lexer->Run(fileString);


	// Print tokens from Lexar class in specified format
	lexer->printTokens();

	// Dealocate memory
    delete lexer;

    return 0;
}