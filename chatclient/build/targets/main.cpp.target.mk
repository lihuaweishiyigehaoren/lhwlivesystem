build/objs/main.cpp.o :src/main.cpp ../spider/translayor/src/Net.h \
 ../spider/translayor/src/ByteArray.h ../spider/translayor/src/NetLinux.h \
 ../spider/translayor/src/EventQueue.h \
 ../spider/translayor/src/EventQueueLoop.h \
 ../spider/translayor/src/Loop.h ../spider/translayor/src/IoLoop.h \
 ../spider/translayor/src/EPollLoop.h \
 ../spider/translayor/src/EPollConnection.h \
 ../spider/translayor/src/EPollStream.h \
 ../spider/translayor/src/EPollServer.h \
 ../spider/translayor/src/PackageDataSink.h \
 ../spider/translayor/src/DataSink.h \
 ../spider/translayor/src/ThreadPool.h \
 ../spider/translayor/src/ConcurrentQueue.h \
 ../spider/translayor/src/thread_pool.tcc \
 ../spider/translayor/src/EPollClient.h ../spider/translayor/src/Common.h \
 ../spider/logging/src/Logging.h ../spider/logging/src/Interface.h \
 ../spider/logging/src/Logger.h ../spider/logging/src/Severity.h \
 ../spider/logging/src/LoggerStream.h ../spider/logging/src/System.h \
 ../spider/logging/src/ExpressionLogger.h \
 ../spider/logging/src/CheckLogger.h \
 ../spider/logging/src/IOStreamManager.h ../spider/logging/src/Check.h
	@mkdir -pv $(dir $@)
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) -o $@ $<

