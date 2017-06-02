CC = g++
CFLAGS = -Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++11 	
LDFLAGS = $(CFLAGS) -lcrypto 


all: main.o CRecord.o CDatabase.o CInteract.o CLogin.o
		$(CC) $(LDFLAGS) main.o CRecord.o CDatabase.o CLogin.o CInteract.o CMainPassword.o -o friedtad
main.o: main.cpp CInteract.h CDatabase.h CRecord.h CLogin.h CMainPassword.h
		$(CC) $(CFLAGS) -c main.cpp -o main.o	
CInteract.o: CInteract.cpp CInteract.h CDatabase.h CRecord.h CLogin.h CMainPassword.h
		$(CC) $(CFLAGS) -c CInteract.cpp -o CInteract.o 
CMainPassword.o: CMainPassword.cpp CDatabase.h CRecord.h CLogin.h CMainPassword.h
		$(CC) $(CFLAGS) -c CMainPassword.cpp -o CMainPassword.o 
CDatabase.o: CDatabase.cpp CDatabase.h CRecord.h CLogin.h CMainPassword.h CMainPassword.h
		$(CC) $(CFLAGS) -c CDatabase.cpp -o CDatabase.o 
CLogin.o: CLogin.cpp CLogin.h CRecord.h
		$(CC) $(CFLAGS) -c CLogin.cpp -o CLogin.o 
CRecord.o: CRecord.cpp CRecord.h
		$(CC) $(CFLAGS) -c CRecord.cpp -o CRecord.o 
compile: all 
	$(CC)  $(LDFLAGS) ./CLogin.o ./CRecord.o ./CDatabase.o ./CInteract.o ./main.o ./CMainPassword.o -o friedtad
run: friedtad
	./friedtad
.PHONY: doc
doc: 
	doxygen Doxyfile
.PHONY: clean
clean:
	rm -f friedtad
	rm -f PMinic.txt
	rm -f PMbackup.txt
	rm -f *.o
	rm -rf doc/
