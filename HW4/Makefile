# in EC327, we use the ${GCC} compiler
# therefore, we define the GCC variable
GCC = g++ 


test: 5.o
	${GCC} 5.o -o test
	
5.o: 5_new.cpp
	${GCC} -c 5_new.cpp

clean:
	rm 5.o test 
