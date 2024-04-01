from packages.graphics import *

def main():
    win = GraphWin("Incubation Chamber Visualizer", 500, 500)
    win.setBackground(color_rgb(255,255,255))

    inputBox = Entry(Point(250,250), 10)
    inputBox.draw(win)

    win.getMouse()
    win.close()

main()