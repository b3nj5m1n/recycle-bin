import argparse
import os
import string
import random
from abc import ABC, abstractmethod

parser = argparse.ArgumentParser()
parser.add_argument("-m", "--mode", required=True, type=str)
parser.add_argument("-i", "--length-min", required=True, type=int)
parser.add_argument("-x", "--length-max", required=True, type=int)
args = parser.parse_args()

class Mode(ABC):
    @abstractmethod
    def __init__(self, length_min, length_max, seed=random.random()):
        self.length_min = length_min
        self.length_max = length_max
        self.seed = seed
        self.i = 0
        self.rnd = random.Random(seed)
        self.current = self.rnd.random()
    def new(self):
        self.i += 1
        self.current = self.rnd.random()
        pass
    @abstractmethod
    def get_prompt(self):
        pass
    @abstractmethod
    def get_answer(self):
        pass
    @abstractmethod
    def check_answer(self, answer):
        pass

class ModeLetters(Mode):
    def __init__(self, *args):
        super().__init__(*args)
    def get_prompt(self):
        letters = []
        g = random.Random(self.current)
        for i in range(g.choice(range(self.length_min, self.length_max + 1))):
            letters.append(g.choice(['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']))
        return ' '.join(letters).upper()
    def get_answer(self):
        return self.get_prompt()
    def check_answer(self, answer):
        table = answer.maketrans('', '', ' \n\t\r')
        answer = answer.strip().lower().translate(table)
        correct = self.get_answer().strip().lower().translate(table)
        if not len(answer) == len(correct):
            return False
        for pair in zip(answer, correct):
            if not pair[0] == pair[1]:
                return False
        return True



modes = {
    "letters": ModeLetters
}

generator = modes[args.mode](args.length_min, args.length_max)

print("Press any key when you're done memorizing.\n")

while True:
    print("\n" * 2)
    generator.new()
    print(generator.get_prompt(), end='\r')
    os.system('read -s -n 1')
    answer = input("Enter your answer:\n> ")
    if generator.check_answer(answer):
        print("Correct")
    else:
        print(f"The correct answer would have been: {generator.get_answer()}")
