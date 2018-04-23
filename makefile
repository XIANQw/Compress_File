CC	= gcc
CFLAGS 	= -ansi -pedantic -Wall -g
RM	= rm -f
EXEC	= huffman huffman_d print_arbre

all: $(EXEC)

%.pdf: %.dot
	@echo "Creating the tree $@"
	dot -Tpdf $< -o $@

%.dot: %.in
	./print_arbre $< >$@
test_codage: arbre.o coding.o foret.o freq.o test_codage.o
print_arbre: arbre.o coding.o foret.o freq.o print_arbre.o
huffman: arbre.o coding.o foret.o freq.o huffman.o
huffman_d: arbre.o coding.o foret.o freq.o huffman_d.o

arbre.o: arbre.c arbre.h
coding.o: coding.c coding.h freq.h arbre.h foret.h
foret.o: foret.c foret.h arbre.h
freq.o: freq.c freq.h
huffman.o: huffman.c freq.h
huffman_d.o: huffman_d.c freq.h arbre.h coding.h
print_arbre.o: print_arbre.c freq.h arbre.h coding.h

xmp.in:
	echo "example of Huffman coding" >xmp.in

xmp.dot: xmp.in print_arbre
xmp.pdf: xmp.dot

.PHONY: clean fclean test

makefile_arbre.pdf: makefile_arbre.dot
makefile_arbre.dot: makefile_arbre.in print_arbre
makefile_arbre.in: makefile
	cp makefile makefile_arbre.in


# a test
test: huffman_d huffman makefile_arbre.pdf
	@echo Encoding the makefile
	./huffman makefile >makefile_encoded.txt
	@echo Decoding what we got and checking if this is the initial file
	@echo "./huffman_d <makefile_encoded.txt |diff - makefile"
	@if (./huffman_d <makefile_encoded.txt |diff - makefile) ; then echo "File are identical" ; else echo "There is a difference" ; fi

clean:
	$(RM) *~ *.o *.dot
	$(RM) makefile_arbre.in xmp.in makefile_encoded.txt frequence.txt

fclean: clean
	$(RM) $(EXEC) *.pdf
