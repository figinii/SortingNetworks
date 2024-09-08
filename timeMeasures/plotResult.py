import pandas as pd
import matplotlib.pyplot as plt

sampleSizeLabel = "sampleLen"
timeLabel = "time"
cycleLabel = "cycles"

file_path = ['./outFile/test1.csv', './outFile/test2.csv']  

data1 = pd.read_csv(file_path[0], header=0)
data2 = pd.read_csv(file_path[1], header=0)

sampleSizes1 = sorted(set(data1[sampleSizeLabel]))
mean1 = {timeLabel : [], cycleLabel : []}
variance1 = {timeLabel : [], cycleLabel : []}

for field in {timeLabel, cycleLabel}:
    for i in sampleSizes1:
        fieldValue = data1[data1[sampleSizeLabel] == i][field]
        mean1[field].append(fieldValue.mean())
        variance1[field].append(fieldValue.var())

sampleSizes2 = sorted(set(data1[sampleSizeLabel]))
mean2 = {timeLabel : [], cycleLabel : []}
variance2 = {timeLabel : [], cycleLabel : []}

for field in {timeLabel, cycleLabel}:
    for i in sampleSizes2:
        fieldValue = data2[data2[sampleSizeLabel] == i][field]
        mean2[field].append(fieldValue.mean())
        variance2[field].append(fieldValue.var())

print(mean1, mean2)

#plt.scatter(data1[sampleSizeLabel], data1[cycleLabel], edgecolor='black', label='CPUcycles')
#plt.scatter(data2[sampleSizeLabel], data2[cycleLabel], edgecolor='black', label='CPUcycles')

plt.plot(sampleSizes1, mean1[timeLabel], marker='o')
plt.plot(sampleSizes2, mean2[timeLabel], marker='v')

plt.xlim(min(sampleSizes1)-100, max(sampleSizes1)+100)
plt.xticks([512, 1024, 2048])
plt.show()


