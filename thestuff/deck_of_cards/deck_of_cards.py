from dataclasses import dataclass
from enum import Enum, auto, unique
from abc import ABC, abstractmethod
import random
import math

@unique
class Value(Enum):
    ACE = auto()
    TWO = auto()
    THREE = auto()
    FOUR = auto()
    FIVE = auto()
    SIX = auto()
    SEVEN = auto()
    EIGHT = auto()
    NINE = auto()
    TEN = auto()
    JACK = auto()
    QUEEN = auto()
    KING = auto()
    @staticmethod
    def get_value_from_string(string: str):
        mappings={
            'A': Value.ACE,
            '2': Value.TWO,
            '3': Value.THREE,
            '4': Value.FOUR,
            '5': Value.FIVE,
            '6': Value.SIX,
            '7': Value.SEVEN,
            '8': Value.EIGHT,
            '9': Value.NINE,
            '1': Value.TEN,
            'J': Value.JACK,
            'Q': Value.QUEEN,
            'K': Value.KING,
        }
        return mappings.get(string,"Invalid input")

@unique
class Suit(Enum):
    SPADES = auto()
    DIAMONDS = auto()
    CLUBS = auto()
    HEARTS = auto()
    @staticmethod
    def get_suit_from_string(string: str):
        mappings={
            'S': Suit.SPADES,
            'D': Suit.DIAMONDS,
            'C': Suit.CLUBS,
            'H': Suit.HEARTS,
        }
        return mappings.get(string,"Invalid input")

class PlayingCardStringError(Exception):
    """Raised when the short representation of
    a card doesn't match the requirements"""
    pass

@dataclass
class PlayingCard():
    value: Value
    suit: Suit
    def __init__(self, value: Value = None, suit: Suit = None, string: str = None):
        self.value = value
        self.suit = suit
        if not string == None:
            self.from_string(string)
    def __str__(self):
        return f"""{self.value.name}-{self.suit.name[0]}"""
    def from_string(self, string: str):
        """Parses shorthand short representation of a card, the
        format is VALUE SUIT, each one letter without a space in
        between, for example JD (Jack of Diamonds), 1S (10 of Spades)"""
        string = string.strip()
        if string == None: raise PlayingCardStringError
        if len(string) != 2: raise PlayingCardStringError
        self.value = Value.get_value_from_string(string[0])
        self.suit = Suit.get_suit_from_string(string[1])

class CountingSystem(ABC):
    mappings: dict = {}
    @classmethod
    def count_card(cls, card: PlayingCard) -> int:
        return cls.mappings[card.value]
    @classmethod
    def count_cards(cls, cards: list[PlayingCard]) -> int:
        result = 0
        for card in cards:
            result += cls.count_card(card)
        return result

class CountingSystemHiLo(CountingSystem):
    mappings={
        Value.ACE: -1,
        Value.TWO: 1,
        Value.THREE: 1,
        Value.FOUR: 1,
        Value.FIVE: 1,
        Value.SIX: 1,
        Value.SEVEN: 0,
        Value.EIGHT: 0,
        Value.NINE: 0,
        Value.TEN: -1,
        Value.JACK: -1,
        Value.QUEEN: -1,
        Value.KING: -1,
    }

class DeckOfCards():
    cards = []
    def __init__(self, create_deck=True):
        if create_deck:
            for _, suit in Suit.__members__.items():
                for _, value in Value.__members__.items():
                    self.cards.append(PlayingCard(value, suit))
    def __str__(self):
        return '.'.join([str(card) for card in self.cards])
    def cut(self):
        """Cut the deck at a random point in the middle third of the deck"""
        i = random.randint(math.floor(len(self.cards)*(1/3)), math.ceil(len(self.cards)*(2/3)))
        self.cards = self.cards[i:] + self.cards[:i]
    def riffle_shuffle(self):
        """Simulate an imperfect riffle shuffle"""
        stacks = [[],[]]
        for card in self.cards:
            stacks[random.randint(0,1)].append(card)
        self.cards = stacks[0] + stacks[1]
    def wash(self):
        random.shuffle(self.cards)
    def shuffle(self):
        """Imitates casino procedure (except for the strip cut)"""
        self.wash()
        for _ in range(4):
            self.riffle_shuffle()
        self.cut()

if __name__ == '__main__':
    cards = [
        PlayingCard(string="JS"),
        PlayingCard(string="5D"),
        PlayingCard(string="8H"),
        PlayingCard(string="AC"),
    ]
    print(CountingSystemHiLo.count_cards(cards))

