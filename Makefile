all: prog

prog:
	@mkdir -p bin
	make -C src
	@cp src/prog ./bin

debug:
	@mkdir -p bin
	make -C src debug
	@cp src/prog ./bin/prog-debug

# valgrind:
# 	@mkdir -p bin
# 	make -C src debug
# 	@cp src/prog ./bin/prog-debug
# 	valgrind --leak-check=full --track-origins=yes ./bin/prog-debug
#
# test:
# 	make -C test/
# 	@mkdir -p bin
# 	@cp test/test ./bin
# 	@./bin/test

.PHONY : clean test

clean :
	make clean -C test
	make clean -C src
	rm -rf bin
