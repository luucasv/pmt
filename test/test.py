from os import system
from timeit import time

def getTime(cmd):
  start_time = time.time()
  system(cmd)
  end_time = time.time()
  elapsed = end_time - start_time
  return elapsed

def runPattern(pattern, text_file, max_error, algorithm):
  return getTime('./bin/pmt "{}" {} -c -e {} -a {} > /dev/null'.format(
      pattern, text_file, max_error, algorithm))

def runGrep(pattern, text_file):
  return getTime('grep -c "{}" {} > /dev/null'.format(pattern, text_file))

text_files = [
  'dna'
]

patterns = {}

from os import system
from timeit import time

def getTime(cmd):
  start_time = time.time()
  system(cmd)
  end_time = time.time()
  elapsed = end_time - start_time
  return elapsed

def runPattern(pattern, text_file, max_error, algorithm):
  return getTime('timeout 50s ./bin/pmt "{}" {} -c -e {} > /dev/null'.format(
      pattern, text_file, max_error))

def runPatternFile(pattern, text_file, max_error, algorithm):
  return getTime('timeout 150s ./bin/pmt -p "{}" {} -c -e {} -a {} > /dev/null'.format(
      pattern, text_file, max_error, algorithm))

def runGrep(pattern, text_file):
  return getTime('grep -c "{}" {} > /dev/null'.format(pattern, text_file))

def runGrepFile(pattern, text_file):
  return getTime('grep -c -e {} {} > /dev/null'.format(' -e '.join(pattern), text_file))

text_files = [
  'english'
]

patterns = {}

patterns['english'] = [
  'I',
  'blue',
  'hello',
  'church',
  'thinking',
  'specially',
  'engagement',
  'marshmallow',
  'exaggeration',
  'thunderstruck',
  'I haven\'t got',
  'And I tried it',
  'O King of the Age',
  'light and darkness'
  'a three hundred and',
  'The journey to Chester',
  'pen pineapple apple pen',
  'making these observations',
  'four quarters of the globe',
  'from the Russian proletariat',
]

patterns['dna'] = [
  'A',
  'T',
  'CC',
  'GA',
  'GC',
  'GTAA',
  'CCAC',
  'CCTCTT',
  'GAATATGT',
  'TTTCGACT',
  'TAAAAAGCTC',
  'GGTTAGGCAG',
  'AGTAAACGTC',
  'CGGGGAAGTCGT',
  'GATGTCCACTTG',
  'CTGCAGTACAGCTG',
  'ACTTAAGGACGTAT',
  'CTCGGAGAAGAAGC',
  'CACCTCTCGTAATGGA',
  'TAGCTCTTACATGTTGGGATTA',
  'CTTGAGACGCCAGCCTTGATGACG'
]



algo_types = ['exact']

algos = {}

algos['exact'] = [
  'grep',
  ''
]

algos['aprox'] = [
  'sellers',
  'ukkonen'
]

def main():
  
  base = '../pmt/data/'
  system('make')
  for alg_type in algo_types:
    for txt in text_files:
      for pat in patterns[txt]:
        if alg_type == 'exact':
          errors = [0]
        else:
          errors = [1, len(pat)-1]
        for alg in algos[alg_type]:
          for err in errors:
            time = 0.0
            no_repetitions = 3
            for _ in range(no_repetitions):
              if alg != 'grep':
                time += runPattern(pat, base + txt, err, alg)
              else:
                time += runGrep(pat, base + txt)
            time /= no_repetitions
            print('{:30} {:5} {:5} {:10} {:5.4f}'.format(alg_type + '_' + txt + ('1' if err < 2 else 'M'), len(pat), err, alg, time))


  # Multiple patterns
  # alg_type = 'exact'
  # for txt in text_files:
  #   for pat_lim in range(len(patterns[txt])):
  #     if pat_lim % 4 != 1: continue
  #     pat = patterns[txt][:pat_lim]
      
  #     pat_file = base + 'pat_tmp'
  #     with open(pat_file, 'w') as f:
  #       for p in pat:
  #         print(p, file = f)

  #     errors = [0]
  #     for alg in algos[alg_type]:
  #       for err in errors:
  #         time = 0.0
  #         no_repetitions = 3
  #         for _ in range(no_repetitions):
  #           if alg != 'grep':
  #             time += runPatternFile(pat_file, base + txt, err, alg)
  #           else:
  #             time += runGrepFile(pat, base + txt)
  #         time /= no_repetitions
  #         print('{:30} {:5} {:5} {:10} {:5.4f}'.format('multiple' + '_' + txt + ('1' if err < 2 else 'M'), len(pat), err, alg, time))

if __name__ == '__main__':
  main()
