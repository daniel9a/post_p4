defrag.out : defragmenter.o DefragRunner.o mynew.o QuadraticProbing.o  
	g++ -ansi -Wall -o defrag.out defragmenter.o DefragRunner.o mynew.o QuadraticProbing.o  

defragmenter.o : defragmenter.cpp defragmenter.h DefragRunner.h QuadraticProbing.h 
	g++ -ansi -Wall -c defragmenter.cpp

DefragRunner.o : DefragRunner.cpp DefragRunner.h mynew.h CPUTimer.h defragmenter.h 
	g++ -ansi -Wall -c DefragRunner.cpp

mynew.o : mynew.cpp mynew.h 
	g++ -ansi -Wall -c mynew.cpp

QuadraticProbing.o : QuadraticProbing.cpp QuadraticProbing.h 
	g++ -ansi -Wall -c QuadraticProbing.cpp

clean : 
	rm -f defrag.out defragmenter.o  DefragRunner.o  mynew.o  QuadraticProbing.o   
