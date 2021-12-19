from PIL import Image, ImageTk
import tkinter
import winsound

def change_mode():
    study_session()
    break_session()
    return None    

def study_session():

    session = tkinter.Toplevel()
    session.title('Study session')
    session.geometry('500x500')
    
    img_st = tkinter.Canvas(session, width = 400, height = 400)
    img_st.pack()
    spongebob = Image.open("spongebobreading.jpg")
    spongebobTK = ImageTk.PhotoImage(master = session, image = spongebob)
    img_st.create_image(210, 275, anchor = tkinter.CENTER, image = spongebobTK)

    break_button = tkinter.Button(session, text = "Break", bg = 'blue', fg = 'white', font = 'arial 20 bold', command = lambda: session.destroy()).place(x = 180, y = 415)

    session.mainloop()
    
    return None

def break_session():

    breakk = tkinter.Toplevel()
    breakk.title('Break session')
    breakk.geometry('500x500')
    
    img_br = tkinter.Canvas(breakk, width = 400, height = 400)
    img_br.pack()
    homer = Image.open("homer.jpg")
    homerTK = ImageTk.PhotoImage(master = breakk, image = homer)
    img_br.create_image(210, 275, anchor = tkinter.CENTER, image = homerTK)

    break_button = tkinter.Button(breakk, text = "Study", bg = 'red', fg = 'white', font = 'arial 20 bold', command = lambda: breakk.destroy()).place(x = 180, y = 415)
    
    breakk.mainloop()

    return None


pomodoro = tkinter.Tk()
pomodoro.title('Pomodoro timer')
pomodoro.geometry('500x500')

mode = 0

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

go = tkinter.Button(pomodoro, text = "Let's study!", bg = 'red', fg = 'white', font = 'arial 20 bold', command = change_mode).place(x = 160, y = 415)

pomodoro.mainloop()
