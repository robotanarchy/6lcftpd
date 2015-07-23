COMPONENT:=socket
EXEC:=../../bin/test_$(COMPONENT)

CXX:=LANG=C g++ -std=c++11 -Wall -g -Werror
PKGCONFIG:=pkg-config
LIBS:=SDL2_net


valgrind: $(EXEC)
	valgrind $(EXEC)

run: $(EXEC)
	$(EXEC)

$(EXEC): test_$(COMPONENT).cpp ../../src/$(COMPONENT)/*.*pp
	mkdir -p ../../bin
	$(CXX) `$(PKGCONFIG) --cflags --libs $(LIBS)` -o $@ \
		test_$(COMPONENT).cpp ../../src/$(COMPONENT)/*.cpp

clean:
	rm $(EXEC) || true


.PHONY: clean run valgrind
