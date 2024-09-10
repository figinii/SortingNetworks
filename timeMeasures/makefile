TARGETS = timedSort timedSortIntrinsic timedBatcher

OUTDIR = ./bin
OUT_TIMED_SORT = $(OUTDIR)/timedSort
OUT_TIMED_SORT_INT = $(OUTDIR)/timedIntr
OUT_TIMED_BATCHER = $(OUTDIR)/timedBatcher

all: $(TARGETS)

timedSort: mkdir cleanBin
	gcc timingSort.c -o $(OUT_TIMED_SORT)

timedSortIntrinsic: mkdir cleanBin
	gcc -g -mavx -mavx512f timingIntrinsic.c -o $(OUT_TIMED_SORT_INT)

timedBatcher: mkdir cleanBin
	gcc -g timingBatcher.c ../lib/mergeExchange/mergExchange.c -o $(OUT_TIMED_BATCHER)

mkdir:
	mkdir -p $(OUTDIR)/

cleanBin:
	rm -rf $(OUTDIR)/*