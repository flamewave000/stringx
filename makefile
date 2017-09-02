library: src/strx_manip.cpp src/strx_format.cpp
	g++ -std=c++14 -c src/strx_manip.cpp src/strx_format.cpp
	@mkdir -p lib
	ar rcs lib/libstringx.a strx_manip.o strx_format.o
	@rm strx_manip.o strx_format.o
	
sample: library samples/main.cpp
	g++ -std=c++14 -static samples/main.cpp -Llib -lstringx -o sample
	
clean:
	rm -Rf lib/ sample strx_manip.o strx_format.o || true