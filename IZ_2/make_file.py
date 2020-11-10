from random import randint

with open("text.txt", "w") as f:
    for _ in range(200000000):
        f.write(str(randint(0, 9)) + " ")
