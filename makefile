CC	= gcc
CFLAGS 	= -ansi -pedantic -Wall -g
RM	= rm -f
DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin
DIR_INPUT = ./input
DIR_OUTPUT = ./output
EXEC	= $(DIR_BIN)/huffman $(DIR_BIN)/huffman_d $(DIR_BIN)/print_arbre

SRC = $(wildcard ${DIR_SRC}/*.c)
OBJ = $(patsubst %.c,  ${DIR_OBJ}/%.o, $(notdir ${SRC}))
TARGET = $(patsubst %.o,  ${DIR_BIN}/%, $(notdir ${OBJ}))

all: ${EXEC} 
	

$(DIR_OUTPUT)/%.pdf: $(DIR_OUTPUT)%.dot
	@echo "Creating the tree $@"
	dot -Tpdf $< -o $@

$(DIR_OUTPUT)/%.dot: $(DIR_INPUT)/%.in
	./$(DIR_BIN)/print_arbre $< >$@

$(DIR_BIN)/test_codage: ${DIR_OBJ}/arbre.o ${DIR_OBJ}/coding.o ${DIR_OBJ}/foret.o ${DIR_OBJ}/freq.o ${DIR_OBJ}/test_codage.o
	$(CC) $^ -o $@
$(DIR_BIN)/print_arbre: ${DIR_OBJ}/arbre.o ${DIR_OBJ}/coding.o ${DIR_OBJ}/foret.o ${DIR_OBJ}/freq.o ${DIR_OBJ}/print_arbre.o
	$(CC) $^ -o $@
$(DIR_BIN)/huffman: ${DIR_OBJ}/arbre.o ${DIR_OBJ}/coding.o ${DIR_OBJ}/foret.o ${DIR_OBJ}/freq.o ${DIR_OBJ}/huffman.o
	$(CC) $^ -o $@
$(DIR_BIN)/huffman_d: ${DIR_OBJ}/arbre.o ${DIR_OBJ}/coding.o ${DIR_OBJ}/foret.o ${DIR_OBJ}/freq.o ${DIR_OBJ}/huffman_d.o
	$(CC) $^ -o $@

${DIR_OBJ}/%.o:${DIR_SRC}/%.c
	$(CC) $(CFLAGS) -c $< -o $@

xmp.in:
	echo "example of Huffman coding" >xmp.in

xmp.dot: xmp.in print_arbre
xmp.pdf: xmp.dot

.PHONY: clean fclean test

$(DIR_OUTPUT)/makefile_arbre.pdf: $(DIR_OUTPUT)/makefile_arbre.dot
$(DIR_OUTPUT)/makefile_arbre.dot: $(DIR_INPUT)/makefile_arbre.in $(DIR_BIN)/print_arbre
$(DIR_INPUT)/makefile_arbre.in: makefile
	cp $^ $@


# a test
test: $(DIR_BIN)/huffman_d $(DIR_BIN)/huffman $(DIR_OUTPUT)/makefile_arbre.pdf
	@echo Encoding the makefile
	./$(DIR_BIN)/huffman makefile >$(DIR_OUTPUT)/makefile_encoded.txt
	@echo Decoding what we got and checking if this is the initial file
	@echo "./$(DIR_BIN)/huffman_d <$(DIR_OUTPUT)/makefile_encoded.txt |diff - makefile"
	@if (./$(DIR_BIN)/huffman_d <$(DIR_OUTPUT)/makefile_encoded.txt |diff - makefile) ; then echo "File are identical" ; else echo "There is a difference" ; fi

clean:
	$(RM) $(DIR_BIN)/* $(DIR_OBJ)/*.o
	$(RM) $(DIR_OUTPUT)/*
	$(RM) *.txt

