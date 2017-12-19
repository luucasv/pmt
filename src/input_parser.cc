/*
Copyright (c) 2017 Lucas V. da C. Santana and Tiago Figueiredo Gonçalves

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Written by: Lucas V. da C. Santana <lvcs@cin.ufpe.br>
            Tiago Figueiredo Gonçalves <tfg@cin.ufpe.br>
*/


#include "input_parser.h"

#include <sys/stat.h>
#include <getopt.h>
#include <stdio.h>

#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>

#include "resources.h"
#include "algorithm.h"
#include "util.h"

using std::vector;
using std::string;

namespace input_parser {

InputArguments::InputArguments() {
  max_error = 0;
  count_flag = false;
  algorithm = algorithm::NO_ALGORITHM;
}

// show usage message
void ShowUsage(const char *base) {
  printf(USAGE_MESSAGE, base, base, base, base);
}

// show help message
void ShowHelp(const char *base) {
  ShowUsage(base);
  printf(HELP_MESSAGE, base);
}

void ShowVersion() {
  puts(VERSION_MESSAGE);
}

std::ostream& operator<< (std::ostream& out,
                          const std::vector<std::string>& v) {
  out << "[";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (i > 0) {
      out << ", ";
    }
    out << '\'' << v[i] << '\'';
  }
  out << ']';
  return out;
}

std::ostream& operator<< (std::ostream& out,
                          algorithm::AlgorithmEnum algorithm) {
  if (algorithm == algorithm::KMP) {
    out << "KMP";
  } else if (algorithm == algorithm::AHO_CORASICK) {
    out << "AHO_CORASICK";
  } else if (algorithm == algorithm::SHIFT_OR) {
    out << "SHIFT_OR";
  } else if (algorithm == algorithm::SHIFT_OR_64) {
    out << "SHIFT_OR_64";
  } else if (algorithm == algorithm::UKKONEN) {
    out << "UKKONEN";
  } else if (algorithm == algorithm::NAIVE) {
    out << "NAIVE";
  } else if (algorithm == algorithm::SELLERS) {
    out << "SELLERS";
  } else if (algorithm == algorithm::WU_MANBER) {
    out << "WU_MANBER";
  } else if (algorithm == algorithm::WU_MANBER_64) {
    out << "WU_MANBER_64";
  } else if (algorithm == algorithm::BOYER_MOORE) {
    out << "BOYER_MOORE";
  }
  return out;
}


void ShowArgs(const InputArguments &args) {
  std::cout << "For debbug: \nArguments:\n";
  std::cout << "max_error  = " << args.max_error << '\n'
            << "patterns   = " << args.patterns << '\n'
            << "text_files = " << args.text_files << '\n'
            << "algorithm  = " << args.algorithm << '\n';
}

// read all patters in file_name (one per line) and push into patterns vector
bool ReadPatterns(vector<string> *patterns, const char *file_name) {
  std::ifstream file(file_name);
  if (!file.good()) {
    return false;
  }
  string pattern;
  while (std::getline(file, pattern)) {
    (*patterns).push_back(pattern);
  }
  return true;
}

const char * IS_FILE_MSG[] = {"Is a directory", "No such file or directory"};

// Returns the message to be showed if file_name is not a file,
// if file_name is a file returns NULL
inline const char* GetFileMessage(const char *file_name) {
  struct stat buffer;
  if (stat(file_name, &buffer) == 0) {
    if (buffer.st_mode & S_IFDIR) {
      return IS_FILE_MSG[0];
    } else if (buffer.st_mode & S_IFREG) {
      return NULL;
    }
  }
  return IS_FILE_MSG[1];
}

InputArguments ParseArgs(int argc, char * const*argv) {
  // Return variable, already set to its default values
  InputArguments args;

  // ===================== parsing options ==============================
  // defining valid options
  const char short_options[] = ":e:p:a:chv";
  const struct option long_options[] = {
    {"edit",      required_argument, nullptr, 'e' },
    {"pattern",   required_argument, nullptr, 'p' },
    {"algorithm", required_argument, nullptr, 'a' },
    {"count",     no_argument,       nullptr, 'c' },
    {"help",      no_argument,       nullptr, 'h' },
    {"version",   no_argument,       nullptr, 'v' },
    {nullptr,     no_argument,       nullptr,  0  }
  };
  while (true) {
    int current_option = getopt_long(argc, argv, short_options,
                                     long_options, NULL);
    if (current_option == -1) {
      break;
    }

    switch (current_option) {
      case 'e': {
        bool is_num;
        std::tie(is_num, args.max_error) = util::StringToInt(optarg);
        if (!is_num || args.max_error < 0) {
          std::cerr << argv[0] << ": " << optarg
                    << ": Invalid max_error value\n";
          exit(EXIT_FAILURE);
        }
        break;
      }
      case 'p': {
        bool file_exits = ReadPatterns(&args.patterns, optarg);
        if (!file_exits) {
          std::cerr << argv[0] << ": " << optarg
                    << ": " << GetFileMessage(optarg) << '\n';
          exit(EXIT_FAILURE);
        }
        break;
      }
      case 'a': {
        args.algorithm = algorithm::GetAlgorithmEnum(optarg);
        if (args.algorithm == algorithm::NO_ALGORITHM) {
          std::cerr << argv[0] << ": " << optarg
                    << ": Invalid algorithm name\n";
          exit(EXIT_FAILURE);
        }
        break;
      }
      case 'c': {
        args.count_flag = true;
        break;
      }
      case 'h': {
        ShowHelp(argv[0]);
        exit(EXIT_SUCCESS);
        break;
      }
      case 'v': {
        ShowVersion();
        exit(EXIT_SUCCESS);
        break;
      }
      case ':': {
        std::cerr << argv[0] << ": " << argv[optind - 1]
                  << ": Missing argument.\n";
        ShowUsage(argv[0]);
        exit(EXIT_FAILURE);
        break;
      }
      case '?': {
        std::cerr << argv[0] << ": " << argv[optind - 1]
                  << ": Invalid option.\n";
        ShowUsage(argv[0]);
        exit(EXIT_FAILURE);
        break;
      }
      default: {
        std::cerr << argv[0] << ":  Internal error while parsing arguments\n";
        ShowUsage(argv[0]);
        exit(EXIT_FAILURE);
        break;
      }
    }
  }

  // ===================== getting text_files ==============================
  // pattern is needed only there are no pattern files
  if (args.patterns.empty()) {
    if (optind >= argc) {
      std::cerr << argv[0] << ": Missing pattern argument\n";
      ShowUsage(argv[0]);
      exit(EXIT_FAILURE);
    } else {
      args.patterns.push_back(argv[optind]);
      optind++;
    }
  }

  // ===================== reading text_files ==============================
  while (optind < argc) {
    const char *msg = GetFileMessage(argv[optind]);
    if (msg != NULL) {
      std::cerr << argv[0] << ": " << argv[optind] << ": " << msg << '\n';
      exit(EXIT_FAILURE);
    } else {
      args.text_files.emplace_back(argv[optind]);
    }
    optind++;
  }
  if (args.text_files.empty()) {
    std::cerr << argv[0] << ": Missing textfile argument\n";
    ShowUsage(argv[0]);
    exit(EXIT_FAILURE);
  }

  // ======================= setting default algorithms ====================
  if (args.algorithm == algorithm::NO_ALGORITHM) {
    if (args.max_error > 0) {
      size_t max_len = 0;
      for (const string &pattern : args.patterns) {
        max_len = std::max(max_len, pattern.size());
      }
      if (max_len <= 15 || (max_len <= 05 && args.max_error <= 4)) {
        args.algorithm = algorithm::UKKONEN;
      } else if (max_len < 64) {
        args.algorithm = algorithm::WU_MANBER_64;
      } else {
        args.algorithm = algorithm::SELLERS;
      }
    } else if (args.patterns.size() > 1) {
      args.algorithm = algorithm::AHO_CORASICK;
    } else {
      if (args.patterns[0].size() < 64) {
        args.algorithm = algorithm::SHIFT_OR_64;
      } else {
        args.algorithm = algorithm::BOYER_MOORE;
      }
    }
  } else if (args.max_error > 0) {
    if (!algorithm::IsAproximatedMatchAlgorithm(args.algorithm)) {
      std::cerr << argv[0] << ": Invalid algorithm\n";
      exit(EXIT_FAILURE);
    }
  }
  return args;
}

}  // namespace input_parser
