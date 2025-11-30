CXX = g++
CXXFLAGS = -std=c++17 -O2 -pthread

all: libparallel_scheduler.so demo-application

libparallel_scheduler.so: parallel_scheduler.o
	$(CXX) -shared -o libparallel_scheduler.so parallel_scheduler.o

parallel_scheduler.o: parallel_scheduler.cpp parallel_scheduler.h
	$(CXX) $(CXXFLAGS) -fPIC -c parallel_scheduler.cpp

demo-application: demo.o libparallel_scheduler.so
	$(CXX) $(CXXFLAGS) demo.o -L. -lparallel_scheduler -o demo-application

demo.o: demo.cpp parallel_scheduler.h
	$(CXX) $(CXXFLAGS) -c demo.cpp

clean:
	rm -f *.o *.so demo-application
