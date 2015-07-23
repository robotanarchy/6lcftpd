COMPONENT:=session
ADDITIONAL_CPP:=../../src/socket/*.cpp ../../src/config/*.cpp
ADDITIONAL_HPP:=../../src/socket/*.hpp ../../src/config/*.hpp

EXEC:=bin/test_$(COMPONENT)
EXECDIR:=../../
EXECFULL:=$(EXECDIR)$(EXEC)
CXX:=LANG=C g++ -std=c++11 -Wall -g -Werror
PKGCONFIG:=pkg-config
LIBS:=SDL2_net


valgrind: $(EXECFULL)
	cd $(EXECDIR) && valgrind $(EXEC)

run: $(EXECFULL)
	cd $(EXECDIR) && $(EXEC)

$(EXECFULL): test_$(COMPONENT).cpp ../../src/$(COMPONENT)/*.*pp $(ADDITIONAL_CPP) $(ADDITIONAL_HPP)
	mkdir -p ../../bin
	$(CXX) `$(PKGCONFIG) --cflags --libs $(LIBS)` -o $@ \
		test_$(COMPONENT).cpp ../../src/$(COMPONENT)/*.cpp \
		$(ADDITIONAL_CPP)

clean:
	rm $(EXECFULL) || true


.PHONY: clean run valgrind
