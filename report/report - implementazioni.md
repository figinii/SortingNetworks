- [Batcher Merge Exchange](https://github.com/figinii/SortingNetworks/tree/main/lib/mergeExchange)
- [Bitonic Sort](https://github.com/figinii/SortingNetworks/blob/main/lib/bitonic/bitonicSort.h)
- [Bitonic Sort AVX2](https://github.com/figinii/SortingNetworks/blob/main/lib/bitonic/bitonicAVX2.h)
- [Bitonic Sort AVX-512](https://github.com/figinii/SortingNetworks/blob/main/lib/bitonic/bitonicAVX-512.h)
- [Bitonic Scrambler](https://github.com/figinii/SortingNetworks/blob/main/lib/bitonic/bitonicCmpParam.h)
- [Reverse Sorting](https://github.com/figinii/SortingNetworks/tree/main/reverseSorting)
- [01 Principle](https://github.com/figinii/SortingNetworks/tree/main/zerOnePrinciple)

## tempi

le misurazioni sono state effettuate usando il TSC, con una sample size di 1000 per ogni dimensione. Di seguito riportati i grafici delle medie a confronto.

In verde il Batcher Merge Exchange senza parallelismo, in blu il bitonic sort che sfrutta parallelismo e in arancione il bitonic sort ottimizzato usando intrinsic.

![../reportAssets/intrinsicVsNoVsMerge.png](https://github.com/figinii/SortingNetworks/blob/main/report/reportAssets/intrinsicVsNoVsMerge.png)

Come ci si poteva aspettare la l'uso del parallelismo ha un impatto notevole sulla velocità d'esecuzione. Divario che aumenta notevolmente al crescere della dimensione dell'input.

![intrinsicVsNo.png](https://github.com/figinii/SortingNetworks/blob/main/report/reportAssets/intrinsicVsNo.png)

Da questo secondo tracciato invece si può notare la differenza nei tempi d'esecuzione data dall'implementazione usando intrinsic. Anche in questo caso il divario tende a crescere all'aumentare del numero di elementi.
