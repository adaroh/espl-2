f = open('grades.csv' , 'r')
fmt = f.readline()
arr = {}
for line in f:
  list = line.split(',')
  try:
    arr[list[2]]['count']+= 1
    arr[list[2]]['studs'].append(list[0])
  except KeyError:
    arr[list[2]] = {'count': 1, 'studs': [list[0]]}

print arr