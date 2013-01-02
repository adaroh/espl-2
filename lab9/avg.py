f = open('grades.csv' , 'r')
fmt = f.readline()
total = 0.0
count = 0.0
for line in f:
  list = line.split(',')
  total = total + float(list[2])
  count = count + 1
print 'average is ' , (total/count)