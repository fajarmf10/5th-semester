import csv
import random
import pandas as pd
from sklearn.preprocessing import Imputer
import numpy
import operator
import math

#dataset = pd.read_csv('pima-indians-diabetes.csv', header=None)
# mark zero values as missing or NaN
#dataset[[1,2,3,4,5]] = dataset[[1,2,3,4,5]].replace(0, numpy.NaN)
# fill missing values with mean column values
#values = dataset.values
#print list(dataset.values.flatten())
#lala = dataset.values.tolist()
#lala = list(dataset.values.flatten())
#imputer = Imputer()
#transformed_values = imputer.fit_transform(values)
# count the number of NaN values in each column
# print(numpy.isnan(transformed_values).sum())
#print transformed_values[:]


def loadDataset(filename, split=0.67, trainingSet=[], testSet=[]):
    dataset = pd.read_csv(filename, header=None)
    dataset[[1,2,3,4,5]] = dataset[[1,2,3,4,5]].replace(0, numpy.NaN)
    values = dataset.values
    imputer = Imputer()
    final_value = imputer.fit_transform(values)
    final = str(final_value.tolist())
    for x in range(len(final)):
        for y in range(8):
            final[x][y] = float(final[x][y])
        if random.random() < split:
            trainingSet.append(final[x])
        else:
            testSet.append(final[x])


def cosine_similarity(instance1,instance2, length):
    "compute cosine similarity of v1 to v2: (v1 dot v2)/{||v1||*||v2||)"
    sumxx, sumxy, sumyy = 0, 0, 0
    for i in range(length):
        x = instance1[i]; y = instance2[i]
        sumxx += x*x
        sumyy += y*y
        sumxy += x*y
    sumxx = math.sqrt(sumxx)
    sumyy = math.sqrt(sumyy)
    distance = float(sumxy) / float(sumxx * sumyy)
    return (1 - distance)


def euclideanDistance(instance1, instance2, length):
    distance = 0
    for x in range(length):
        distance += pow((instance1[x] - instance2[x]), 2)
    return math.sqrt(distance)


def getNeighbors(trainingSet, testInstance, k):
    distances = []
    length = len(testInstance) - 1
    for x in range(len(trainingSet)):
        dist = cosine_similarity(testInstance, trainingSet[x], length)
        distances.append((trainingSet[x], dist))
        distances.sort(key=operator.itemgetter(1))
        neighbors = []
    for x in range(k):
        neighbors.append(distances[x][0])
    return neighbors

def getResponse(neighbors):
    classVotes = {}
    for x in range(len(neighbors)):
        response = neighbors[x][-1]
        if response in classVotes:
            classVotes[response] += 1
        else:
            classVotes[response] = 1
    sortedVotes = sorted(classVotes.iteritems(), key=operator.itemgetter(1), reverse=True)
    return sortedVotes[0][0]

def getAccuracy(testSet, predictions):
    correct = 0
    for x in range(len(testSet)):
        if testSet[x][-1] == predictions[x]:
            correct += 1
    return (correct / float(len(testSet))) * 100.0


#    with open(filename, 'rb') as csvfile:
#        lines = csv.reader(csvfile)
#        dataset = list(lines)
#        for x in range(len(dataset) - 1):
#            for y in range(57):
#                dataset[x][y] = float(dataset[x][y])
#            if random.random() < split:
#                trainingSet.append(dataset[x])
#            else:
#                testSet.append(dataset[x])


def main():
    # prepare data
    trainingSet = []
    testSet = []
    split = 0.67
#    filename = raw_input("Masukkan nama dataset >")
    loadDataset('pima-indians-diabetes.csv', split, trainingSet, testSet)
    print 'Train set: ' + repr(len(trainingSet))
    print 'Test set: ' + repr(len(testSet))
    # generate predictions
    predictions = []
    k = input("Masukkan nilai dari k: ")  # Assumed K value
    for x in range(len(testSet)):
        neighbors = getNeighbors(trainingSet, testSet[x], k)
        result = getResponse(neighbors)
        predictions.append(result)
        print('> predicted=' + repr(result) + ', actual=' + repr(testSet[x][-1]))
    accuracy = getAccuracy(testSet, predictions)
    print('Accuracy: ' + repr(accuracy) + '%')


if __name__ == '__main__':
    main()
