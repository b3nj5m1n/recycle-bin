 
CC = g++

CFLAGS_CMN = -std=c++20
CFLAGS = -Wall -g $(CFLAGS_CMN)
CFLAGS_OBJ = -c $(CFLAGS_CMN)

DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin

main: obj_main
	$(CC) $(CFLAGS) -o $(DIR_BIN)/main $(DIR_OBJ)/main.o
 
obj_main: $(DIR_SRC)/main.cpp
	$(CC) $(CFLAGS_OBJ) $(DIR_SRC)/main.cpp -o $(DIR_OBJ)/main.o
 
# main: obj_main obj_BinarySearchTree
# 	$(CC) $(CFLAGS) -o $(DIR_BIN)/main $(DIR_OBJ)/main.o $(DIR_OBJ)/BinarySearchTree.o
 
# obj_main: $(DIR_SRC)/main.cpp obj_BinarySearchTree
# 	$(CC) $(CFLAGS_OBJ) $(DIR_SRC)/main.cpp -o $(DIR_OBJ)/main.o
 
# obj_BinarySearchTree: $(DIR_SRC)/BinarySearchTree.h
# 	$(CC) $(CFLAGS_OBJ) $(DIR_SRC)/BinarySearchTree.h -o $(DIR_OBJ)/BinarySearchTree.o
