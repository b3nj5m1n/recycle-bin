import turtle
import time
import math
from vec import vector2, vector2_line

# Broken

t = turtle.Turtle()
u = turtle.Turtle()
t.color("blue")
u.color("green")
u.penup()
t.penup()
t.setposition((0,250))
u.setposition((0,-250))
u.pendown()
t.pendown()

def draw_dot(pos: vector2):
    moooin = turtle.Turtle()
    moooin.color('cyan')
    moooin.penup()
    moooin.goto(pos.x, pos.y)
    moooin.pendown()
    moooin.dot(15, 'cyan')
    moooin.hideturtle()

def move(player):
    a = turtle.numinput("", "Right turn (degrees)", 0)
    c = turtle.numinput("", "Distance", 0)
    
    ortsvektor = vector2(player.xcor() + 0.0000000000000001, player.ycor() + 0.0000000000000001)
    player.right(a)
    player.forward(c)
    richtungsvektor = vector2((player.xcor() - ortsvektor.x) + 0.0000000000000001, (player.ycor() - ortsvektor.y) + 0.0000000000000001)
    gerade = vector2_line(ortsvektor, richtungsvektor)

    if richtungsvektor.x == 0 and richtungsvektor.y == 0:
        return

    for i, line in enumerate(vektoren):
        print(f"Checking against move {i}")
        ints = gerade.intersects(line)
        print(ints)
        if ints != False:
            draw_dot(ints)
    
    vektoren.append(gerade)

vektoren = []

# h = int(turtle.numinput("Wieviele Runden möchtet ihr spielen? ", "Anzahl Runden:", 10, minval=1))
h = 10

for c in range(0,h):
    move(t)
    move(u)
