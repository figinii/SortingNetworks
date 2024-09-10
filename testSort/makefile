TARGETS = sort mergeEx bitonic intrinsicBitonic intrinsicScrambler avx

OUTDIR = ./bin/
OUT_SORT_TEST = $(OUTDIR)sort
OUT_MERGEX_TEST = $(OUTDIR)mergeEx
OUT_BITONIC = $(OUTDIR)bitonic
OUT_BITONIC_INTR = $(OUTDIR)intrinsicBitonic
OUT_SCRAMBLE = $(OUTDIR)unsort
OUT_AVX = $(OUTDIR)avx

all: $(TARGETS)

sort: mkdir clean
	gcc testSort.c ../sort/sort.c ../utils/arrayUtils.c ../sort/comparator/compare.c ../sort/comparator/saveComparation.c -o $(OUT_SORT_TEST)

mergeEx: mkdir clean
	gcc testLibMergeExchange.c ../lib/mergeExchange/mergExchange.c ../utils/arrayUtils.c -o $(OUT_MERGEX_TEST)

bitonic: mkdir clean
	gcc testLibBitonic.c -o $(OUT_BITONIC)

intrinsicBitonic: mkdir clean
	gcc -g -mavx -mavx512f teslLibBitonicIntrinsic.c -o $(OUT_BITONIC_INTR)

intrinsicScrambler: mkdir clean
	gcc -g -mavx -mavx512f testScramble.c -o $(OUT_SCRAMBLE)

avx: mkdir clean
	gcc -g -mavx -mavx512bw -mavx512f testLibAVX.c -o $(OUT_AVX)

mkdir:
	mkdir -p $(OUTDIR)

clean:
	rm -f $(OUTDIR)*