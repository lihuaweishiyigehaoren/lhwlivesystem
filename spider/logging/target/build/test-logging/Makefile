-include Makefile.config

-include ../Makefile.deps

OBJS := __-__-__-test-logging-main_cpp.o

all: test-logging

test-logging: $(OBJS)
	@echo -e "\e[32m[LINK] \033[0mtest-logging"
	@$(LD) $(OBJS) -o test-logging -L"../logging" -llogging 

install: ../../bin/test-logging

../../bin/test-logging: test-logging
	@echo -e "\e[32m[INSTALL] \033[0mtest-logging -> ../../bin"
	@cp test-logging ../../bin

clean:
	@echo -e "\e[32m[CLEAN] \033[0mtest-logging"
	@rm -f test-logging
	@rm -f *.o

__-__-__-test-logging-main_cpp.o: ../../../test/test-logging/main.cpp \
 ../../../src/Logging.h \
 ../../../src/Interface.h \
 ../../../src/Logger.h \
 ../../../src/Severity.h \
 ../../../src/LoggerStream.h \
 ../../../src/System.h \
 ../../../src/ExpressionLogger.h \
 ../../../src/CheckLogger.h \
 ../../../src/IOStreamManager.h \
 ../../../src/Check.h
	@echo -e "\e[32m[CXX] \033[0m../../../test/test-logging/main.cpp -> $@"
	@$(CXX) ../../../test/test-logging/main.cpp -c -o $@ -I../../../src -I../../../src -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DUSE_KLOG

