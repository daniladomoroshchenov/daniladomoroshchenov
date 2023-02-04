tmp = 0
sum = 0
dif = 0
mul = 0
div = 0

def click_handler(event = None):
    assert type(event) == int
    current = entry_field.get()
    entry_field.delete(0, END)
    entry_field.insert(0, str(current) + str(event))

def sum_event():
    global tmp, sum, dif, mul, div
    if sum == 1:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) + float(current))
        tmp = 0
    if dif == 1:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) - float(current))
        tmp = 0
    if mul== 1:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) * float(current))
        tmp = 0
    if div == 1:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) / float(current))
        tmp = 0
    sum = 1
    dif = 0
    mul = 0
    div = 0
    if not tmp:
        tmp = entry_field.get()
        entry_field.delete(0, END)
    else:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) + float(current))
        tmp = 0

def dif_event():
    global tmp, sum, dif, mul, div
    if sum == 1:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) + float(current))
        tmp = 0
    if dif == 1:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) - float(current))
        tmp = 0
    if mul== 1:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) * float(current))
        tmp = 0
    if div == 1:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) / float(current))
        tmp = 0
    sum = 0
    dif = 1
    mul = 0
    div = 0
    if not tmp:
        tmp = entry_field.get()
        entry_field.delete(0, END)
    else:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) - float(current))
        tmp = 0

def mul_event():
    global tmp, sum, dif, mul, div
    if sum == 1:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) + float(current))
        tmp = 0
    if dif == 1:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) - float(current))
        tmp = 0
    if mul == 1:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) * float(current))
        tmp = 0
    if div == 1:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) / float(current))
        tmp = 0
    sum = 0
    dif = 0
    mul = 1
    div = 0
    if not tmp:
        tmp = entry_field.get()
        entry_field.delete(0, END)
    else:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) * float(current))
        tmp = 0

def div_event():
    global tmp, sum, dif, mul, div
    if sum == 1:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) + float(current))
        tmp = 0
    if dif == 1:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) - float(current))
        tmp = 0
    if mul == 1:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) * float(current))
        tmp = 0
    if div == 1:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) / float(current))
        tmp = 0
    sum = 0
    dif = 0
    mul = 0
    div = 1
    if not tmp:
        tmp = entry_field.get()
        entry_field.delete(0, END)
    else:
        current = entry_field.get()
        entry_field.delete(0, END)
        entry_field.insert(0, float(tmp) / float(current))
        tmp = 0

def equal_event():
    global tmp, sum, dif, mul, div
    current = entry_field.get()
    entry_field.delete(0, END)
    if sum == 1:
        entry_field.insert(0, float(tmp) + float(current))
    if dif == 1:
        entry_field.insert(0, float(tmp) - float(current))
    if mul == 1:
        entry_field.insert(0, float(tmp) * float(current))
    if div == 1:
        entry_field.insert(0, float(tmp) / float(current))
    sum = 0
    dif = 0
    mul = 0
    div = 0
    tmp = 0

def clear_event():
    entry_field.delete(0, END)
    global tmp, sum, dif, mul, div
    sum = 0
    dif = 0
    mul = 0
    div = 0
    tmp = 0

from tkinter import *

root = Tk()

entry_field = Entry(root, width = 40, borderwidth = 5)
entry_field.grid(row = 0, column = 0, columnspan = 3, padx = 10, pady = 10)
button_1 = Button(root, text = "1", padx = 40, pady = 20, command = lambda: click_handler(1))
button_2 = Button(root, text = "2", padx = 40, pady = 20, command = lambda: click_handler(2))
button_3 = Button(root, text = "3", padx = 40, pady = 20, command = lambda: click_handler(3))
button_4 = Button(root, text = "4", padx = 40, pady = 20, command = lambda: click_handler(4))
button_5 = Button(root, text = "5", padx = 40, pady = 20, command = lambda: click_handler(5))
button_6 = Button(root, text = "6", padx = 40, pady = 20, command = lambda: click_handler(6))
button_7 = Button(root, text = "7", padx = 40, pady = 20, command = lambda: click_handler(7))
button_8 = Button(root, text = "8", padx = 40, pady = 20, command = lambda: click_handler(8))
button_9 = Button(root, text = "9", padx = 40, pady = 20, command = lambda: click_handler(9))
button_0 = Button(root, text = "0", padx = 40, pady = 20, command = lambda: click_handler(0))
button_add = Button(root, text = "+", padx = 40, pady = 20, command = sum_event)
button_dif = Button(root, text = '-', padx = 40, pady = 20, command = dif_event)
button_mul = Button(root, text = '*', padx = 40, pady = 20, command = mul_event)
button_div = Button(root, text = '/', padx = 40, pady = 20, command = div_event)
button_clear = Button(root, text = "Clear", padx = 40, pady = 20, command = clear_event)
button_equal = Button(root, text = "=", padx = 40, pady = 20, command = equal_event)

button_1.grid(row = 1, column = 0, sticky = "we")
button_2.grid(row = 1, column = 1, sticky = "we")
button_3.grid(row = 1, column = 2, sticky = "we")

button_4.grid(row = 2, column = 0, sticky = "we")
button_5.grid(row = 2, column = 1, sticky = "we")
button_6.grid(row = 2, column = 2, sticky = "we")

button_7.grid(row = 3, column = 0, sticky = "we")
button_8.grid(row = 3, column = 1, sticky = "we")
button_9.grid(row = 3, column = 2, sticky = "we")

button_0.grid(row = 4, column = 0, sticky = "we")
button_add.grid(row = 4, column = 1, sticky = "we")
button_dif.grid(row = 4, column = 2, sticky = "we")

button_equal.grid(row = 5, column = 0, sticky = "we")
button_mul.grid(row = 5, column = 1, sticky = "we")
button_div.grid(row = 5, column = 2, sticky = "we")

button_clear.grid(row = 6, column = 0, columnspan = 3, sticky = "we")

root.mainloop()