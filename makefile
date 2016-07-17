# http://stackoverflow.com/questions/31176997/what-does-clang-check-do-without-analyze-option

FILES :=                          \
    Graph.h                       \
    Graph.log                     \
    html                          \
    TestGraph.c++                 \
    TestGraph.out

# uncomment these:
#    graph-tests/EID-TestGraph.c++ \
#    graph-tests/EID-TestGraph.out \

CXXFLAGS := -pedantic -std=c++11 -Wall
LDFLAGS  := -lgtest -lgtest_main -pthread
VALGRIND := valgrind

ifeq ($(CC), clang)
    CLANG-CHECK  := clang-check
    CXX          := clang++
else
    CXX          := g++-4.8
    GCOV         := gcov-4.8
    GCOVFLAGS    := -fprofile-arcs -ftest-coverage
endif

ifeq ($(CI), true)
    CLANG-FORMAT := clang-format
else
    CLANG-FORMAT := clang-format-3.4
endif

graph-tests:
	git clone https://github.com/cs371g-summer-2016/graph-tests.git

html: Doxyfile Graph.h TestGraph.c++
	doxygen Doxyfile

Graph.log:
	git log > Graph.log

Doxyfile:
	doxygen -g
	# you must manually edit Doxyfile and
	# set EXTRACT_ALL     to YES
	# set EXTRACT_PRIVATE to YES
	# set EXTRACT_STATEIC to YES

TestGraph: Graph.h TestGraph.c++
ifeq ($(CC), clang)
	$(CXX) $(CXXFLAGS) TestGraph.c++ -o TestGraph $(LDFLAGS)
	-$(CLANG-CHECK) -extra-arg=-std=c++11          TestGraph.c++ --
	-$(CLANG-CHECK) -extra-arg=-std=c++11 -analyze TestGraph.c++ --
else
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) TestGraph.c++ -o TestGraph $(LDFLAGS)
endif

TestGraph.tmp: TestGraph
	$(VALGRIND) ./TestGraph                                       >  TestGraph.tmp 2>&1
ifeq ($(CC), gcc)
	$(GCOV) -b TestGraph.c++ | grep -A 5 "File 'TestGraph.c++'" >> TestGraph.tmp
endif
	cat TestGraph.tmp

check:
	@not_found=0;                                 \
    for i in $(FILES);                            \
    do                                            \
        if [ -e $$i ];                            \
        then                                      \
            echo "$$i found";                     \
        else                                      \
            echo "$$i NOT FOUND";                 \
            not_found=`expr "$$not_found" + "1"`; \
        fi                                        \
    done;                                         \
    if [ $$not_found -ne 0 ];                     \
    then                                          \
        echo "$$not_found failures";              \
        exit 1;                                   \
    fi;                                           \
    echo "success";

clean:
	rm -f  *.gcda
	rm -f  *.gcno
	rm -f  *.gcov
	rm -f  *.plist
	rm -f  Graph.log
	rm -f  Doxyfile
	rm -f  gmon.out
	rm -f  TestGraph
	rm -f  TestGraph.tmp
	rm -rf graph-tests
	rm -rf html
	rm -rf latex

config:
	git config -l

format:
	$(CLANG-FORMAT) -i Graph.h
	$(CLANG-FORMAT) -i TestGraph.c++

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: html Graph.log TestGraph.tmp graph-tests check
