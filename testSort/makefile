TARGETS = sort mergeEx bitonic

OUTDIR = ./bin/
OUT_SORT_TEST = $(OUTDIR)sort
OUT_MERGEX_TEST = $(OUTDIR)mergeEx
OUT_BITONIC = $(OUTDIR)bitonic

all: $(TARGETS)

sort: mkdir clean
	gcc testSort.c ../sort/sort.c ../utils/arrayUtils.c ../sort/comparator/compare.c ../sort/comparator/saveComparation.c -o $(OUT_SORT_TEST)

mergeEx: mkdir clean
	gcc testLibMergeExchange.c ../lib/mergeExchange/mergExchange.c ../utils/arrayUtils.c -o $(OUT_MERGEX_TEST)

bitonic: mkdir clean
	gcc testLibBitonic.c -o $(OUT_BITONIC)

mkdir:
	mkdir -p $(OUTDIR)

clean:
	rm -f $(OUTDIR)*