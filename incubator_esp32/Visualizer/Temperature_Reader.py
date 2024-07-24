from packages.graphics import *
from tkinter import *
import socket
from tkinter import messagebox
import sys

#buttonClicked  = False # Before first click

def main():
    #win = GraphWin("Incubation Chamber Visualizer", 500, 500)
    #win.setBackground(color_rgb(255,255,255))
    '''
    print("Creating server...")
    s = socket.socket()
    s.bind(('0.0.0.0', 8090))
    s.listen(0)
    
    while True:
            # TODO: Add this to tkinter
            client, addr = s.accept()
            while True:
                    content = client.recv(32)
                    if len(content) == 0:
                            break
                    else:
                            print(content)
            print("Closing connection")
            client.close()
    '''
    # Create object 

    root = Tk() 

    # Adjust size 
    root.geometry( "500x500" )
    root.title("Incubation Chamber Visualizer") 
    
    # Change the label text 
    #def show(): 
    #    label.config( text = clicked.get() + " is Selected" ) 
    
    # Dropdown menu options 
    options = [ 
        "Incubation Chamber #1 192.168.168.182", 
        "Incubation Chamber #2 192.168.168.183", 
        "Incubation Chamber #3 192.168.168.184", 
        "Incubation Chamber #4 192.168.168.185", 
        "Incubation Chamber #5 192.168.168.186", 
        "Incubation Chamber #6 192.168.168.187", 
        "Incubation Chamber #7 192.168.168.188"
    ] 
    
    # datatype of menu text 
    clicked = StringVar(root) 
    
    # initial menu text 
    clicked.set( "Incubation Chamber #1 192.168.168.182") 


    # Create Dropdown menu 
    drop = OptionMenu( root , clicked, *options,) 
    drop.pack() 

   
    
    def ButtonPress():
        label.config( text = clicked.get() + " is Selected" ) 
        #global buttonClicked
        #buttonClicked = not buttonClicked 

        # button was pressed
        print("Button Pressed!")

    # before the first click
    
    # Create button, it will change label text 
    button = Button( root , text = "Connect..." , command = ButtonPress ).pack() 

    # Create Label 
    label = Label( root , text = "No Chamber Selected" ) 
    label.pack() 

    # Close the window when the system [x] button is pressed 
    root.protocol('WM_DELETE_WINDOW', lambda: sys.exit())
    # Execute tkinter loop 
    root.mainloop() 
    


   
main()