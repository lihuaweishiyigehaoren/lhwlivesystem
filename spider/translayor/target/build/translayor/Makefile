-include Makefile.config

-include ../Makefile.deps

OBJS := __-__-__-src-PackageDataSink_cpp.o \
__-__-__-src-EventQueueLoop_cpp.o \
__-__-__-src-Net_cpp.o \
__-__-__-src-EPollClient_cpp.o \
__-__-__-src-EPollConnection_cpp.o \
__-__-__-src-EPollServer_cpp.o \
__-__-__-src-EPollStream_cpp.o \
__-__-__-src-EpollLoop_cpp.o \
__-__-__-src-CommonUtils_cpp.o \
__-__-__-src-http-String_cpp.o \
__-__-__-src-ThreadPool_cpp.o \
__-__-__-src-http-HttpConnection_cpp.o \
__-__-__-src-http-HttpContext_cpp.o \
__-__-__-src-http-HttpRequest_cpp.o \
__-__-__-src-http-HttpResponse_cpp.o \
__-__-__-src-http-HttpServer_cpp.o

all: libtranslayor.so

libtranslayor.so: $(OBJS)
	@echo -e "\e[32m[LINK] \033[0mlibtranslayor.so"
	@$(LD) $(OBJS) -shared -o libtranslayor.so -L"$(LOGGING_LIB)" -llogging -lpthread

install: ../../lib/libtranslayor.so

../../lib/libtranslayor.so: libtranslayor.so
	@echo -e "\e[32m[INSTALL] \033[0mlibtranslayor.so -> ../../lib"
	@cp libtranslayor.so ../../lib

clean:
	@echo -e "\e[32m[CLEAN] \033[0mlibtranslayor.so"
	@rm -f libtranslayor.so
	@rm -f *.o

__-__-__-src-PackageDataSink_cpp.o: ../../../src/PackageDataSink.cpp \
 ../../../src/PackageDataSink.h \
 ../../../src/DataSink.h ../../../src/Net.h \
 ../../../src/NetLinux.h \
 ../../../src/ByteArray.h \
 ../../../src/Exendian.h \
 ../../../src/ThreadPool.h \
 ../../../src/ConcurrentQueue.h \
 ../../../src/thread_pool.tcc \
 ../../../src/EventQueue.h \
 ../../../src/http/HttpContext.h \
 ../../../src/http/HttpRequest.h \
 ../../../src/http/HttpResponse.h
	@echo -e "\e[32m[CXX] \033[0m../../../src/PackageDataSink.cpp -> $@"
	@$(CXX) ../../../src/PackageDataSink.cpp -c -o $@ -I../../../src $(LOGGING_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG

__-__-__-src-EventQueueLoop_cpp.o: ../../../src/EventQueueLoop.cpp \
 ../../../src/EventQueueLoop.h \
 ../../../src/Loop.h ../../../src/EventQueue.h \
 ../../../src/ByteArray.h \
 ../../../src/Exendian.h
	@echo -e "\e[32m[CXX] \033[0m../../../src/EventQueueLoop.cpp -> $@"
	@$(CXX) ../../../src/EventQueueLoop.cpp -c -o $@ -I../../../src $(LOGGING_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG

__-__-__-src-Net_cpp.o: ../../../src/Net.cpp ../../../src/Net.h \
 ../../../src/NetLinux.h \
 ../../../src/ByteArray.h \
 ../../../src/Exendian.h
	@echo -e "\e[32m[CXX] \033[0m../../../src/Net.cpp -> $@"
	@$(CXX) ../../../src/Net.cpp -c -o $@ -I../../../src $(LOGGING_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG

__-__-__-src-EPollClient_cpp.o: ../../../src/EPollClient.cpp \
 ../../../src/EPollLoop.h \
 ../../../src/Loop.h \
 ../../../src/EPollConnection.h \
 ../../../src/NetLinux.h \
 ../../../src/Net.h \
 ../../../src/NetLinux.h \
 ../../../src/ByteArray.h \
 ../../../src/Exendian.h \
 ../../../src/EPollStream.h \
 ../../../src/EPollServer.h \
 ../../../src/PackageDataSink.h \
 ../../../src/DataSink.h \
 ../../../src/ThreadPool.h \
 ../../../src/ConcurrentQueue.h \
 ../../../src/thread_pool.tcc \
 ../../../src/EPollClient.h \
 ../../../src/DataSink.h \
 ../../../src/Common.h \
 ../../../src/CommonUtils.h
	@echo -e "\e[32m[CXX] \033[0m../../../src/EPollClient.cpp -> $@"
	@$(CXX) ../../../src/EPollClient.cpp -c -o $@ -I../../../src $(LOGGING_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG

__-__-__-src-EPollConnection_cpp.o: ../../../src/EPollConnection.cpp \
 ../../../src/EPollLoop.h \
 ../../../src/Loop.h \
 ../../../src/EPollConnection.h \
 ../../../src/NetLinux.h \
 ../../../src/Net.h \
 ../../../src/NetLinux.h \
 ../../../src/ByteArray.h \
 ../../../src/Exendian.h \
 ../../../src/EPollStream.h \
 ../../../src/EPollServer.h \
 ../../../src/PackageDataSink.h \
 ../../../src/DataSink.h \
 ../../../src/ThreadPool.h \
 ../../../src/ConcurrentQueue.h \
 ../../../src/thread_pool.tcc \
 ../../../src/EPollClient.h \
 ../../../src/DataSink.h \
 ../../../src/Common.h 
	@echo -e "\e[32m[CXX] \033[0m../../../src/EPollConnection.cpp -> $@"
	@$(CXX) ../../../src/EPollConnection.cpp -c -o $@ -I../../../src $(LOGGING_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG

__-__-__-src-EPollServer_cpp.o: ../../../src/EPollServer.cpp \
 ../../../src/EPollServer.h \
 ../../../src/Net.h \
 ../../../src/NetLinux.h \
 ../../../src/ByteArray.h \
 ../../../src/Exendian.h \
 ../../../src/PackageDataSink.h \
 ../../../src/DataSink.h \
 ../../../src/ThreadPool.h \
 ../../../src/ConcurrentQueue.h \
 ../../../src/thread_pool.tcc \
 ../../../src/EPollConnection.h \
 ../../../src/NetLinux.h \
 ../../../src/EPollStream.h \
 ../../../src/EPollLoop.h \
 ../../../src/Loop.h \
 ../../../src/EPollClient.h \
 ../../../src/DataSink.h \
 ../../../src/Common.h \
 ../../../src/CommonUtils.h 
	@echo -e "\e[32m[CXX] \033[0m../../../src/EPollServer.cpp -> $@"
	@$(CXX) ../../../src//EPollServer.cpp -c -o $@ -I../../../src $(LOGGING_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG

__-__-__-src-EPollStream_cpp.o: ../../../src/EPollStream.cpp \
 ../../../src/EPollStream.h \
 ../../../src/NetLinux.h \
 ../../../src/Net.h \
 ../../../src/NetLinux.h \
 ../../../src/ByteArray.h \
 ../../../src/Exendian.h \
 ../../../src/EPollLoop.h \
 ../../../src/Loop.h \
 ../../../src/EPollConnection.h \
 ../../../src/EPollServer.h \
 ../../../src/PackageDataSink.h \
 ../../../src/DataSink.h \
 ../../../src/ThreadPool.h \
 ../../../src/ConcurrentQueue.h \
 ../../../src/thread_pool.tcc \
 ../../../src/EPollClient.h \
 ../../../src/DataSink.h \
 ../../../src/Common.h 
	@echo -e "\e[32m[CXX] \033[0m../../../src/EPollStream.cpp -> $@"
	@$(CXX) ../../../src/EPollStream.cpp -c -o $@ -I../../../src $(LOGGING_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG

__-__-__-src-EpollLoop_cpp.o: ../../../src/EPollLoop.cpp \
 ../../../src/EPollLoop.h \
 ../../../src/Loop.h \
 ../../../src/EPollConnection.h \
 ../../../src/NetLinux.h \
 ../../../src/Net.h \
 ../../../src/NetLinux.h \
 ../../../src/ByteArray.h \
 ../../../src/Exendian.h \
 ../../../src/EPollStream.h \
 ../../../src/EPollServer.h \
 ../../../src/PackageDataSink.h \
 ../../../src/DataSink.h \
 ../../../src/ThreadPool.h \
 ../../../src/ConcurrentQueue.h \
 ../../../src/thread_pool.tcc \
 ../../../src/EPollClient.h \
 ../../../src/DataSink.h \
 ../../../src/Common.h 
	@echo -e "\e[32m[CXX] \033[0m../../../src/EpollLoop.cpp -> $@"
	@$(CXX) ../../../src/EPollLoop.cpp -c -o $@ -I../../../src $(LOGGING_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG

__-__-__-src-CommonUtils_cpp.o: ../../../src/CommonUtils.cpp \
 ../../../src/CommonUtils.h
	@echo -e "\e[32m[CXX] \033[0m../../../src/CommonUtils.cpp -> $@"
	@$(CXX) ../../../src/CommonUtils.cpp -c -o $@ -I../../../src $(LOGGING_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG

__-__-__-src-http-String_cpp.o: ../../../src/http/String.cpp \
 ../../../src/http/String.h
	@echo -e "\e[32m[CXX] \033[0m../../../src/http/String.cpp -> $@"
	@$(CXX) ../../../src/http/String.cpp -c -o $@ -I../../../src $(LOGGING_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG

__-__-__-src-ThreadPool_cpp.o: ../../../src/ThreadPool.cpp \
 ../../../src/ThreadPool.h \
 ../../../src/ConcurrentQueue.h \
 ../../../src/thread_pool.tcc 
	@echo -e "\e[32m[CXX] \033[0m../../../src/ThreadPool.cpp -> $@"
	@$(CXX) ../../../src/ThreadPool.cpp -c -o $@ -I../../../src $(LOGGING_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG

__-__-__-src-http-HttpConnection_cpp.o: ../../../src/http/HttpConnection.cpp \
 ../../../src/TransLayor.h ../../../src/IoLoop.h \
 ../../../src/EPollLoop.h \
 ../../../src/Loop.h \
 ../../../src/EPollConnection.h \
 ../../../src/NetLinux.h \
 ../../../src/Net.h \
 ../../../src/NetLinux.h \
 ../../../src/ByteArray.h \
 ../../../src/Exendian.h \
 ../../../src/EPollStream.h \
 ../../../src/EPollServer.h \
 ../../../src/PackageDataSink.h \
 ../../../src/DataSink.h \
 ../../../src/ThreadPool.h \
 ../../../src/ConcurrentQueue.h \
 ../../../src/thread_pool.tcc \
 ../../../src/EPollClient.h \
 ../../../src/DataSink.h \
 ../../../src/Common.h \
 ../../../src/EPollClient.h \
 ../../../src/EPollConnection.h \
 ../../../src/EPollServer.h \
 ../../../src/EPollStream.h \
 ../../../src/http/HttpConnection.h \
 ../../../src/http/HttpRequest.h \
 ../../../src/http/HttpContext.h \
 ../../../src/http/HttpResponse.h 
	@echo -e "\e[32m[CXX] \033[0m../../../src/http/HttpConnection.cpp -> $@"
	@$(CXX) ../../../src/http/HttpConnection.cpp -c -o $@ -I../../../include $(LOGGING_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG

__-__-__-src-http-HttpContext_cpp.o: ../../../src/http/HttpContext.cpp \
 ../../../src/http/HttpContext.h \
 ../../../src/ByteArray.h \
 ../../../src/Exendian.h \
 ../../../src/http/String.h
	@echo -e "\e[32m[CXX] \033[0m../../../src/http/HttpContext.cpp -> $@"
	@$(CXX) ../../../src/http/HttpContext.cpp -c -o $@ -I../../../src $(LOGGING_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG

__-__-__-src-http-HttpRequest_cpp.o: ../../../src/http/HttpRequest.cpp \
 ../../../src/http/HttpRequest.h \
 ../../../src/http/HttpContext.h \
 ../../../src/ByteArray.h \
 ../../../src/Exendian.h \
 ../../../src/http/String.h
	@echo -e "\e[32m[CXX] \033[0m../../../src/http/HttpRequest.cpp -> $@"
	@$(CXX) ../../../src/http/HttpRequest.cpp -c -o $@ -I../../../src $(LOGGING_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG

__-__-__-src-http-HttpResponse_cpp.o: ../../../src/http/HttpResponse.cpp \
 ../../../src/http/HttpResponse.h \
 ../../../src/http/HttpContext.h \
 ../../../src/ByteArray.h \
 ../../../src/Exendian.h \
 ../../../src/http/String.h
	@echo -e "\e[32m[CXX] \033[0m../../../src/http/HttpResponse.cpp -> $@"
	@$(CXX) ../../../src/http/HttpResponse.cpp -c -o $@ -I../../../src $(LOGGING_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG

__-__-__-src-http-HttpServer_cpp.o: ../../../src/http/HttpServer.cpp \
 ../../../src/http/HttpServer.h \
 ../../../src/TransLayor.h ../../../src/IoLoop.h \
 ../../../src/EPollLoop.h \
 ../../../src/Loop.h \
 ../../../src/EPollConnection.h \
 ../../../src/NetLinux.h \
 ../../../src/Net.h \
 ../../../src/NetLinux.h \
 ../../../src/ByteArray.h \
 ../../../src/Exendian.h \
 ../../../src/EPollStream.h \
 ../../../src/EPollServer.h \
 ../../../src/PackageDataSink.h \
 ../../../src/DataSink.h \
 ../../../src/ThreadPool.h \
 ../../../src/ConcurrentQueue.h \
 ../../../src/thread_pool.tcc \
 ../../../src/EPollClient.h \
 ../../../src/DataSink.h \
 ../../../src/Common.h \
 ../../../src/EPollClient.h \
 ../../../src/EPollConnection.h \
 ../../../src/EPollServer.h \
 ../../../src/EPollStream.h \
 ../../../src/http/HttpConnection.h \
 ../../../src/http/HttpRequest.h \
 ../../../src/http/HttpContext.h \
 ../../../src/http/HttpResponse.h
	@echo -e "\e[32m[CXX] \033[0m../../../src/http/HttpServer.cpp -> $@"
	@$(CXX) ../../../src/http/HttpServer.cpp -c -o $@ -I../../../src $(LOGGING_INCLUDE) -std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG

