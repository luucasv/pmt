#ifndef SRC_RESOURCES_H
#define SRC_RESOURCES_H

const char help_msg[] = "\n"
"Search for occorencies of pattern in all textfile's\n"
"Example: %s church shakespeare.txt\n"
"\n"
"  -h, --help                      show this help text and exit\n"
"  -v, --version                   show current version and exit\n"
"\n"
"OPTIONS:\n"
"  -e, --edit maxerror            set edit error to max_error >= 0\n"
"                                 default is 0, and 0 means exact match\n"
"                                 max_error > 0 means aproximate match\n"
"  -p, --pattern patternfile      search for the patterns in patternfile\n"
"  -a, --algorithm algorithmname  set algorithm to algorithm_name\n"
"                                 possible names: KMP, AHO_CORASICK,\n"
"                                 UKKONEN, SHIFT_OR, NAIVE (case is ignored)\n"
"                                 KMP is default for sigle pattern\n"
"                                 AHO_CORASICK for multiple pattern\n"
"                                 and UKKONEN for aproximate match\n"
"  -c, --count                    print only count of matches per file\n"
"\n"
"This is a project done at CIn - UFPE\n"
"Authors: Lucas Santana <lvcs@cin.ufpe.br>\n"
"         Tiago Gonçalves <tfg@cin.ufpe.br>\n"
"Report bugs to: <lvcs@cin.ufpe.br> or <tfg@cin.ufpe.br>\n";

const char usage_msg[] = ""
"Usage: %s  [options...] pattern textfile [textfile...]\n"
"       %s  [options...] -p patternfile textfile [textfile...]\n"
"       %s  --help\n"
"       %s  --version\n";

const char version_msg[] = ""
"pmt 0.0.1\n"
"Copyright (c) 2017 Lucas V. da C. Santana and Tiago Figueiredo Gonçalves\n"
"\n"
"License: GPL: <https://www.gnu.org/licenses/gpl.html>\n"
"This program comes with ABSOLUTELY NO WARRANTY\n"
"This is free software, and you are welcome to redistribute it\n"
"under certain conditions\n"
"\n"
"This is a project done at CIn - UFPE\n"
"Authors: Lucas Santana <lvcs@cin.ufpe.br>\n"
"         Tiago Gonçalves <tfg@cin.ufpe.br>\n"
"Report bugs to: <lvcs@cin.ufpe.br> or <tfg@cin.ufpe.br>\n";

#endif  // SRC_RESOURCES_H
