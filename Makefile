all: sharedPool
sharedPool: sharedPool.o hdlDHCP.o hdlCache.o ssp.o spd.o
	gcc -g -o sharedPool sharedPool.o hdlDHCP.o hdlCache.o ssp.o spd.o -lpthread -lsqlite3

sharedPool.o: sharedPool.c
	gcc -g -c sharedPool.c -o sharedPool.o -lpthread

hdlDHCP.o: hdlDHCP.c
	gcc -g -c hdlDHCP.c -o hdlDHCP.o
	
hdlCache.o: hdlCache.c
	gcc -g -c hdlCache.c -o hdlCache.o

ssp.o: ssp.c
	gcc -g -c ssp.c -o ssp.o

spd.o: spd.c
	gcc -g -c spd.c -o spd.o

clean:
	rm sharedPool sharedPool.o hdlDHCP.o hdlCache.o ssp.o spd.o
