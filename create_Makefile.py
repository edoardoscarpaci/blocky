import os
import argparse


parser = argparse.ArgumentParser(
    description="Create A Makefile for your c++ program to easy compile your source code")


def setParser():
    parser.add_argument(
        "-path", default=os.path.dirname(os.path.abspath(__file__))+"/")
    parser.add_argument(
        "-src", default=os.path.dirname(os.path.abspath(__file__))+"/src/")
    parser.add_argument("-filename", default="main")
    parser.add_argument("-i", nargs="+", default=["include/"])
    parser.add_argument("-flags", nargs="+", default=["-Wall"])
    parser.add_argument("-d", default="yes")
    parser.add_argument("-wx", default="no")


setParser()
src = vars(parser.parse_args()).get("src")
path = vars(parser.parse_args()).get("path")
filepath = []


for (dirname, subdirname, filenames) in os.walk(src):
    for name in filenames:
        filepath.append((dirname + name).replace(path, ""))

namefile = vars(parser.parse_args()).get("filename")


def writeVariable(vFile):
    f.write("TARGET= " +
            namefile + "\n" + "INCLUDE_DIR= ")
    for dir in vars(parser.parse_args()).get("i"):
        f.write("-I" + dir + " ")
    if(vars(parser.parse_args()).get("wx") != "no"):
        f.write("-I/usr/include/wx-3.0/")
    f.write("\nSRC_DIR = -Isrc/")
    f.write("\n")
    f.write("FLAGS= ")
    for flags in vars(parser.parse_args()).get("flags"):
        f.write(flags + " ")
    if(vars(parser.parse_args()).get("d") == "yes"):
        f.write("-g ")
    if(vars(parser.parse_args()).get("wx") != "no"):
        f.write("`wx-config --cxxflags --libs`")
    f.write("\nLINKER= " + " \n")
    f.write("OBJECTS= ")
    for filename in filepath:
        index = filename.rfind("/")
        f.write(filename[index + 1:len(filename)-4] + ".o ")
    f.write("\n")
    f.write("BUILD_DIR= build/" + "\n\n\n")


def writeCompiler(vFile):
    f.write("default : $(BUILD_DIR)$(TARGET)\n")
    f.write("$(BUILD_DIR)$(TARGET) : $(OBJECTS)" + " \n")
    f.write("\tg++ $(OBJECTS) $(FLAGS) $(LINKER) -o $(BUILD_DIR)$(TARGET)" + "\n\n")

    for filename in filepath:
        index = filename.rfind("/")
        f.write(filename[index + 1:len(filename) - 4] + ".o " +
                ": " + filename.replace(path, "") + "\n")
        f.write("\tg++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c " +
                filename.replace(path, "") + "\n\n")

    f.write("clean : \n\t rm -f *.o")


with open("Makefile", "w+") as f:
    writeVariable(f)
    writeCompiler(f)
