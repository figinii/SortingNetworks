Il progetto è stato condotto da Matteo Figini con la supervisione del professore Barenghi Alessandro. 

L’inizio del progetto (con comunicazione alla referente Fugini Mariagrazia) è avvenuto in data 15 aprile 2024 e la consegna e conclusione è avvenuta in data 1 settembre 2024.

Il progetto è partito con un’introduzione teorica riguardante i side channels attacks, con particolare focus sui time attacks e ad un’introduzione all’approccio constant time alla programmazione.  
La gran parte del progetto si è poi concentrata su teoria e implementazione ottimizzata delle sorting network come possibile soluzione alle problematiche sollevate precedentemente.

# side channels attacks

I side channels attack sono una classe di cyber attacks che sfruttano tracce lasciate dall'esecuzione di un algoritmo per violare il sistema originale. Ad esempio si possono controllare i consumi energetici, le emissioni elettromagnetiche o i tempi di esecuzione per risalire ad informazioni che altrimenti resterebbero celate. 
In particolare questo tipo di attacchi non mira a testare la robustezza matematica dell'algoritmo originale, ma si concentrano sull'analizzarne l'implementazione fisica. 

Un esempio concreto può essere il risalire alle informazioni contenute all'interno di una smartCard tramite il monitoraggio del consumo energetico del relativo lettore.

![[smartCardReader.png]](https://github.com/figinii/SortingNetworks/blob/main/report/reportAssets/smartCardReader.png)

Osservando che la lettura di un 1 consuma il doppio dell'energia rispetto alla lettura di uno 0 diventa quindi immediato risalire all'informazione originale contenuta nella smart card; questo a prescindere dall'algoritmo utilizzato per la trasmissione dei dati durante la lettura ed indipendentemente dalla sua robustezza.

# time channel

Una particolare sottocategoria dei side channels attacks sono i time channel attacks. 
Come intuibile dal nome, questi attacchi vanno ad analizzare il tempo d'esecuzione di un algoritmo, o più in particolare si concentrano sulla differenza nei tempi di esecuzione in funzione dell'input.

Un esempio molto semplice di codice che scopre il fianco ad un time attack può essere il seguente:

```
bool verifica_password(password_inserita) {  
	if (password_inserita == password_corretta) {  
	        return true;
	}  
	 return false;
}
```

che può essere tradotto nel seguente diagramma:
![[flowChartPassCheck.png]](https://github.com/figinii/SortingNetworks/blob/main/report/reportAssets/flowChartPassCheck.png)

il confronto effettuato tramite l'operatore <code>==</code> infatti è valutato carattere per carattere e appena trovato un carattere differente viene interrotto. Complementarmente se i due caratteri coincidono il confronto prosegue. 
Questa differenze nel comportamento dell'algoritmo è facilmente osservabile tenendo traccia dei tempi d'esecuzione dell'algoritmo. 
È facile quindi capire come, grazie a questa informazione aggiuntiva, sia semplice risalire alla password corretta, teoricamente segreta, usando un banale attacco bruteforce in tempi ragionevoli.

## Constant Time Discipline

Una soluzione possibile per proteggersi da time attacks è la constant time discipline, ovvero un approccio alla programmazione che mira a garantire che i tempi di esecuzione delle operazioni sia indipendente dall'input inserito.

Riprendendo l'esempio a inizio paragrafo

```
bool verifica_password(password_inserita) {  
	if (password_inserita == password_corretta) {  
	        return true;
	}  
	 return false;
}
```

la constant time discipline porterebbe portare a modificare la metodologia di confronto delle due password in modo tale che prosegua per tutta la lunghezza della parola in input e la differenza valutata solo alla fine della comparazione.

# sorting networks

un'operazione molto comune a diversi cifrari è il sorting. Le sorting network sono astrazioni di algoritmi di sorting in cui le comparazioni effettuate non dipendono dai valori da ordinare, ma unicamente dalla dimensione del vettore in ingresso. 

## sort

Un problema di ordinamento può essere definito come segue:
Prendiamo J  = {0, ..., n-1} un insieme di indici; B un insieme di elementi e una relazione di ordinamento ≤ definita su B. 
Una sequenza di elementi è definibile come una funzione f: J → A. 

Un problema di ordinamento può essere definito quindi come il processo di riordinare una qualunque sequenza di elementi ai ∈ A in una sequenza aφ(0), ..., aφ(n-1) tale che aφ(i) ≤ aφ(j)  con  i < j

## interconnection networks

Un interconnection network è una rete che ha come obiettivo quello di consentire la comunicazione tra nodi diversi; ciascun network differisce dall'altro a seconda della topologia dello stesso, ovvero dal pattern usato per collegare tra loro i nodi della rete.
Le topologie si dividono in statiche e dinamiche, differenziate dalla possibilità di modificare le interconnesioni tra i nodi una volta fissate.

Una topologia statica è la batterfly mostrata di seguito.

![[butterflyNetwork.png]](https://github.com/figinii/SortingNetworks/blob/main/report/reportAssets/butterflyNetwork.png)

Gli elementi quadrati rappresentano i nodi della rete, che possono essere ad esempio telefoni o computer. Quelli circolari sono invece switch:

![[switch example.png]](https://github.com/figinii/SortingNetworks/blob/main/report/reportAssets/switch%20example.png)

Uno switch elementare come quello mostrato in figura ha due input (in0, in1) e due output(out0, out1). Quando attivato quello che fa è direzionare i due canali in modo da portare il contenuto di in0 su out1 e in1 su out0. Se invece disattivo lascia i dati passano così come sono disposti senza effettuare alcun cambio di direzione.

Tornando alla batterfly network diventa quindi evidente come sia possibile direzionare ciascun input all'output desiderato andando ad accendere gli switch corrispondenti.

![[batterflyRoutingEx.png]](https://github.com/figinii/SortingNetworks/blob/main/report/reportAssets/batterflyRoutingEx.png)

## sorting network
Le idee originate nel campo delle interconnection networks possono essere traslate all'operazione di sorting.
L'ordinamento infatti non è altro che un routing in cui ciascun elemento è direzionato in una determinata posizione all'interno della lista a seconda della sua relazione (maggiore/minore) con gli altri elementi.

Una sorting network è dunque composta da due elementi familiari:
- i canali (nodi) che rappresentano una posizione all'interno delle lista
- i comparatori (gli switch), elementi che vanno a scambiare la posizione di due valori della lista quando una certa condizione è verificata (es. aφ(i) ≤ aφ(j))

Il funzionamento è quindi intuitivo:

![[sortingNetworkRoutingEx.png]](https://github.com/figinii/SortingNetworks/blob/main/report/reportAssets/sortingNetworkRoutingEx.png)

Partendo da sinistra i valori si muovono attraverso la sorting network; ogni volta che incontrano un comparatore, viene effettuato un confronto e in caso vengono scambiati.
Così i valori più "pesanti" vengono routati verso il basso, mentre quelli più "leggeri" salgono verso l'alto.

Più semplicemente le sorting network non sono altro che topologie statiche di reti usate per riordinare elementi all'interno di una lista; mentre i più comuni algoritmi di riordinamento sono topologie dinamiche, che quindi cambiano le comparazioni che effettuano a run time a seconda della lista in input.

### reverse sorting e scrambler

Con questa nuova prospettiva in mente è facile vedere come le comparator networks possano essere usate per diverse applicazioni.

Per esempio si può invertire l'operazione di ordinamento effettuata salvandosi il risultato delle comparazioni. 
Facendo semplicemente passare la lista ordinata attraverso la sorting network in senso inverso, e abilitando gli switch che erano stati attivati all'andata, è possibile riottenere la lista di partenza.

Un'altra applicazione interessante sta nel modificare la funzione implementata dai comparatori. Invece di scambiare i due valori quando aφ(i) ≤ aφ(j), lo scrambler scambia i due valori casualmente. Ciò che si ottiene è dunque una rete di scrabling che dato un vettore in ingresso produce in uscita un vettore disordinato.

### 0-1 principle

Lo 01 principle è uno strumento estremamente utile per dimostrare la correttezza di una sorting network. 
Questo afferma:

*Se una sorting network ordina ogni sequenza di 0 e 1 allora ordina ogni altra sequenza di valori qualsiasi.*

La dimostrazione è piuttosto semplice:

Data una sequenza di elementi A non ordinata, si definisce una funzione f: A → {0, 1} tale che
per ogni c ∈ A vale
![[01mapping.png]](https://github.com/figinii/SortingNetworks/blob/main/report/reportAssets/01mapping.png)

dove bk indica l'elemento in posizione k di A

Di conseguenza se tutte le sequenza di 0 e 1 sono sortate correttamente allora qualunque sequenza numerica sarà sortata correttamente. 

Riuslta essere uno strumento formidabile in quanto riduce di molto la complessità di verifica della correttezza di qualsiasi sorting network.

### Efficienza

Per misurare l'efficienza di una sorting network se ne considera la dimensione, ovvero il numero di comparatori presenti all'interno della rete stessa. Si va dunque a misurare il numero di comparazioni totali che vengono effettuate sul vettore in ingresso attraverso la rete.

#### parallelismo

Un grosso vantaggio delle sorting networks sta nel parallelismo intrinseco alla loro struttura. Le comparazioni che avvengono tra dati diversi possono essere infatti portate avanti in parallelo, ottimizzando quindi la velocità d'esecuzione.

Per questo motivo un'alternativa metrica temporale definita per le sorting network è la profondità, ovvero il massimo numero di comparatori che un singolo canale può potenzialmente attraversare lungo un intero percorso.

#### generatori di sorting networks

Per reti con un piccolo numero di input sono state trovate topologie che presentano una dimensione ottima; una lista di queste la lascio al seguente [link](https://bertdobbelaere.github.io/sorting_networks.html)

Per quanto riguarda input di dimensione maggiore, o non prefissata ciò che serve è un algoritmo che generi una sorting network.
Per questo obiettivo ne esistono diversi con efficienza variabile.

Uno dei più semplici è sicuramente l'insertion sort che mantiene un'efficienza di O(n^2).

![[insertionSortingNet.png]](https://github.com/figinii/SortingNetworks/blob/main/report/reportAssets/insertionSortingNet.png)

Affascinante è notare come la stessa rete viene generata anche dal bubble sort; mostrando quindi come di fatto implementano la stessa logica di base, vista però da due prospettive diverse.

Per quanto riguarda generatori con complessità minore ce ne sono diversi:

#### Bitonic Sort

Una equenza è detta bitonica (bitonic) se è separabile in due sottosequenze la prima crescente e la seconda decrescente.

![[bitonicSeq.png]](https://github.com/figinii/SortingNetworks/blob/main/report/reportAssets/bitonicSeq.png)

si tratta di una sorting network estremamente regolare composta da due elementi:

![[bitonicSorting.png]](https://github.com/figinii/SortingNetworks/blob/main/report/reportAssets/bitonicSorting.png)

- il sorter (in rosa): data una sequenza bitonica in ingresso produce una sequenza ordinata di valori in uscita
- il merger date due sequenze ordinate produce una sequenza bitonica 

Applicando questi due elementi ripetuti si ottiene una stringa ordinata dato un qualsiasi ingresso.

Il bitonic sort ha una dimensione di O(n log^2(n)) e una profondità di O(log^2(n)), ma presenta lo svantaggio di lavorare su input di dimensione 2^n.

#### Batcher's merge exchange
![[BatcherMergeExchange.png]](https://github.com/figinii/SortingNetworks/blob/main/report/reportAssets/BatcherMergeExchange.png)

l'algoritmo di Batcher preserva la stessa dimensione e profondità del bitonic sort, può però lavorare su input di dimensione qualsiasi.

#### O (n log(n))
Un modo per costruire sorting network di dimensione O(n log(n)) è l'algoritmo AKS (Agrawal-Kayal-Saxena). Questo però ha delle forte limitazioni a livello pratico in quanto possiede una costante lineare molto grande. 

# bibliography - and additional links
- The Art of Computer Programming, Vol. 1 Fundamental Algorithms, 3rd Edition (Donald E. Knuth) 
- Timing Channels in Cryptography A Micro-Architectural Perspective (Chester Rebeiro, Debdeep Mukhopadhyay etc.)
- https://hwlang.de/algorithmen/sortieren/networks/indexen.htm
- https://www.cs.kent.edu/~batcher/sort.pdf
- https://www.drdobbs.com/sorting-networks/184402663?pgno=1
- https://www.cl.cam.ac.uk/teaching/1415/AdvAlgo/lec2_ann.pdf
- https://en.wikipedia.org/wiki/Sorting_network
