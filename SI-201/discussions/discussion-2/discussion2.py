
from turtle import *
### write all new functions here ###

def draw_circle(x, y, turtle, color, radius):
    turtle.up()
    turtle.goto(x,y)
    turtle.down()
    turtle.color(color)
    turtle.begin_fill()
    turtle.circle(radius)
    turtle.end_fill()
def draw_rect(x, y, turtle, color, length, width):
    turtle.up()
    turtle.goto(x,y)
    turtle.down()
    turtle.color(color)
    turtle.begin_fill()
    for i in range(2):
        turtle.forward(length)
        turtle.right(90)
        turtle.forward(width)
        turtle.right(90)
    turtle.end_fill()

def draw_line(turtle, color, x, y, length):
    turtle.up()
    turtle.goto(x, y)
    turtle.down()
    turtle.color(color)
    turtle.forward(length)


def draw_emoji(turtle):
    draw_circle(0, -100, turtle, 'yellow', 200)
    draw_circle(75, 100, turtle, 'black', 40)
    draw_circle(-75, 100, turtle, 'black', 40)

    draw_rect(60, 110, turtle, 'lightblue', 40, 200)
    draw_rect(-90, 110, turtle, 'lightblue', 40, 200)

    draw_circle(0, -50, turtle, 'black', 40)
    turtle.setheading(40)
    draw_rect(-130, 150, turtle, 'black', 100, 25)
    turtle.setheading(140)
    draw_rect(120, 130, turtle, 'black', 100, 25)
def main():
    space = Screen()
    space.bgcolor('black')
    alex = Turtle("turtle")
    alex.speed(10)
    draw_emoji(alex)


    space.exitonclick()
if __name__ == '__main__':
    main()

