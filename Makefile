# Executable names:
EXE = encounters
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o data_reader.o kd_tree.o avl_tree.o

# Use the cs225 makefile template:
include cs225/make/cs225.mk