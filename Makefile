a.out: main.o ./configF/configF.o ./storage/storage.o ./integ/integrate.o ./approx/approx.o ./approx/splines.o ./approx/points.o ./chart/chart.o
	cc -o $@ $^ ./approx/libge.a

main.o: main.c
configF.o: ./configF/configF.c ./configF/configF.h
storage.o: ./storage/storage.c ./storage/storage.h
integrate.o: ./integ/integrate.c ./integ/integrate.h
approx.o: ./approx/approx.c ./approx/approx.h
splines.o: ./approx/splines.c ./approx/splines.h
points.o: ./approx/points.c ./approx/points.h
chart.o: ./chart/chart.c ./chart/chart.h

test:
	./a.out chart

clear:
	rm a.out *.o ./configF/*.o ./storage/*.o ./integ/*.o ./approx/*.o ./chart/*.o
