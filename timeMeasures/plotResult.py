import pandas as pd
import matplotlib.pyplot as plt

sampleSizeLabel = "sampleLen"
timeLabel = "time"
cycleLabel = "cycles"

file_path = ['./outFile/test1.csv', './outFile/test2.csv', './outFile/test3.csv']  

mean = []
variance = []

for index in range(0, len(file_path)):
    data = pd.read_csv(file_path[index], header=0)
    sampleSizes = sorted(set(data[sampleSizeLabel]))

    mean.append({timeLabel : [], cycleLabel : []})
    variance.append({timeLabel : [], cycleLabel : []})

    for field in {timeLabel, cycleLabel}:
        for i in sampleSizes:
            fieldValue = data[data[sampleSizeLabel] == i][field]
            mean[index][field].append(fieldValue.mean())
            variance[index][field].append(fieldValue.var())


print(mean)

#plt.scatter(data1[sampleSizeLabel], data1[cycleLabel], edgecolor='black', label='CPUcycles')
#plt.scatter(data2[sampleSizeLabel], data2[cycleLabel], edgecolor='black', label='CPUcycles')

plt.plot(sampleSizes, mean[0][cycleLabel], marker='o')
plt.plot(sampleSizes, mean[1][cycleLabel], marker='v')
plt.plot(sampleSizes, mean[2][cycleLabel], marker='p')

plt.xlim(min(sampleSizes)-100, max(sampleSizes)+100)
plt.xticks([512, 1024, 2048])
plt.show()


