-include Makefile.config
-include ../Makefile.deps

OBJS := __-__-__-src-chatserver_cpp.o

all: chatserver

chatserver: $(OBJS)
	@echo -e "\e[32m[LINK] \033[0mchatserver"
	@$(LD) $(OBJS) -o chatserver $(TRANSLAYOR_LIB) $(LOGGING_LIB) -ltranslayor -llogging

install: ../../bin/chatserver

../../bin/chatserver: chatserver
	@echo -e "\e[32m[INSTALL] \033[0mchatserver -> ../../bin"
	@cp chatserver ../../bin

clean:
	@echo -e "\e[32m[CLEAN] \033[0mchatserver"
	@rm -f chatserver
	@rm -f *.o

__-__-__-src-chatserver_cpp.o: ../../../src/main.cpp \
 ../../../src/ServerEventQueueLoop.h \
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
	@$(CXX) ../../../src/main.cpp -c -o $@ -I../../../src  $(LOGGING_INCLUDE) $(TRANSLAYOR_INCLUDE) -std=c++11 -O2 -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG