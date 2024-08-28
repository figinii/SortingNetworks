TARGETS = timedSort

OUTDIR = ./bin
OUT_TIMED_SORT = $(OUTDIR)/timedSort

all: $(TARGETS)

timedSort: mkdir cleanBin
	gcc timingSort.c -o $(OUTDIR)/timedSort

mkdir:
	mkdir -p $(OUTDIR)/

cleanBin:
	rm -rf $(OUTDIR)/*