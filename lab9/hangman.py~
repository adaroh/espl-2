import random
word = random.choice(list(open('long-words.txt')))
print word
bad = 0
guessed = []
while bad<6:
  found = True
  for ch in word[:-1]:
    if ch in guessed:
      print ch,
    else:
      print '_',
      found = False
  print ''
  if found:
    break
  char = str(raw_input('Guess a letter:'))
  if char not in word:
    bad += 1
  guessed.append(char)