#include "main.h"

int main(int argc, char* argv[]) {
    assert(argc == 3 && BAD_PROGRAM_ARGUMENT);
    Algo Early(argv[1]);
    std::string word = argv[2];
    if (Early.predict(word)) {
        std::cout << WORD_BELONG << std::endl;
    } else {
        std::cout << WORD_NOTBELONG << std::endl;
    }
    return 0;
}