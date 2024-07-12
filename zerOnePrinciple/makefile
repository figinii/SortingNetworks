TARGETS = zerOnePrincipleFromDiagram zerOnePrincipleCheckSort
all: $(TARGETS)

OUTDIR = ./bin/
OUT_DIAGRAM = $(OUTDIR)zerOnePrincipleDiagram
OUT_CHECK_SORT = $(OUTDIR)zerOnePrincipleCheckSort

zerOnePrincipleFromDiagram: mkdir cleanFromDiagram
	gcc zerOnePrincipleFromDiagram.c ../utils/comparatorList.c ../utils/arrayUtils.c -lm -o $(OUT_DIAGRAM)

zerOnePrincipleCheckSort: mkdir cleanCheckSort 
	gcc zerOnePrincipleCheckSort.c ../sort/sort.c ../sort/compare.c ../utils/arrayUtils.c -lm -o $(OUT_CHECK_SORT)

mkdir:
	mkdir -p $(OUTDIR)

cleanFromDiagram:
	rm -f $(OUT_DIAGRAM)

cleanCheckSort:
	rm -f $(OUT_CHECK_SORT)