#include "huffman.hpp"

int main(int argc, char* argv[]) {
    std::vector<std::string> my_argv(argc);
    for (int i = 0; i < argc; ++i) {
        my_argv[i] = std::string(argv[i]);
    }
    if ((argc < 4) || ((argc == 5) && (my_argv[1] != "-v"))) {
        std::cout << "wrong args" << std::endl;
        return 0;
    }
    bool flag_v = (argc == 5) ? (my_argv[1] == "-v") : (false);
    bool flag_c_d = (argc == 5) ? (my_argv[2] == "-c") : (my_argv[1] == "-c");
    run_coding_or_decoding(my_argv[argc - 2], my_argv[argc - 1], flag_v, flag_c_d);
    return 0;
}

