OUTDIR = ./bin/
COMPARATOR_PRINT_DIR = ./comparatorPrints/
OUT_SORT_REVERT = $(OUTDIR)sortAndRevert

sortRevert: clean mkdir
	gcc sortAndRevert.c ../sort/sort.c ../utils/arrayUtils.c ../sort/comparator/compare.c ../utils/comparatorList.c ../sort/comparator/saveComparation.c ../utils/fileUtils.c -o $(OUT_SORT_REVERT)

mkdir:
	mkdir -p $(OUTDIR)
	mkdir -p $(COMPARATOR_PRINT_DIR)

clean:
	rm -f $(OUT_PRINT_NET)
	rm -fr $(COMPARATOR_PRINT_DIR)