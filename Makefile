
all:
	@test -r build/Makefile || make configure
	make -C build all

configure:
	@echo '==============> Configuring Build'
	@-(cd build/; ln -s ../lib; ln -s ../src; ln -s ../test)
	@cd build/ && ./autogen.sh && ./$@

install:
	make -C build install

clean:
	make -C build clean

deep-clean:
	make -C build deep-clean
	unlink build/lib
	unlink build/src
	unlink build/test

test : all
	make -C build test
