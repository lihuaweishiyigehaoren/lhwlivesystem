-include Makefile.config

-include ../Makefile.deps

OBJS := __-__-__-src-CheckLogger_cpp.o \
__-__-__-src-ExpressionLogger_cpp.o \
__-__-__-src-Logger_cpp.o \
__-__-__-src-IOStreamManager_cpp.o \
__-__-__-src-DirectLoggerStream_cpp.o \
__-__-__-src-Logging_cpp.o

all: liblogging.so

liblogging.so: $(OBJS)
	@echo -e "\e[32m[LINK] \033[0mliblogging.so"
	@$(LD) $(OBJS) -shared -o liblogging.so   

install: ../../lib/liblogging.so

../../lib/liblogging.so: liblogging.so
	@echo -e "\e[32m[INSTALL] \033[0mliblogging.so -> ../../lib"
	@cp liblogging.so ../../lib

clean:
	@echo -e "\e[32m[CLEAN] \033[0mliblogging.so"
	@rm -f liblogging.so
	@rm -f *.o

__-__-__-src-CheckLogger_cpp.o: ../../../src/CheckLogger.cpp \
 ../../../src/CheckLogger.h \
 ../../../src/ExpressionLogger.h \
 ../../../src/Logger.h \
 ../../../src/Severity.h \
 ../../../src/LoggerStream.h \
 ../../../src/System.h
	@echo -e "\e[32m[CXX] \033[0m../../../src/CheckLogger.cpp -> $@"
	@$(CXX) ../../../src/CheckLogger.cpp -c -o $@ -I../../../src -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DUSE_KLOG

__-__-__-src-ExpressionLogger_cpp.o: ../../../src/ExpressionLogger.cpp \
 ../../../src/ExpressionLogger.h \
 ../../../src/Logger.h \
 ../../../src/Severity.h \
 ../../../src/LoggerStream.h \
 ../../../src/System.h
	@echo -e "\e[32m[CXX] \033[0m../../../src/ExpressionLogger.cpp -> $@"
	@$(CXX) ../../../src/ExpressionLogger.cpp -c -o $@ -I../../../src -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DUSE_KLOG

__-__-__-src-Logger_cpp.o: ../../../src/Logger.cpp \
 ../../../src/Logger.h \
 ../../../src/Severity.h \
 ../../../src/LoggerStream.h \
 ../../../src/System.h \
 ../../../src/DirectLoggerStream.h
	@echo -e "\e[32m[CXX] \033[0m../../../src/Logger.cpp -> $@"
	@$(CXX) ../../../src/Logger.cpp -c -o $@ -I../../../src -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DUSE_KLOG

__-__-__-src-IOStreamManager_cpp.o: ../../../src/IOStreamManager.cpp \
 ../../../src/IOStreamManager.h \
 ../../../src/Severity.h
	@echo -e "\e[32m[CXX] \033[0m../../../src/IOStreamManager.cpp -> $@"
	@$(CXX) ../../../src/IOStreamManager.cpp -c -o $@ -I../../../src -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DUSE_KLOG

__-__-__-src-DirectLoggerStream_cpp.o: \
 ../../../src/DirectLoggerStream.cpp \
 ../../../src/DirectLoggerStream.h \
 ../../../src/LoggerStream.h \
 ../../../src/Severity.h \
 ../../../src/IOStreamManager.h
	@echo -e "\e[32m[CXX] \033[0m../../../src/DirectLoggerStream.cpp -> $@"
	@$(CXX) ../../../src/DirectLoggerStream.cpp -c -o $@ -I../../../src -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DUSE_KLOG

__-__-__-src-Logging_cpp.o: ../../../src/Logging.cpp \
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
	@echo -e "\e[32m[CXX] \033[0m../../../src/Logging.cpp -> $@"
	@$(CXX) ../../../src/Logging.cpp -c -o $@ -I../../../src -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DUSE_KLOG

