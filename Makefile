# Executable names:
EXE = encounters
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = encounter.o data_reader.o kdtree.o main.o graph.o

# Use the cs225 makefile template:
include cs225/make/cs225.mk
