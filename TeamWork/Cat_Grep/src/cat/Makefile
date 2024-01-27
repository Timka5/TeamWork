SHELL := /bin/bash
CC = gcc
CFLAGS = -Wall -Wextra -Werror
FILE = test.txt
FILE1 = test1.txt
FILEH = HI.txt

all: s21_cat clean_o errors

s21_cat: cat.o cat_f.o
	$(CC) $(CFLAGS) -o s21_cat cat.o cat_f.o

cat.o: s21_cat.c
	$(CC) $(CFLAGS) -c s21_cat.c -o cat.o

cat_f.o: cat_f.c cat_f.h
	$(CC) $(CFLAGS) -c cat_f.c -o cat_f.o

rebuild: clean all

errors:
	clang-format -n cat_f.c cat_f.h s21_cat.c
	valgrind ./s21_cat test1.txt test.txt --leak-check=full

clean:
	rm -f *.o s21_cat
clean_o:
	rm -f *.o
test:
	-diff <(./s21_cat $(FILE)) <(cat $(FILE))
	-diff <(./s21_cat -b $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat -e $(FILE)) <(cat -e $(FILE))
	-diff <(./s21_cat -n $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat -s $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat -t $(FILE)) <(cat -t $(FILE))
	-diff <(./s21_cat -v $(FILE)) <(cat -v $(FILE))
	-diff <(./s21_cat -E $(FILE)) <(cat -E $(FILE))
	-diff <(./s21_cat -T $(FILE)) <(cat -T $(FILE))
	-diff <(./s21_cat --squeeze-blank $(FILE)) <(cat --squeeze-blank $(FILE))
	-diff <(./s21_cat --number $(FILE)) <(cat --number $(FILE))
	-diff <(./s21_cat --number-nonblank $(FILE)) <(cat --number-nonblank $(FILE))
	-diff <(./s21_cat -bn $(FILE)) <(cat -bn $(FILE))
	-diff <(./s21_cat -sETb $(FILE)) <(cat -sETb $(FILE))
	-diff <(./s21_cat -be $(FILE)) <(cat -be $(FILE))
	-diff <(./s21_cat -bs $(FILE)) <(cat -bs $(FILE))
	-diff <(./s21_cat -bt $(FILE)) <(cat -bt $(FILE))
	-diff <(./s21_cat -bE $(FILE)) <(cat -bE $(FILE))
	-diff <(./s21_cat -bT $(FILE)) <(cat -bT $(FILE))
	-diff <(./s21_cat -bv $(FILE)) <(cat -bv $(FILE))
	-diff <(./s21_cat -en $(FILE)) <(cat -en $(FILE))
	-diff <(./s21_cat -es $(FILE)) <(cat -es $(FILE))
	-diff <(./s21_cat -et $(FILE)) <(cat -et $(FILE))
	-diff <(./s21_cat -ns $(FILE)) <(cat -ns $(FILE))
	-diff <(./s21_cat -nt $(FILE)) <(cat -nt $(FILE))
	-diff <(./s21_cat -nv $(FILE)) <(cat -nv $(FILE))
	-diff <(./s21_cat -nE $(FILE)) <(cat -nE $(FILE))
	-diff <(./s21_cat -nT $(FILE)) <(cat -nT $(FILE))
	-diff <(./s21_cat -st $(FILE)) <(cat -st $(FILE))
	-diff <(./s21_cat -sv $(FILE)) <(cat -sv $(FILE))
	-diff <(./s21_cat -sE $(FILE)) <(cat -sE $(FILE))
	-diff <(./s21_cat -sT $(FILE)) <(cat -sT $(FILE))
	-diff <(./s21_cat -bes $(FILE)) <(cat -bes $(FILE))
	-diff <(./s21_cat -bet $(FILE)) <(cat -bet $(FILE))
	-diff <(./s21_cat -bev $(FILE)) <(cat -bev $(FILE))
	-diff <(./s21_cat -beT $(FILE)) <(cat -beT $(FILE))
	-diff <(./s21_cat -bst $(FILE)) <(cat -bst $(FILE))
	-diff <(./s21_cat -bsT $(FILE)) <(cat -bsT $(FILE))
	-diff <(./s21_cat -bsv $(FILE)) <(cat -bsv $(FILE))
	-diff <(./s21_cat -btv $(FILE)) <(cat -btv $(FILE))
	-diff <(./s21_cat -btE $(FILE)) <(cat -btE $(FILE))
	-diff <(./s21_cat -bEs $(FILE)) <(cat -bEs $(FILE))
	-diff <(./s21_cat -bEt $(FILE)) <(cat -bEt $(FILE))
	-diff <(./s21_cat -bET $(FILE)) <(cat -bET $(FILE))
	-diff <(./s21_cat -bEv $(FILE)) <(cat -bEv $(FILE))
	-diff <(./s21_cat -bTv $(FILE)) <(cat -bTv $(FILE))
	-diff <(./s21_cat -ens $(FILE)) <(cat -ens $(FILE))
	-diff <(./s21_cat -ent $(FILE)) <(cat -ent $(FILE))
	-diff <(./s21_cat -enT $(FILE)) <(cat -enT $(FILE))
	-diff <(./s21_cat -esn $(FILE)) <(cat -esn $(FILE))
	-diff <(./s21_cat -est $(FILE)) <(cat -est $(FILE))
	-diff <(./s21_cat -esT $(FILE)) <(cat -esT $(FILE))
	-diff <(./s21_cat $(FILE) $(FILE1)) <(cat $(FILE) $(FILE1))
	-diff <(./s21_cat -sv $(FILE) $(FILE1)) <(cat -sv $(FILE) $(FILE1))
	-diff <(./s21_cat -sb $(FILE) $(FILE1)) <(cat -sb $(FILE) $(FILE1))
	-diff <(./s21_cat -es $(FILE) $(FILE1)) <(cat -es $(FILE) $(FILE1))
	-diff <(./s21_cat -Tn $(FILE) $(FILE1)) <(cat -Tn $(FILE) $(FILE1))
	-diff <(./s21_cat $(FILEH)) <(cat $(FILEH))