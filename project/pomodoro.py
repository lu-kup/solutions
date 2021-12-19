from PIL import Image, ImageTk
import tkinter
from playsound import playsound
import time
import math

def study_session():

    global mins, secs
    try:
        mins = int(studyt.get())
    except ValueError:
        mins = 1
    secs = 0
    
    def move_time():

        global mins, secs
        if not (mins == 0 and secs == 0):
            if secs == 0:
                secs = 59
                mins = int(mins) - 1
            else:
                secs -= 1
            start = "{:02d}:{:02d}".format(mins, math.floor(secs))
            timer.config(text = start)            
            session.after(1000, move_time)           
            #I got the idea to use recursion to update the Label from Codemy.com youtube channel tutorial.
        else:
            timer.config(text = 'OVER')
            for i in range(5):
                playsound('bell.wav')
            break_session()    

    session = tkinter.Toplevel()
    session.title('Study session')
    session.geometry('500x500')

    start = "{:02d}:{:02d}".format(mins, secs)
    timer = tkinter.Label(session, text = start, font = 'arial 30 bold')
    timer.pack(padx = 100, pady = 50)
    
    img_st = tkinter.Canvas(session, width = 400, height = 400)
    img_st.pack()
    spongebob = Image.open("spongebobreading.jpg")
    spongebobTK = ImageTk.PhotoImage(master = session, image = spongebob)
    img_st.create_image(210, 100, anchor = tkinter.CENTER, image = spongebobTK)

    break_button = tkinter.Button(session, text = "Stop session", bg = 'grey', fg = 'white', font = 'arial 20 bold', command = lambda: session.destroy()).place(x = 150, y = 415)

    session.after(1000, move_time) 
    session.mainloop()
    
    return None

def break_session():

    global mins, secs
    
    try:
        mins = int(breakt.get())
    except ValueError:
        mins = 1
    secs = 0

    def move_time():

        global mins, secs
        if not (mins == 0 and secs == 0):
            if secs == 0:
                secs = 59
                mins = int(mins) - 1
            else:
                secs -= 1
            start = "{:02d}:{:02d}".format(mins, math.floor(secs))
            timer.config(text = start)            
            breakk.after(1000, move_time)           
        else:
            timer.config(text = 'OVER')
            for i in range(5):
                playsound('bell.wav')
            study_session()

    breakk = tkinter.Toplevel()
    breakk.title('Break session')
    breakk.geometry('500x500')

    start = "{:02d}:{:02d}".format(mins, secs)
    timer = tkinter.Label(breakk, text = start, font = 'arial 30 bold')
    timer.pack(padx = 100, pady = 50)
    
    img_br = tkinter.Canvas(breakk, width = 400, height = 400)
    img_br.pack()
    homer = Image.open("resting.jpg")
    homerTK = ImageTk.PhotoImage(master = breakk, image = homer)
    img_br.create_image(210, 70, anchor = tkinter.CENTER, image = homerTK)

    break_button = tkinter.Button(breakk, text = "Stop session", bg = 'grey', fg = 'white', font = 'arial 20 bold', command = lambda: breakk.destroy()).place(x = 150, y = 415)

    breakk.after(1000, move_time) 
    breakk.mainloop()

    return None


pomodoro = tkinter.Tk()
pomodoro.title('Pomodoro timer')
pomodoro.geometry('500x600')

mins = 0
secs = 0

studyt = tkinter.StringVar()
breakt = tkinter.StringVar()

img = tkinter.Canvas(pomodoro, width = 400, height = 400)
img.pack()
tomato = Image.open("sticker.jpg")
tomatoTK = ImageTk.PhotoImage(tomato)
img.create_image(210, 275, anchor = tkinter.CENTER, image = tomatoTK)

tb1 = tkinter.Label(pomodoro, text = "Study time (mins):", font = 'arial 10').place(x = 100, y = 50)   
te1= tkinter.Entry(pomodoro, width = '20', textvariable = studyt).place(x = 100, y = 75)

tb2 = tkinter.Label(pomodoro, text = "Break time (mins):", font = 'arial 10').place(x = 300, y = 50)   
te2 = tkinter.Entry(pomodoro, width = '20', textvariable = breakt).place(x = 300, y = 75)

go = tkinter.Button(pomodoro, text = "Let's study!", bg = 'red', fg = 'white', font = 'arial 20 bold', command = study_session).place(x = 160, y = 415)
rest = tkinter.Button(pomodoro, text = "Take a break!", bg = 'blue', fg = 'white', font = 'arial 20 bold', command = break_session).place(x = 150, y = 490)

pomodoro.mainloop()
