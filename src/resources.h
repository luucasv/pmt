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

#ifndef SRC_RESOURCES_H_
#define SRC_RESOURCES_H_

const char HELP_MESSAGE[] = "\n"
"Search for occorencies of pattern in all textfile's\n"
"Example: %s church shakespeare.txt\n"
"\n"
"  -h, --help                     Show this help text and exit\n"
"  -v, --version                  Show current version and exit\n"
"\n"
"OPTIONS:\n"
"  -e, --edit maxerror            Set edit error to maxerror >= 0\n"
"  -p, --pattern patternfile      Get patterns from patternfile\n"
"  -a, --algorithm algorithmname  Set search algorithm to run\n"
"                                 See ALGORITHMS section for possibleties\n"
"  -c, --count                    Output only count of matches per file\n"
"\n"
"ALGORITHMS:\n"
"  NAIVE         Brute force algorithm, naive implementation\n"
"  KMP           Knuth-Morris-Pratt algorithm implementation\n"
"  SHIFT_OR      Shift-Or algorithm implementation, a bit algorithm\n"
"  AHO_CORASICK  Aho-corasick algorithm implementation, for multiple patterns\n"
"  SELLERS       Sellers algorithm implementation, for aproximate match\n"
"  UKKONEN       Ukkonen algorithm implementation, for aproximate match\n"
"  WU_MANBER     Wu-Manber algorithm implementation, bit and aproximate match\n"
"\n"
"DEFAULTS:\n"
"  maxerror = 0\n"
"  algorithm = KMP           if maxerror = 0 and there is only a pattern\n"
"  algorithm = AHO_CORASICK  if maxerror = 0 and there are multiple pattern\n"
"  algorithm = UKKONEN       if maxerror > 0\n"
"\n"
"This is a project done at CIn - UFPE\n"
"Authors: Lucas Santana <lvcs@cin.ufpe.br>\n"
"         Tiago Gonçalves <tfg@cin.ufpe.br>\n"
"Report bugs to: <lvcs@cin.ufpe.br> or <tfg@cin.ufpe.br>\n";

const char USAGE_MESSAGE[] = ""
"Usage: %s  [options...] pattern textfile [textfile...]\n"
"       %s  [options...] -p patternfile textfile [textfile...]\n"
"       %s  --help\n"
"       %s  --version\n";

const char VERSION_MESSAGE[] = ""
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

#endif  // SRC_RESOURCES_H_
