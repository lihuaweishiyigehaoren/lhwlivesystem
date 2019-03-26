all:
	cd spider && make;
	cd chatserver && make
	cd chatclient && make
clean:
	cd spider && make clean;
	cd chatserver && make clean;
	cd chatclient && make clean;