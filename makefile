all: 2220193626_sh test
2220193626_sh:main.o lazyshell.o CMD.o
	g++  $^ -o $@
main.o:main.cc lazyshell.hh 
lazyshell.o: *.hh 
test: test.cc
	g++ -o test test.cc
CMD.o: CMD.hh
clean:
	rm -f *.o