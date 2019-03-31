all:
	cd spider/logging/target/build && make;
	cd spider/translayor/target/build && make;
	cd chatserver/target/build && make
	cd chatclient/target/build && make
clean:
	cd spider/logging/target/build && make clean;
	cd spider/translayor/target/build && make clean;
	cd chatserver/target/build && make clean;
	cd chatclient/target/build && make clean;
install:
	cd spider/logging/target/build && make install;
	cd spider/translayor/target/build && make install;
	cd chatserver/target/build && make install;
	cd chatclient/target/build && make install;
