CXX=LANG=C g++ -std=c++11 -Wall -g -Werror




valgrind: bin/6lcftpd
	valgrind bin/6lcftpd

run: bin/6lcftpd
	bin/6lcftpd

bin/6lcftpd: src/*.cpp src/*.hpp
	mkdir -p bin
	$(CXX) -o $@ src/*.cpp

clean:
	rm bin/6lcftpd || true


.PHONY: clean run valgrind
