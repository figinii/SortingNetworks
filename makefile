sort: sort.c arrayUtils.c testSort.c compare.c
	rm -f sort
	gcc testSort.c sort.c arrayUtils.c compare.c -o sort