/* Copyright (C) Lucas Santana and Tiago Gonçalves - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Lucas Santana <lvcs@cin.ufpe.br> and
 *  Tiago Gonçalves <tfg@cin.ufpe.br>
 * September-Octuber 2017
 */

#include "parse_args.h"
#include <sys/stat.h>
#include <glob.h>
#include <getopt.h>
#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <tuple>

void ShowHelp(const char* name) {
  std::cerr 
  << "Usage: " << name << " [options...] pattern textfile [textfile...]\n"
  << "       " << name << " --help\n"
  << "       " << name << " --version\n"
  << '\n'
  << "Search for occorencies of pattern in all textfile's\n"
  << "Example: " << name << " church shakespeare.txt\n"
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

// read all patters in file_name (one per line) and push into patterns vector
bool ReadPatterns(std::vector<std::string> &patterns, const char *file_name) {
  std::ifstream file(file_name);
  if (!file.good()) {
    return false;
  }
  std::string pattern;
  while (std::getline(file, pattern)) {
    patterns.push_back(pattern);
  }
  return true;
}

inline bool IsFile(const char *file_name) {
  struct stat buffer;
  return stat(file_name, &buffer) == 0;
}

bool InsertTextFiles(std::vector<std::string> &text_files,const char *pattern) {
  glob_t glob_buffer;
  int glob_ans = glob(pattern, GLOB_TILDE, nullptr, &glob_buffer);
  if (glob_ans == GLOB_NOMATCH) {
    return false;
  }
  bool found_file = false;
  for (int i = 0; i < glob_buffer.gl_pathc; i++) {
    if (IsFile(glob_buffer.gl_pathv[i])) {
      text_files.push_back(std::string(glob_buffer.gl_pathv[i]));
      found_file = true;
    }
  }
  if (!found_file) {
    return false;
  }
  return true;
}

parse_args::InputArguments parse_args::ParseArgs(int argc,char * const*argv) {
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
        if(!is_num || args.max_error < 0) {
          std::cerr << argv[0] << ": " << optarg
                    << ": Invalid max_error value\n";
          exit(EXIT_FAILURE);
        }
        break;
      }
      case 'p': {
        bool file_exits = ReadPatterns(args.patterns, optarg);
        if (!file_exits) {
          std::cerr << argv[0] << ": " << optarg
                    << ": No such file or directory\n";
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
        ShowHelp(argv[0]); // TODO(lvcs): change to ShowVersion
        exit(EXIT_SUCCESS);
      }
      case ':': {
        std::cerr << argv[0] << ": " << argv[optind] << ": Missing argument.\n";
        exit(EXIT_FAILURE);
        break;
      }
      case '?': {
        std::cerr << argv[0] << ": " << argv[optind] << ": Invalid option.\n";
        exit(EXIT_FAILURE);
        break;
      }
      default: {
        std::cerr << argv[0] << ":  Internal error while parsing arguments\n";
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
      exit(EXIT_FAILURE);
    } else {
      args.patterns.push_back(argv[optind]);
      optind++;
    }
  }

  // ===================== reading text_files ==============================
  while (optind < argc) {
    bool is_file = InsertTextFiles(args.text_files, argv[optind]);
    if (!is_file) {
      std::cerr << argv[0] << ": " << argv[optind]
                << ": Doesn't name a file.\n";
      exit(EXIT_FAILURE);
    }
    optind++;
  }
  if (args.text_files.empty()) {
    std::cerr << argv[0] << ": Missing textfile argument\n";
    ShowHelp(argv[0]);
    exit(EXIT_FAILURE);
  }
  return args;
}