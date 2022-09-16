#include "Lexer.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
	std::string fileString = "";

	//Test code for Token
//	Token myComma(TokenType::COMMA, "This is a comma", 5);
//	Token myAdd(TokenType::ADD, "+", 7);
//	myComma.toString();
//	myAdd.toString();

	// Prep fileString ------------------------------------------------------------------
	// Prints Argc and Argv values
//	std::cout << "argc: " << argc << std::endl;		// Debug
//		for(int i = 0; i < argc; i++) {
//			std::cout << i << ": " << argv[i] << std::endl;
//		}

	// Verify num arguments
	if(argc != 3) {											// Should be 3 args (0) C:rest_of_path.exe (1) ./main (2) text_file_name.txt
		std::cerr << "Invalid number of arguments";
	}

	// Open file
	std::string fileName = argv[2];
//	std::cout << "fileName being read in: " << fileName << std::endl;		// Debug
	std::ifstream textFile(fileName);
	if(textFile.fail()) {
		std::cerr << "Failed";
	}

	/* Fill fileString with chars from text
	 * This does not read in EOF
	 */
	while(textFile.peek() != EOF) {
//		std::cout << "peek(): " << textFile.peek() << std::endl;	// Debug
		fileString.push_back(textFile.get());
//		std::cout << "fileString: " << fileString << std::endl;		// Debug
	}
	fileString.push_back(EOF);	//FIXME this adds EOF to the end of my string but this might not be the right approach

	// Pass input to lexar and run it --------------------------------------------------
    Lexer* lexer = new Lexer();
    lexer->Run(fileString);


	// TODO print tokens from Lexar class in specified format
	lexer->printTokens();

	// Dealocate memory
    delete lexer;

    return 0;
}