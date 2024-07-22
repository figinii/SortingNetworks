TARGETS = sort lib

OUTDIR = ./bin/
OUT_SORT_TEST = $(OUTDIR)sort
OUT_LIB_TEST = $(OUTDIR)lib

all: $(TARGETS)

sort: mkdir clean
	gcc testSort.c ../sort/sort.c ../utils/arrayUtils.c ../sort/comparator/compare.c ../sort/comparator/saveComparation.c -o $(OUT_SORT_TEST)

lib: mkdir clean
	gcc testLib.c ../lib/mergExchange.c ../utils/arrayUtils.c -o $(OUT_LIB_TEST)

mkdir:
	mkdir -p $(OUTDIR)

clean:
	rm -f $(OUT_SORT_TEST)
	rm -f $(OUT_LIB_TEST)