from tkinter import *
from time import sleep
import tkinter.messagebox as mb

class rocket:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.object = canvas.create_rectangle(self.x - 7.5, self.y - 50, self.x + 7.5, self.y + 50, fill = 'black')

class Circle:
    def __init__(self):
        self.first_player = 0
        self.second_player = 0
        self.x = 300
        self.y = 300
        self.size = 12.5
        self.speed_x = 3
        self.speed_y = 2
        self.object = canvas.create_oval(self.x - self.size, self.y - self.size, self.x + self.size, self.y + self.size, fill = 'red')
    
    def check_collision(self):
        pos = canvas.coords(self.object)
        if pos[1] <= 0 or pos[3] >= 600:
            self.speed_y *= -1

        if (pos[0] <= canvas.coords(rocket1.object)[2] and pos[1] >= canvas.coords(rocket1.object)[1] and pos[1] <= canvas.coords(rocket1.object)[3]) or (pos[2] >= canvas.coords(rocket2.object)[0] and pos[3] >= canvas.coords(rocket2.object)[1] and pos[3] <= canvas.coords(rocket2.object)[3]):
            self.speed_x *= -1

        if pos[0] <= 0:
            mb.showinfo('Score', 'Player 2 scored!')
            canvas.move(self.object, 300 - self.x, 300 - self.y)
            self.x = 300
            self.y = 300
            self.second_player += 1
            self.speed_x *= -1

        if pos[2] >= 600:
            mb.showinfo('Score', 'Player 1 scored!')
            canvas.move(self.object, 300 - self.x, 300 - self.y)
            self.x = 300
            self.y = 300
            self.first_player += 1
            self.speed_x *= -1

    def move(self):
        self.x += self.speed_x
        self.y += self.speed_y
        canvas.move(self.object, self.speed_x, self.speed_y)
        self.check_collision()


def move_racket(event):
    if event.keysym == 'z':
        if canvas.coords(rocket1.object)[1] >= 3:
            rocket1.y -= 3
            canvas.move(rocket1.object, 0, -3)
    if event.keysym == 'x':
        if canvas.coords(rocket1.object)[3] <= 597:
            rocket1.y += 3
            canvas.move(rocket1.object, 0, 3)
    if event.keysym == 'comma':
        if canvas.coords(rocket2.object)[1] >= 3:
            rocket2.y -= 3
            canvas.move(rocket2.object, 0, -3)
    if event.keysym == 'period':
        if canvas.coords(rocket2.object)[3] <= 597:
            rocket2.y += 3
            canvas.move(rocket2.object, 0, 3)

root = Tk()

canvas = Canvas(root, width = 600, height = 600)

rocket1 = rocket(12.5, 300)
rocket2 = rocket(587.5, 300)

c = Circle()

canvas.bind_all('<KeyPress>', move_racket)

canvas.pack()

score = Label(root, text = f'{c.first_player} : {c.second_player}')
score.pack()

while True:
    score.config(text = f'{c.first_player} : {c.second_player}')
    if c.second_player == 5:
        c.second_player = 0
        c.first_player = 0
        answer = mb.askyesno('Game over', 'Player 2 Win. Continue?')
        if answer == False:
            root.destroy()
            break
    
    if c.first_player == 5:
        c.second_player = 0
        c.first_player = 0
        answer = mb.askyesno('Game over', 'Player 1 Win. Continue?')
        if answer == False:
            root.destroy()
            break
    c.move()
    root.update()
    sleep(0.03)

root.mainloop()