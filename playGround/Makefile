CXX ?= g++
CXXFLAGS ?= -Werror -pedantic -g --std=c++17 -fsanitize=address -fsanitize=undefined

# Run a regression test
test: play.exe 
	./play.exe < input.in

tests: play.exe 
	./play.exe < ./tests/input*.in

custom: play.exe 
	./play.exe < test_input.txt
# Compile the main executable
play.exe: play.cpp
	$(CXX) $(CXXFLAGS) play.cpp -o play.exe

# Remove automatically generated files
clean :
	rm -rvf *.exe *~ *.out *.dSYM *.stackdump

# Disable built-in rules
.SUFFIXES:

# Run style check tools
CPD ?= /usr/um/pmd-6.0.1/bin/run.sh cpd
OCLINT ?= /usr/um/oclint-0.13/bin/oclint
FILES := stats.cpp stats_tests.cpp main.cpp
style :
	$(OCLINT) \
    -no-analytics \
    -rule=LongLine \
    -rule=HighNcssMethod \
    -rule=DeepNestedBlock \
    -rule=TooManyParameters \
    -rc=LONG_LINE=90 \
    -rc=NCSS_METHOD=40 \
    -rc=NESTED_BLOCK_DEPTH=4 \
    -rc=TOO_MANY_PARAMETERS=4 \
    -max-priority-1 0 \
    -max-priority-2 0 \
    -max-priority-3 0 \
    $(FILES) \
    -- -xc++ --std=c++11
	$(CPD) \
    --minimum-tokens 100 \
    --language cpp \
    --failOnViolation true \
    --files $(FILES)
	@echo "########################################"
	@echo "EECS 280 style checks PASS"

sync :
	rsync \
  -rtv \
  --delete \
  --exclude '.git*' \
  --filter=':- .gitignore' \
  ../p1-stats/ \
  leeyongs@login.engin.umich.edu:p1-stats-copy/
