#include "Lexer.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
	std::string fileString = "";

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

	// Fill fileString with chars from text
	while(textFile.peek() != EOF) {
//		std::cout << "peek(): " << textFile.peek() << std::endl;	// Debug
		fileString.push_back(textFile.get());
//		std::cout << "fileString: " << fileString << std::endl;		// Debug
	}


    Lexer* lexer = new Lexer();
    // TODO pass input to lexar and let it run


	// TODO print tokens from Lexar class in specified format


	// TODO dealocate memory

    delete lexer;

    return 0;
}