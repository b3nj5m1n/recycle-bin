from abc import ABC, abstractmethod
from datetime import datetime
from prettytable import PrettyTable
import argparse
import humanize
import os
import random
import string

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
        self.time_memo_started = datetime.now()
        self.time_memo_finished = None
        self.time_answer_checked = None
    def new(self):
        self.i += 1
        self.current = self.rnd.random()
        self.time_generated = datetime.now()
        pass
    @abstractmethod
    def get_prompt(self):
        pass
    @abstractmethod
    def get_answer(self):
        pass
    @abstractmethod
    def check_answer(self, answer):
        self.time_answer_checked = datetime.now()
        pass
    def finish_memo(self):
        self.time_memo_finished = datetime.now()
    def stats(self):
        pt = PrettyTable()
        pt.field_names = ["Time Memo", "Time Recall", "Time Total"]
        pt.add_row([
            humanize.precisedelta(self.time_memo_finished - self.time_memo_started, minimum_unit="seconds"),
            humanize.precisedelta(self.time_answer_checked - self.time_memo_finished, minimum_unit="seconds"),
            humanize.precisedelta(self.time_answer_checked - self.time_memo_started, minimum_unit="seconds")
        ])
        return pt.get_string()

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
        super().check_answer(self)
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
    generator.finish_memo()
    prompt = "Enter your answer"
    space = ''.join([" " for _ in  range(len(generator.get_answer()) - len("Enter your answer:"))])
    answer = input(f"{prompt}:{space}\n> ")
    if generator.check_answer(answer):
        print("Correct")
    else:
        print(f"The correct answer would have been: {generator.get_answer()}")
    print(generator.stats())
