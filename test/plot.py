from os import system
import matplotlib.pyplot as plt

def sortByFirst(a, b):
  return zip(*sorted(zip(a, b)))

def mergeByFirst(a, b):
  merged = {}
  for siz, tim in zip(a, b):
    if siz not in merged:
      merged[siz] = []
    merged[siz].append(tim)

  ans = []
  for siz in merged:
    ans.append((siz, sum(merged[siz]) / len(merged[siz])))

  return zip(*ans)

def plot(results_per_alg, pid):
  fig, ax = plt.subplots()
  x, y = results_per_alg
  x, y = mergeByFirst(x, y)
  x, y = sortByFirst(x, y)
  ax.plot(x, y)

  ax.set_xlabel('Text size (Kbytes)')
  if pid.endswith('size')
    ax.set_ylabel('Size of index (Kbytes)')
  else:
    ax.set_ylabel('Execution time (seconds)')

  ax.legend(loc='best', fancybox=True, framealpha=0.5)

  fig.savefig('figs/{}.png'.format(pid))
  plt.close(fig)

def getResults():
  results_per_plt = {}
  with open('stats/results.txt') as results_file:
    for line in results_file:
      if not line.strip(): continue
      pid, siz, tim = line.split()
      siz = int(siz) / 1024
      tim = float(tim)

      if pid.endswith('size'):
        tim = tim / 1024

      if pid not in results_per_plt:
        results_per_plt[pid] = [[], []]

      results_per_plt[pid][0].append(siz)
      results_per_plt[pid][1].append(tim)
  return results_per_plt

def main():
  results = getResults()

  system('mkdir -p figs')
  for pid in results:
    plot(results[pid], pid)

if __name__ == '__main__': main()
