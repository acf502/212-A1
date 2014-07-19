# ass1.make -- makefile for Ass1
# to run: make
# to clean: make clean

ass1 : main.o linkedlist.o
	g++ -o ass1 main.o linkedlist.o
# above, we are saying ass1 depends on main.o, ass1.o list.o btree.o 
# and to create ass1 we give the g++ command as shown on the next line

# which starts with a TAB (although you cannot see that).
# note that the command : g++ -o ass1 main.o ass1.o list.o btree.o 
# creates an executable file named ass1 from the 2 object files respectively.
main.o: main.cpp linkedlist.h
	g++ -c main.cpp
# above we are saying main.o depends on main.cpp and ass1.h
# and to compile only main.cpp if and only if main.cpp or ass1.h
# have changed since the last creation of main.o

linkedlist.o: linkedlist.cpp  linkedlist.h
	g++ -c linkedlist.cpp
# above we are saying linkedlist.o depends on linkedlist.cpp and linkedlist.h
# so if either linkedlist.cpp or linkedlist.h CHANGED since creating linkedlist.o
# compile linkedlist.cpp again

clean:
	rm *.o ass1
# above we are stating how to run the rule for clean, no dependencies,
# what we want is when we ask to do a "make -f ass1.make clean"
# that will not do anything except remove executable and object files
# so we can "clean out" our directory of unneeded large files.
# we only do a make clean when we want to clean up the files.

# END OF MAKE FILE
