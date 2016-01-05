#
# Makefile
#
# Computer Science 50
# Problem Set 3
#

whodunit: whodunit.c Makefile
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -Wno-unused-variable -o whodunit whodunit.c -lcs -lm

resize: resize.c Makefile
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -Wno-unused-variable -o resize resize.c -lcs -lm

clean:
	rm -f *.o resize whodunit
