a.out: chart.o ../storage/storage.o test.c
	cc -o $@ $^

chart.o: ./chart.c ./chart.h
storage.o: ../storage/storage.c ../storage/storage.h

test:
	./a.out

clean:
	rm *.o *~
