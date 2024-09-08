TARGETS = timedSort timedSortIntrinsic

OUTDIR = ./bin
OUT_TIMED_SORT = $(OUTDIR)/timedSort
OUT_TIMED_SORT_INT = $(OUTDIR)/timedSortIntrinsic

all: $(TARGETS)

timedSort: mkdir cleanBin
	gcc timingSort.c -o $(OUTDIR)/timedSort

timedSortIntrinsic: mkdir cleanBin
	gcc -g -mavx -mavx512f timingIntrinsic.c -o $(OUTDIR)/timedIntr

mkdir:
	mkdir -p $(OUTDIR)/

cleanBin:
	rm -rf $(OUTDIR)/*