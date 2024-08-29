import pandas as pd
import matplotlib.pyplot as plt

sampleSizeLabel = "sampleLen"
timeLabel = "time"
cycleLabel = "cycles"

file_path = './outFile/test1.csv'  
data = pd.read_csv(file_path, header=0)

sampleSizes = sorted(set(data[sampleSizeLabel]))
mean = {timeLabel : [], cycleLabel : []}
variance = {timeLabel : [], cycleLabel : []}

for field in {timeLabel, cycleLabel}:
    for i in sampleSizes:
        fieldValue = data[data[sampleSizeLabel] == i][field]
        mean[field].append(fieldValue.mean())
        variance[field].append(fieldValue.var())

print(mean)

plt.plot(sampleSizes, mean[timeLabel], marker='o')
plt.xlim(min(sampleSizes), max(sampleSizes))
plt.show()
    

