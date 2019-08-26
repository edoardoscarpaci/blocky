import os
import argparse


parser = argparse.ArgumentParser(
    description="Create A Makefile for your c++ program to easy compile your source code")


def setParser():
    parser.add_argument(
        "-path", default=os.path.dirname(os.path.abspath(__file__))+"/")
    parser.add_argument(
        "-src", default=os.path.dirname(os.path.abspath(__file__))+"/src/")
    parser.add_argument(
        "-include", default=os.path.dirname(os.path.abspath(__file__))+"/include/")
    parser.add_argument("-filename", default="main")
    parser.add_argument("-i", nargs="+", default=["include/"])  # include path
    parser.add_argument("-flags", nargs="+",
                        default=["-Wall", "-pthread"])  # add flags
    parser.add_argument("-d", action='count')  # debug mode
    parser.add_argument("-wx", action='count'
                        )  # wxWidgets compiler
    parser.add_argument("-opengl", action='count'
                        )  # openGL glad glfw glm
    parser.add_argument("-pch", action="count")  # Enable precompiled header


setParser()
src = vars(parser.parse_args()).get("src")
path = vars(parser.parse_args()).get("path")
include = vars(parser.parse_args()).get("include")

filepath = []

whitelistFormat = [".cpp", ".hpp", ".c", ".h"]

for (dirname, subdirname, filenames) in os.walk(path):
    for name in filenames:
        if(any(substring in name for substring in whitelistFormat) and name.find("pch") == -1):
            if(dirname[len(dirname) - 1] == "/"):
                filepath.append((dirname + name).replace(path, ""))
            else:
                filepath.append((dirname + "/" + name).replace(path, ""))


namefile = vars(parser.parse_args()).get("filename")


def writeVariable(vFile):
    f.write("TARGET= " +
            namefile + "\n" + "INCLUDE_DIR= ")
    f.write("-I./ ")
    for dir in vars(parser.parse_args()).get("i"):
        f.write("-I" + dir + " ")
    if(vars(parser.parse_args()).get("wx") != None):
        f.write("-I/usr/include/wx-3.0/")
    if(vars(parser.parse_args()).get("opengl") != None):
        f.write(
            " -I/usr/include/glad/  -I/usr/include/glm/  -I/usr/local/include/GLFW ")
    f.write("\nSRC_DIR = -Isrc/")
    f.write("\n")
    f.write("FLAGS= ")
    for flags in vars(parser.parse_args()).get("flags"):
        f.write(flags + " ")

    if(vars(parser.parse_args()).get("pch") != None):
        f.write(" -include pch.h ")

    if(vars(parser.parse_args()).get("d") != None):
        f.write("-g ")
        f.write("-D DEBUG  ")
    else:
        f.write("-O3 ")
    if(vars(parser.parse_args()).get("wx") != None):
        f.write("`wx-config --cxxflags --libs` ")

    if(vars(parser.parse_args()).get("opengl") != None):
        f.write("-ldl  `pkg-config --static --libs x11 xrandr xi xxf86vm glfw3`")

    f.write("\nLINKER= " + " \n")
    f.write("OBJECTS= ")
    for filename in filepath:
        index = filename.rfind("/")
        indexpoint = filename.rfind(".")
        if(any(substring in filename for substring in [".cpp", ".c"])):
            if(index != - 1):
                f.write(filename[index + 1: indexpoint] + ".o ")

            else:
                f.write(filename[:indexpoint] + ".o ")
    if(vars(parser.parse_args()).get("opengl") != None):
        f.write("glad.o")

    f.write("\nFILE_SRC= ")
    for filename in filepath:
        if(any(substring in filename for substring in [".cpp", ".c"])):
            index = filename.rfind("/")
            f.write(filename[index + 1:] + " ")

    f.write("\nFILE_INCLUDE= ")
    for filename in filepath:
        if(any(substring in filename for substring in [".hpp", ".h"])):
            index = filename.rfind("/")
            f.write(filename[index + 1:] + " ")

    f.write("\n")
    f.write("BUILD_DIR= build/" + "\n\n\n")


def writeCompiler(vFile):
    f.write("default : $(BUILD_DIR)$(TARGET)\n")
    f.write("$(BUILD_DIR)$(TARGET) : $(OBJECTS)" + " \n")
    f.write("\tg++ $(OBJECTS) $(FLAGS) $(LINKER) -o $(BUILD_DIR)$(TARGET)" + "\n\n")

    if(vars(parser.parse_args()).get("opengl") != None):
        f.write("glad.o: /usr/local/src/glad.c \n\tg++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c /usr/local/src/glad.c \n\n")

    if(vars(parser.parse_args()).get("pch") != None):
        f.write("pch.h.gch : pch.h \n\t g++ -c pch.h $(FLAGS) -o pch.h.gch \n\n")
        f.write("$(FILE_SRC) $(FILE_INCLUDE): pch.h.gch \n\n\n")
    for filename in filepath:
        if(not any(substring in filename for substring in [".hpp", ".h"])):
            index = filename.rfind(".")
            indexf = filename.rfind("/")
            if(indexf != -1):
                f.write((filename[indexf + 1:index] + ".o").replace("src/", "") +
                        ": " + filename + "\n")
            else:
                f.write((filename[:index] + ".o").replace("src/", "") +
                        ": " + filename + "\n")
            f.write("\tg++ $(FLAGS) $(SRC_DIR) $(INCLUDE_DIR) -c " +
                    filename + "\n\n")

    f.write("clean : \n\t rm -f *.o")


with open("Makefile", "w+") as f:
    writeVariable(f)
    writeCompiler(f)
