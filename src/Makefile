CC=g++
CFLAGS=-Wall -Werror -Wextra -g -lstdc++ -std=c++17
TFLAGS=-g -c -Wall -Werror -Wextra -g -lstdc++ -std=c++17 -lgtest -Wuninitialized -pedantic
GTEST=-lgtest -lgtest_main -pthread
ASAN=-fsanitize=address
COVER=-fprofile-arcs -ftest-coverage

all: Smart_calc_2.0.a 
all2:	clean	Smart_calc_2.0.a	test	gcov_report

Smart_calc_2.0.a:
	$(CC) $(TFLAGS) ./Smart_calculator_Qt/model/model.cpp -o model.o
	ar rcs model.a model.o
	ranlib model.a
test: clean
	@ g++ $(CFLAGS) $(ASAN) $(COVER) test.cpp ./Smart_calculator_Qt/model/model.cpp -o test $(GTEST)
	./test
gcov_report: test
	geninfo --ignore-errors mismatch . -b . -o ./coverage.info --no-external 
	genhtml coverage.info -o ./coverage
	open coverage/index.html
leaks:
	@ g++ -fsanitize=address -g $(TFLAGS) ./Smart_calculator_Qt/model/model.cpp ./Smart_calculator_Qt/model/model.h test.cpp
	g++ -fsanitize=address -g *.o -o test -lgtest
	leaks -atExit -- ./test

test_CMake: build 
	./build/CPP3_s21_SmartCalc_0

build: CMakeLists.txt ./Smart_calculator_Qt/model/model.h ./Smart_calculator_Qt/model/model.cpp test.cpp

	mkdir -p build
	cd build && cmake .. && make

clean:
	rm -rf *.o *.a *.css index.html *.gcno *.gcda *.out *.info test report.* *.dSYM *.gcov build* *.gch SmartCalc_dist Smart_calc.tar.gz ./Smart_calculator_Qt/CmakeCache.txt ./Smart_calculator_Qt/*.cmake ./Smart_calculator_Qt/*autogen ./Smart_calculator_Qt/CMakeFiles rm -rf coverage
clang_format:
#	 cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config */*.cpp *.h
	cp ../materials/linters/.clang-format ../.clang-format
	clang-format -i  ./Smart_calculator_Qt/*.h
	clang-format -i *.cpp ./Smart_calculator_Qt/*.cpp
	clang-format -n  ./Smart_calculator_Qt/*.h
	clang-format -n *.cpp ./Smart_calculator_Qt/*.cpp
	rm -rf ../.clang-format


generatedvi:
	cd doxygen && ./doxygen Doxyfile

dvi:
	open ./doxygen/html/index.html

# install:
# 	@mkdir build
# 	cd build; cmake ..; cmake --build .


install:
	cd Smart_calculator_Qt && cmake . && $(MAKE) all

run:
	open ./Smart_calculator_Qt/Smart_calculator_Qt.app

uninstall:
# rm -rf build
	rm -rf ./Smart_calculator_Qt/*.app
# clean 

 
dist: 
#	rm -rf Smart_calc_dist
	@mkdir Smart_calc_dist
	cp ./Smart_calculator_Qt/*.cpp Smart_calc_dist
	cp ./Smart_calculator_Qt/*.h Smart_calc_dist
	cp ./Smart_calculator_Qt/CMakeLists.txt.user Smart_calc_dist
#	cp *.txt Smart_calc_dist
	cp ./Smart_calculator_Qt/*.cpp Smart_calc_dist
	cp ./Smart_calculator_Qt/view/*.ui Smart_calc_dist
	cp Makefile Smart_calc_dist
	tar -czf Smart_calc.tar.gz Smart_calc_dist/
	rm -rf Smart_calc_dist



