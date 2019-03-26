all:
	cd spider && make;
	cd chatserver && make
clean:
	cd spider && make clean;
	cd chatserver && make clean;