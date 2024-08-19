from packages.graphics import *
from tkinter import *
import socket
from tkinter import messagebox
import sys



def main():

    # Create object 
    tempHighThresh, tempLowThresh, currentTemp, hourLimit, hours = 0,0,0,0,0
    root = Tk()

    def clear(*widgets):
        s.sendto("Hello from server",b"192.168.168.182")
        for widget in widgets:
            widget.destroy() #finally we are deleting the widgets.
        

    # Adjust size 
    root.geometry( "500x500" )
    root.title("Incubation Chamber Visualizer") 
    

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

        label.config( text = clicked.get() + " is selected (not connected)." ) 

        # button was pressed
        print("Button Pressed!")
        print("Creating server...")
        global s
        s = socket.socket()
        s.bind(('0.0.0.0', 8090))
        s.listen(0)
        
        while True:


                client, addr = s.accept()
                if addr[0] in clicked.get():
                    label.config( text = clicked.get() + " is connected." )
                    #print("address is : ")
                    #print(addr[0])
                    #print(type(addr[0]))
                    while True:
                            content = client.recv(512)
                            if len(content) == 0:
                                break
                            else:
                                print(content)
                                print(type(content))
                                #content = content.decode("utf-8")
                                tempHighThresh, tempLowThresh, currentTemp, hourLimit, hours = content.split(b',')
                    print("Closing connection")
                    print("tempHighThresh == ",tempHighThresh) ## REMOVE
                    print("tempLowThresh ==", tempLowThresh) ## REMOVE
                    print("currentTemp == ", currentTemp) ## REMOVE
                    print("hourLimit == ", hourLimit) ## REMOVE
                    print("hours == ", hours) ## REMOVE
                    label_tempHighThresh = Label( root , text = ("The High temp threshold from chamber is "+str(tempHighThresh)))
                    label_tempHighThresh.pack() 
                    label_tempLowThresh = Label( root , text = ("The Low temp threshold from chamber is "+str(tempLowThresh)))
                    label_tempLowThresh.pack() 
                    label_currentTemp = Label( root , text = ("The current temp of the chamber is "+str(currentTemp)))
                    label_currentTemp.pack() 
                    label_hourLimit = Label( root , text = ("The amount of hours the chamber *will* run is "+str(hourLimit)))
                    label_hourLimit.pack() 
                    label_hours = Label( root , text = ("The amount of hours the chamber *has* run is "+str(hours)))
                    label_hours.pack() 
                    entry_label_tempHighThresh = tk.Label(root, text = 'Enter High temp threshold', font=('calibre',10, 'bold'))
                    entry_grid_tempHighThresh = tk.Entry(root, textvariable = "", font=('calibre',10,'normal'))
                    entry_label_tempHighThresh.pack()
                    entry_grid_tempHighThresh.pack()

                    #entry_label_tempHighThresh.grid(row=0,column=0)
                    #entry_grid_tempHighThresh.grid(row=0,column=1)

                    entry_label_tempLowThresh = tk.Label(root, text = 'Enter Low temp threshold', font=('calibre',10, 'bold'))
                    entry_grid_tempLowThresh = tk.Entry(root, textvariable = "", font=('calibre',10,'normal'))
                    entry_label_tempLowThresh.pack()
                    entry_grid_tempLowThresh.pack()
                    #entry_label_tempLowThresh.grid(row=0,column=0)
                    #entry_grid_tempLowThresh.grid(row=0,column=1)

                    entry_label_hourLimit = tk.Label(root, text = 'Enter Hour limit', font=('calibre',10, 'bold'))
                    entry_grid_hourLimit = tk.Entry(root, textvariable = "", font=('calibre',10,'normal'))
                    entry_label_hourLimit.pack()
                    entry_grid_hourLimit.pack()
                    #entry_label_hourLimit.grid(row=0,column=0)
                    #entry_grid_hourLimit.grid(row=0,column=1)
                    clear_btm=Button(root,text="Send") #this button will delete the widgets 
                    clear_btm["command"] = lambda one = label_tempHighThresh, two = label_tempLowThresh, three = label_currentTemp, four = label_hourLimit, five = label_hours, six = entry_label_tempHighThresh, seven = entry_label_tempLowThresh, eight = entry_label_hourLimit, nine = entry_grid_tempHighThresh, ten = entry_grid_tempLowThresh, eleven = entry_grid_hourLimit, twelve = clear_btm:clear(one,two,three,four,five,six,seven,eight,nine,ten,eleven,twelve) #pass the widgets
                    clear_btm.pack()



                    client.close()
                    return;
                else:
                    print("Closing connection")
                    client.close()
                    return;
            

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