CC := g++
CFLAGS := -Wall -Wextra -Werror -std=c++17 -pedantic
UNITFLAGS1 := $(shell pkg-config --cflags gtest)
UNITFLAGS2 := $(shell pkg-config --libs gtest)

OBJS := ./out/s21_matrix_oop.o
UNITOBJS := ./out/s21_matrix_tests.o

all : clean test s21_matrix_oop.a

test : $(OBJS) $(UNITOBJS) s21_matrix_oop.a
	$(CC) -o test $(UNITOBJS) -DGTEST_HAS_PTHREAD=1 -I/usr/local/include -L/usr/local/lib -lgtest -lgtest_main -L. -ls21_matrix_oop  -fprofile-arcs -ftest-coverage
	./test

 s21_matrix_oop.a: $(OBJS)
	ar rc $@ $^
	ranlib $@
	cp $@ lib$@

./out/%.o : ./%.cpp ./s21_matrix_oop.h
	mkdir -p ./out
	$(CC) $(CFLAGS) $(UNITFLAGS1) $(COV_FLAG) -c $<
	mv ./*.o ./out/

./out/s21_matrix_tests.o : ./s21_matrix_tests.cpp
	mkdir -p ./out
	$(CC) $(CFLAGS) -c $< $(UNITFLAGS1)
	mv ./*.o ./out/

gcov_report : COV_FLAG += --coverage
gcov_report : clean test
	lcov -t "coverage" -o coverage.info -c -d .
	genhtml -o report coverage.info
	rm -rf ./*.g*
	# xdg-open ./report/index.html

clean :
	rm -f ./test
	rm -rf ./out
	rm -f ./*.a
	rm -rf *.gcda *.gcno report gcov_report.* gcov_report *.info
