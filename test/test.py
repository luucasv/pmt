from os import system
from timeit import time

def getTime(cmd):
  start_time = time.time()
  system(cmd)
  end_time = time.time()
  elapsed = end_time - start_time
  return elapsed

def runTest(pattern_file, text_file, max_error, algorithm):
  return getTime('./bin/pmt -p {} {} -c -e {} -a {} > /dev/null'.format(
      pattern_file, text_file, max_error, algorithm))

def main():
  algos = [
    ('naive',   False),
    ('kmp',     False),
    ('aho',     False),
    ('so64',      False),
    ('bm',      False),
    ('sellers', True),
    ('ukkonen', True),
    ('wm64',      True)
  ]
  tests = [
    ('data/blue', 'data/english', 0),
    ('data/blue', 'data/english', 1),
    ('data/blue', 'data/english', 2),
    ('data/blue', 'data/english', 3),
    ('data/blue', 'data/english', 4),
    ('data/marshmallow', 'data/english', 0),
    ('data/marshmallow', 'data/english', 1),
    ('data/marshmallow', 'data/english', 2),
    ('data/marshmallow', 'data/english', 3),
    ('data/marshmallow', 'data/english', 4)
  ]

  for pat, txt, err in tests:
    for alg, app in algos:
      if not app and err > 0: continue
      time = runTest(pat, txt, err, alg)
      result = (pat, txt, err, alg, time)
      print('{:30} {:30} {:5} {:10} {:5.4f}'.format(pat, txt, err, alg, time))

if __name__ == "__main__":
    main()