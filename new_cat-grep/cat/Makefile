SHELL := /bin/bash
FLAG = -Wall -Wextra -Werror
FILE = ../../common/cat_test.txt
CHECK = 2>&1 valgrind --tool=memcheck --leak-check=yes

all: s21_cat tests

s21_cat: clean
	gcc $(FLAG) cat.c -o s21_cat

tests:
	-diff <(./s21_cat $(FILE)) <(cat $(FILE))
	-diff <(./s21_cat -e $(FILE)) <(cat -e $(FILE))
	-diff <(./s21_cat -t $(FILE)) <(cat -t $(FILE))
	-diff <(./s21_cat -s $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat --squeeze-blank $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat -n $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat --number $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat -b $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat --number-nonblank $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat -etsnb $(FILE)) <(cat -etsnb $(FILE))

	$(CHECK) ./s21_cat $(FILE) | grep ERROR
	$(CHECK) ./s21_cat -n $(FILE) | grep ERROR
	$(CHECK) ./s21_cat -e $(FILE) | grep ERROR
	$(CHECK) ./s21_cat -t $(FILE) | grep ERROR
	$(CHECK) ./s21_cat -b $(FILE) | grep ERROR
	$(CHECK) ./s21_cat -s $(FILE) | grep ERROR
	$(CHECK) ./s21_cat -etsnb $(FILE) | grep ERROR

clean:
	rm -f s21_cat
