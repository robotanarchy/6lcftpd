CXX=LANG=C g++ -std=c++11


run: bin/6lcftpd
	bin/6lcftpd


bin/6lcftpd: src/*.cpp src/*.hpp
	mkdir -p bin
	$(CXX) -o $@ src/*.cpp


clean:
	rm bin/6lcftpd || true


.PHONY: clean run
