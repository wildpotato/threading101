all: simpleTimeAndCount threadWithClassObj twoThreadsWaiting waitCounterNotify

clean:
	rm -f simpleTimeAndCount threadWithClassObj twoThreadsWaiting waitCounterNotify

simpleTimeAndCount: simpleTimeAndCount.cpp
	g++ -o simpleTimeAndCount simpleTimeAndCount.cpp -Wall -lpthread

threadWithClassObj: threadWithClassObj.cpp
	g++ -o threadWithClassObj threadWithClassObj.cpp -Wall -lpthread

twoThreadsWaiting: twoThreadsWaiting.cpp
	g++ -o twoThreadsWaiting twoThreadsWaiting.cpp -Wall -lpthread

waitCounterNotify: waitCounterNotify.cpp
	g++ -o waitCounterNotify waitCounterNotify.cpp -Wall -lpthread
