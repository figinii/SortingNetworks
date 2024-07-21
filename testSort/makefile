OUTDIR = ./bin/
OUT_SORT_TEST = $(OUTDIR)sort

sort: mkdir clean
	gcc testSort.c ../sort/sort.c ../utils/arrayUtils.c ../sort/comparator/compare.c ../sort/comparator/saveComparation.c -o $(OUT_SORT_TEST)

mkdir:
	mkdir -p $(OUTDIR)

clean:
	rm -f $(OUT)