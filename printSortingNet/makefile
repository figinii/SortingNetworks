OUTDIR = ./bin/
COMPARATOR_PRINT_DIR = ./comparatorPrints/
OUT_PRINT_NET = $(OUTDIR)printNet

sort: clean mkdir
	gcc saveComparatorNet.c ../sort/sort.c ../utils/arrayUtils.c ../sort/comparator/compare.c ../sort/comparator/saveComparation.c -o $(OUT_PRINT_NET)

mkdir:
	mkdir -p $(OUTDIR)
	mkdir -p $(COMPARATOR_PRINT_DIR)

clean:
	rm -f $(OUT_PRINT_NET)
	rm -fr $(COMPARATOR_PRINT_DIR)
