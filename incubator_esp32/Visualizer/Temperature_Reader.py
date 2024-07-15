from packages.graphics import *
from tkinter import *

def main():
    #win = GraphWin("Incubation Chamber Visualizer", 500, 500)
    #win.setBackground(color_rgb(255,255,255))

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
    clicked.set( "Monday" ) 
    
    # Create Dropdown menu 
    drop = OptionMenu( root , clicked , *options ) 
    drop.pack() 
    
    # Create button, it will change label text 
    button = Button( root , text = "Connect..." , command = show ).pack() 
    
    # Create Label 
    label = Label( root , text = " " ) 
    label.pack() 
    
    # Execute tkinter 
    root.mainloop() 

   
main()