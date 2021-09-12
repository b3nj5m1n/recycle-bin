import deck_of_cards
from deck_of_cards import CountingSystemHiLo, DeckOfCards
import random
from time import sleep
from dataclasses import dataclass
import rich
from rich.console import Console
from rich.panel import Panel
from rich.markdown import Markdown
from rich.text import Text
from rich.layout import Layout
from rich.live import Live
from rich.padding import Padding

n = 25

console = Console(color_system="truecolor")
layout = Layout()

layout.split_column(
    Layout(name="status"),
    Layout(name="cards"),
)
layout["status"].size = 3
# layout["status"].ratio = 2
layout["status"].visible = False
# layout["cards"].size = None
# layout["cards"].ratio = 6

@dataclass
class Save():
    count: int
    answer: int
    def output(self):
        result = Text(justify="center")
        if self.count == None or self.answer == None: return
        layout["status"].visible = True
        if self.answer == self.count:
            result.append("Correct", style='bold green')
        else:
            result.append(f"Incorrect. The correct count was {self.count}.", style='bold red')
        layout["status"].update(
            Panel(result)
        )

last_answer = Save(None, None)

def render_cards(cards):
    result = Text(justify="center")
    for card in cards:
        color_fg = ''
        if card.suit == deck_of_cards.Suit.SPADES: color_fg = "black"
        if card.suit == deck_of_cards.Suit.CLUBS: color_fg = "black"
        if card.suit == deck_of_cards.Suit.HEARTS: color_fg = "red"
        if card.suit == deck_of_cards.Suit.DIAMONDS: color_fg = "red"
        result.append(card.value.name + " of " + card.suit.name + "\n", style='bold ' + color_fg)
    return result

while True:
    # with console.screen():
    with Live(layout, screen=True):
        last_answer.output()
        deck = DeckOfCards()
        deck.shuffle()
        cards = random.sample(deck.cards, n)
        count = CountingSystemHiLo.count_cards(cards)
        layout["cards"].update(
            Panel(render_cards(cards))
        )
        # console.print("What is the count?", justify="left", style='bold')
        answer = int(input(">>> "))
        last_answer = Save(count, answer)
