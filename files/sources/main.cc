#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

bool hasConvccExtension(const std::string& filename) {
    const std::string extension = ".convcc";
    if (filename.length() >= extension.length()) {
        return (0 == filename.compare(filename.length() - extension.length(), extension.length(), extension));
    }
    return false;
}

int main(int argc, char* argv[]) {

    /* Parsing Arguments */

    // At least 2 arguments
    if (argc < 3) {
        std::cerr << "\033[1mconvcc: \033[31mfatal error:\033[0m no input files" << std::endl;
        std::cerr << "compilation terminated." << std::endl;
        return -1;
    }

    // Checking args
    std::string filename;
    std::string output_file;

    for (int i = 1; i < argc; i++){
        std::string arg = argv[i];
        
        // FILENAME
        if (arg == "-f") {
            if (i + 1 < argc) {
                filename = argv[++i];
            } else {
                std::cerr << "\033[1mconvcc: \033[31merror:\033[0m -f flag requires a filename." << std::endl;
                std::cerr << "Usage: " << argv[0] << " -f filename [-o output]" << std::endl;
                std::cerr << "compilation terminated." << std::endl;
                return -1;
            }
        // OUTPUT FILENAME
        } else if (arg == "-o") {
            if (i + 1 < argc) {
                output_file = argv[++i];
            } else {
                std::cerr << "\033[1mconvcc: \033[31merror:\033[0m -o flag requires a filename." << std::endl;
                std::cerr << "Usage: " << argv[0] << " -f filename [-o output]" << std::endl;
                std::cerr << "compilation terminated." << std::endl;
                return -1;
            }
        // Add other args with else if (best choice for now)
        } else {
            std::cerr << "\033[1mconvcc: \033[31merror:\033[0m unknown argument `" << argv[i] << "`" << std::endl;
            std::cerr << "Usage: " << argv[0] << " -f filename [-o output]" << std::endl;
            std::cerr << "compilation terminated." << std::endl;
            return -1;
        }
    }

    // When no input file but has output file
    if (filename.empty()) {
        std::cerr << "\033[1mconvcc: \033[31mfatal error:\033[0m no input files" << std::endl;
        std::cerr << "compilation terminated." << std::endl;
        return -1;
    }

    // Cheking file extension
    if (!hasConvccExtension(filename)){
        std::cerr << "\033[1mconvcc: \033[31mfatal error:\033[0m invalid file format" << std::endl;
        std::cerr << "must be a '.convcc' file" << std::endl;
        std::cerr << "compilation terminated." << std::endl;
        return -1;
    }

    // In case file do not exist
    std::ifstream file(filename);
    if (!file){
        std::cerr << "\033[1mconvcc: \033[31mfatal error: \033[0mno no such file or directory '" << filename << "'" << std::endl;
        std::cerr << "compilation terminated." << std::endl;
        return -1;
    }

    // File to string
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string input = buffer.str();
    std::cout << input << std::endl;
    
    // Compiler will compile input

    // Close the file
    file.close();
}