-include Makefile.config
-include ../Makefile.deps

OBJS := __-__-__-src-chatclient_cpp.o

all: chatclient

chatclient: $(OBJS)
	@echo -e "\e[32m[LINK] \033[0mchatclient"
	@$(LD) $(OBJS) -o chatclient $(TRANSLAYOR_LIB) $(LOGGING_LIB) -ltranslayor -llogging

install: ../../bin/chatclient

../../bin/chatclient: chatclient
	@echo -e "\e[32m[INSTALL] \033[0mchatclient -> ../../bin"
	@cp chatclient ../../bin

clean:
	@echo -e "\e[32m[CLEAN] \033[0mchatclient"
	@rm -f chatclient
	@rm -f *.o

__-__-__-src-chatclient_cpp.o: ../../../src/main.cpp \
 ../../../../spider/translayor/src/Net.h \
 ../../../../spider/translayor/src/NetLinux.h \
 ../../../../spider/translayor/src/ByteArray.h \
 ../../../../spider/translayor/src/Exendian.h \
 ../../../../spider/translayor/src/EventQueue.h \
 ../../../../spider/translayor/src/EventQueueLoop.h \
 ../../../../spider/translayor/src/Loop.h ../../../../spider/translayor/src/IoLoop.h \
 ../../../../spider/translayor/src/EPollLoop.h \
 ../../../../spider/translayor/src/EPollConnection.h \
 ../../../../spider/translayor/src/NetLinux.h \
 ../../../../spider/translayor/src/EPollStream.h \
 ../../../../spider/translayor/src/EPollServer.h \
 ../../../../spider/translayor/src/PackageDataSink.h \
 ../../../../spider/translayor/src/DataSink.h \
 ../../../../spider/translayor/src/ThreadPool.h \
 ../../../../spider/translayor/src/ConcurrentQueue.h \
 ../../../../spider/translayor/src/thread_pool.tcc \
 ../../../../spider/translayor/src/EPollClient.h \
 ../../../../spider/translayor/src/DataSink.h \
 ../../../../spider/translayor/src/Common.h \
 ../../../../spider/translayor/src/TransLayor.h \
 ../../../../spider/translayor/src/EPollClient.h \
 ../../../../spider/translayor/src/EPollConnection.h \
 ../../../../spider/translayor/src/EPollServer.h \
 ../../../../spider/translayor/src/EPollStream.h \
 ../../../../spider/translayor/src/http/HttpServer.h \
 ../../../../spider/translayor/src/http/HttpConnection.h \
 ../../../../spider/translayor/src/http/HttpRequest.h \
 ../../../../spider/translayor/src/http/HttpContext.h \
 ../../../../spider/translayor/src/http/HttpResponse.h
	@echo -e "\e[32m[CXX] \033[0m../../../src/main.cpp -> $@"
	@$(CXX) ../../../src/main.cpp -c -o $@ -I../../../src  $(LOGGING_INCLUDE) $(TRANSLAYOR_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG