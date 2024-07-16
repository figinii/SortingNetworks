OUTDIR = ./bin/
OUT = $(OUTDIR)sort

sort: mkdir clean
	gcc testSort.c sort.c ../utils/arrayUtils.c ./comparator/compare.c -o $(OUT)

mkdir:
	mkdir -p $(OUTDIR)

clean:
	rm -f $(OUT)