snackaroo: snackaroo.o snackaroo_dish.o snackaroo_driver.o snackaroo_relationship.o
	gcc -o snackaroo snackaroo.o snackaroo_dish.o snackaroo_driver.o snackaroo_relationship.o

snackaroo.o: snackaroo.c snackaroo.h snackaroo_dish.h snackaroo_driver.h snackaroo_relationship.h
	gcc -c snackaroo.c

snackaroo_dish.o: snackaroo_dish.c snackaroo_dish.h snackaroo_relationship.h
	gcc -c snackaroo_dish.c

snackaroo_driver.o: snackaroo_driver.c snackaroo_driver.h snackaroo_relationship.h
	gcc -c snackaroo_driver.c

snackaroo_relationship.o: snackaroo_relationship.c snackaroo_relationship.h snackaroo_dish.h snackaroo_driver.h
	gcc -c snackaroo_relationship.c