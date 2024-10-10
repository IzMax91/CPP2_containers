CC = g++
FLAGS = -Wall -Werror -Wextra -std=c++17 -lm -fprofile-arcs -ftest-coverage
OS= $(shell uname)

ifeq ("$(OS)","Linux")
	TEST_FLAGS = -lgtest -lpthread
else
	TEST_FLAGS = -lgtest
endif

all: test gcov_report

test:
	${CC} ${FLAGS} tests/*.cc -o test.out ${TEST_FLAGS}
	./test.out

gcov_report:
	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	open ./report/index.html

clean:
	rm -f *.o *.obj *.out *.gcda *.gcno *.info
	rm -rf report

rebuild: clean all
