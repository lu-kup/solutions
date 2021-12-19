# POMODORO TIMER
#### Video Demo:  https://www.youtube.com/watch?v=1OJjLFuXvqc&ab_channel=LukasKuprys
#### Description:
Pomodoro study method is a technique used to structure study sessions. It allows to increase focus and prevent procrastination.
In essence, the method consists of spending a certain fixed amount of time studying, which is then followed by a break of fixed length. This is done for a number of study sessions.
I often use this method when studying for university, and will be likely structure my work sessions this way in the upcoming exam session that I will have in January.
Normally, in order to time my pomodoro sessions, I would use the timer on my iPhone. However, it is rather inconvenient as the time setting must be changed after every study session or break.
In addition, it does not stop ringing automatically. Therefore, for my own use during the exams, I decided to code a more suitable timer dedicated to the pomodoro method.

My Pomodoro Timer program is a desktop app with a user interface that is implemented using Tkinter. Tkinter is a Python library for creating graphical user interfaces that is rather simple to use.
Once the program starts, a window is opened where the user can input the desired lenghts for their study and break sessions. Once the button 'Let's study' is clicked, the first study session timer starts.
After the session ends, a bell sound rings for a few times and then a new window opens with a new timer for the break session automatically. (I originally wanted the wanted the previous window to close automatically, but I was not able to
implement this on Tkinter. Instead, I made the timer turn into the message 'OVER', which indicates that the script has ended and the window can be closed manually). Once the break ends, another timer starts for the study session.
The user can stop an active study session by clicking on the dedicated button at any time, which then allows setting a new number for the length of study and break sessions when starting again.

The folder for this program contains the file with Python script and the media files that are used by the script. The images are used as illustrations in the windows, and wav file for bellsound is used for the alarm when timer reaches 0.
The script includes three main functions. 'Study session' and 'break session' open the new windows with timers by taking inputs from input fields on the main window. These functions also include the function 'move time' inside that includes
the mechanism for time calculations in the timer.
