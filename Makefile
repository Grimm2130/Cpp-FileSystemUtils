DIR_BUILD=Build

clean:
	@if [ -e ${DIR_BUILD} ];	\
	then					\
		rm -r ${DIR_BUILD};	\
	fi;

rebase:
	@if ! [ -e ${DIR_BUILD} ];	\
	then						\
		mkdir ${DIR_BUILD};		\
	fi;

build-debug:
	@cd ${DIR_BUILD} && cmake -S .. -B . -DCMAKE_BUILD_TYPE=DEBUG && cmake --build .

build:
	@cd ${DIR_BUILD} && cmake -S .. -B . && cmake --build .

rebuild-debug: clean rebase build-debug

rebuild: clean rebase build

run-tests-debug:
	@gdb ./${DIR_BUILD}/Tests/Test;

run-tests:
	@./${DIR_BUILD}/Tests/All;