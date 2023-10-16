# import tkinter GUI
import tkinter
# import rectpack to help pack rectangles
from rectpack import *
# import sys to access arguments
import sys


# Custom Canvas class
class CustomCanvas:
    # Constructor that takes in height and width and generates a tkinter canvas
    def __init__(self, h, w):
        self.canvas = tkinter.Canvas(height=h, width=w, bg="black")


# rectangle class to make a rectangle object
class Rectangle:
    # constructor takes in fields for height, width, and the x and y coordinates and stores them in variables
    def __init__(self, h, w, x=0, y=0):
        self.height = h
        self.width = w
        self.x = x
        self.y = y


# pack function that uses rectpack features to optimize storage using the rectangle dimensions and the canvas size given
def pack(allRect, canvasSize):
    # makes new packer object
    p = newPacker()
    # iterates through all rectangles, adding their sizes to the packer
    for r in allRect:
        p.add_rect(r.height, r.width)
    # adds a bin for the rectangles to fit in. In this case, 1 bin (the canvas) holds all the rectangles
    p.add_bin((canvasSize[0]), (canvasSize[1]))
    # calls the pack function defined in the rectpack import
    p.pack()
    # stores the packed rectangles in a list
    list_of_rects = p.rect_list()
    # initialize result list to store rectangle objects
    result_list = []
    # iterates through the rectangles packed by the packer object
    for rect in list_of_rects:
        # adds the rectangles to the result list while making rectangle objects
        result_list.append(Rectangle(rect[4], rect[3], rect[1], rect[2]))
    # returns the result list of rectangles
    return result_list


# main module
if __name__ == '__main__':
    # captures the second argument (the first being the python file) to be used as the file path
    arg1 = sys.argv[1]
    # open the file for reading
    text = open(arg1)
    # list to store the processed lines from the file
    lines = []
    # iterates through the lines parsed from the file, splitting at each comma to capture all ints line by line
    for line in text:
        # adds the dimensions to the lines array
        lines.append(line.split(","))
    # create the custom canvas object using the first line of the file
    specCanvas = CustomCanvas(int(lines[0][0]), int(lines[0][1]))
    # list to store the rectangle tuples that will be passed to the pack function
    list_of_recs = []
    # toggle variable that will skip the first line of the lines array (which contains the size of the canvas
    toggle = 0
    # iterates through the lines, using the dimensions to make rectangles, except for the canvas dimensions
    for f in lines:
        # flip the toggle to skip the first line
        if toggle == 0:
            toggle = 1
        else:
            # adds new rectangles to the list of rectangles
            list_of_recs.append(Rectangle(int(f[0]), int(f[1])))
    # uses the previously declared pack function to pack the rectangles into the canvas, using the list of recs
    # and the dimensions of the custom canvas
    pack(list_of_recs, (int(lines[0][0]), int(lines[0][1])))
