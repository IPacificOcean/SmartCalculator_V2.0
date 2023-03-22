GCC = g++ -std=c++17 -g -Wall -Werror -Wextra
TEST = ./tests/*.cc
SOURCE = ./model/fasad/model.cc ./model/executors/calculator_exec.cc \
 		 ./model/executors/parser.cc ./model/executors/validator.cc \
 		 ./model/executors/credit_exec.cc ./model/executors/debit_exec.cc \
 		 ./model/executors/plot.cc
SOURCE_CONTR = ./controller/controller.cc
SOURCE_VIEW = ./view/calculator.cc ./view/credit.cc ./view/debit.cc
HADS = ./view/calculator.h ./view/credit.h ./view/debit.h \
		./controller/controller.cc \
		./model/fasad/model.h ./model/executors/calculator_exec.h \
        ./model/executors/parser.h ./model/executors/validator.h \
        ./model/executors/credit_exec.h ./model/executors/debit_exec.h \
        ./model/executors/plot.h
HADS_UI = ./view/ui_calculator.h ./view/ui_credit.h ./view/ui_debit.h
GCOV =--coverage
LIBA = *.a
LIBO = *.o

OS = $(shell uname)

ifeq ($(OS), Darwin)
	LIBFLAGS = -lm -lgtest -lstdc++ -lgtest_main
else
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs gtest  --libs gtest_main`
endif

all: install

#tests:
#	clear
#	$(GCC) $(TEST) $(SOURCE) $(LIBFLAGS)  -o test
#	./test

#tests:
#	g++  -std=c++17 -lm -lstdc++ -lgtest_main -lgtest  -Wall -Werror -Wextra ./tests/tests.cc ./model/fasad/model.cc ./model/executors/calculator_exec.cc ./model/executors/parser.cc ./model/executors/validator.cc ./model/executors/credit_exec.cc ./model/executors/debit_exec.cc  ./model/executors/plot.cc -o test


clean:
	rm -rf *.o *.a  *.out test *.dSYM  report coverage.info *.gcda *.gcno *.txt *.tgz

build_app:
	mkdir build_app
	cd build_app && qmake ../view && make && make clean

install: build_app
	cd build_app && open s21_smart_calc.app

uninstall:
	rm -rf build_app

dvi:
	open dvi.html

dist:
	rm -rf Archive_SmartCalc_v2.0/
	mkdir Archive_SmartCalc_v2.0/
	mkdir Archive_SmartCalc_v2.0/src
	cp -r ./view ./controller ./model ./tests dvi.html Makefile Archive_SmartCalc_v2.0/src/
	tar cvzf Archive_SmartCalc_v2.0.tgz Archive_SmartCalc_v2.0/
	rm -rf Archive_SmartCalc_v2.0/


s21_smart_calc.o:
	$(GCC) -c $(TEST) $(SOURCE)


s21_smart_calc.a: s21_smart_calc.o
	ar rcs $(LIBA) $(LIBO)

tests: s21_smart_calc.a
	$(GCC) $(TEST) $(SOURCE) $(LIBFLAGS) -o test
	./test

gcov_report: s21_smart_calc.a
	$(GCC) $(GCOV) $(TEST) $(SOURCE) $(LIBA) -L. $(LIBA)  $(LIBFLAGS) -o test
	./test
	lcov -t "test" -c -d  ./ --no-external --output-file ./coverage.info
	genhtml ./coverage.info --output-directory ./report/
	open ./report/index.html

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(SOURCE) $(SOURCE_CONTR) $(SOURCE_VIEW) $(HADS) $(HADS_UI)
	@clang-format  -i $(SOURCE) $(SOURCE_CONTR) $(SOURCE_VIEW) $(HADS)
	clang-format -n $(SOURCE) $(SOURCE_CONTR) $(SOURCE_VIEW) $(HADS)

ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif
