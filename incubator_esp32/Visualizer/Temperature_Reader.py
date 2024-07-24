from packages.graphics import *
from tkinter import *
import socket
from tkinter import messagebox
import sys

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
    def show(): 
        label.config( text = clicked.get() ) 
    
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
    clicked = StringVar() 
    
    # initial menu text 
    clicked.set( "Incubation Chamber #1 192.168.168.182" ) 
    
    # Create Dropdown menu 
    drop = OptionMenu( root , clicked , *options ) 
    drop.pack() 
    
    # Create button, it will change label text 
    button = Button( root , text = "Connect..." , command = show ).pack() 
    
    # Create Label 
    label = Label( root , text = " This Label" ) 
    label.pack() 

    root.protocol('WM_DELETE_WINDOW', lambda: sys.exit())
    # Execute tkinter 
    root.mainloop() 
    
    #button to close the window
    #Button(root, text="Quit", command=root.destroy).pack() 


   
main()