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


#include "parse_args.h"

#include <sys/stat.h>
#include <glob.h>
#include <getopt.h>

#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>
#include <string>

using std::vector;
using std::string;

namespace parse_args {

InputArguments::InputArguments() {
  max_error = 0;
  count_flag = false;
  algorithm = util::NO_ALGORITHM;
}

// show usage message
void ShowUsage(const char *base) {
  std::cerr
  << "Usage: " << base << " [options...] pattern textfile [textfile...]\n"
  << "       " << base << " --help\n"
  << "       " << base << " --version\n";
}

// show help message
void ShowHelp(const char *base) {
  ShowUsage(base);
  std::cerr
  << '\n'
  << "Search for occorencies of pattern in all textfile's\n"
  << "Example: " << base << " church shakespeare.txt\n"
  << '\n'
  << " -h, --help                      show this help text and exit\n"
  << " -v, --version                   show current version and exit\n"
  << '\n'
  << "OPTIONS:\n"
  << " -e, --edit max_error            set edit error to max_error >= 0\n"
  << "                                 default is 0, and 0 means exact match\n"
  << "                                 max_error > 0 means aproximate match\n"
  << " -p, --pattern patternfile       search for the patterns in patternfile\n"
  << " -a, --algorithm algorithm_name  set algorithm to algorithm_name\n"
  << "                                 possible names: KMP, AHO_CORASICK,\n"
  << "                                 UKKONEN, SHIFT_OR (case is ignored)\n"
  << "                                 KMP is default for sigle pattern\n"
  << "                                 AHO_CORASICK for multiple pattern\n"
  << "                                 and UKKONEN for aproximate match\n"
  << " -c, --count                     print only count of matches per file\n"
  << '\n'
  << "This is a project done at CIn - UFPE\n"
  << "Authors: Lucas Santana <lvcs@cin.ufpe.br>\n"
  << "         Tiago Gonçalves <tfg@cin.ufpe.br>\n"
  << "Report bugs to: <lvcs@cin.ufpe.br> or <tfg@cin.ufpe.br>\n";
}

void ShowVersion() {
  std::cerr
  << "pmt 0.0.1\n"
  << "Copyright (c) 2017 Lucas V. da C. Santana and Tiago Figueiredo Gonçalves"
  << '\n'
  << "License: GPL: <https://www.gnu.org/licenses/gpl.html>\n"
  << "This program comes with ABSOLUTELY NO WARRANTY\n"
  << "This is free software, and you are welcome to redistribute it\n"
  << "under certain conditions\n"
  << '\n'
  << "This is a project done at CIn - UFPE\n"
  << "Authors: Lucas Santana <lvcs@cin.ufpe.br>\n"
  << "         Tiago Gonçalves <tfg@cin.ufpe.br>\n"
  << "Report bugs to: <lvcs@cin.ufpe.br> or <tfg@cin.ufpe.br>\n";
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
  // TODO(lvcs): Perguntar sobre pattern, se deveria ter um pattern obrigatório
  // depois que um arquivo de padrões foi espcificado

  // Return variabel, already set to its default values
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
        args.algorithm = util::GetAlgorithm(optarg);
        if (args.algorithm == util::NO_ALGORITHM) {
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
  if (args.algorithm == util::NO_ALGORITHM) {
    if (args.max_error > 0) {
      args.algorithm = util::UKKONEN;
    } else if (args.patterns.size() > 1) {
      args.algorithm = util::AHO_CORASICK;
    } else {
      args.algorithm = util::KMP;
    }
  }
  // TODO(lvcs): check what to do if algorithm is set to a exact match one
  //             but max_error is set to a number > 0
  return args;
}

}  // namespace parse_args
