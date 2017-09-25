#include "lib/util.h"
#include "lib/parse_args.h"
#include "iostream"

int main(int argc, char* const* argv) {
  parse_args::InputArguments args = parse_args::ParseArgs(argc, argv);
  std::cout << args.max_error << '\n'
            << args.patterns.size() << '\n'
            << args.text_files.size() << '\n';

  return EXIT_SUCCESS;
}