# TODO: readme.md
import csv
import random
import math
import operator
import numpy as np

def loadDataset(filename, split, trainingSet=[], testSet=[]):
    with open(filename, 'rb') as csvfile:
        lines = csv.reader(csvfile)
        dataset = list(lines)
        for x in range(len(dataset)-1):
            for y in range(57):
                dataset[x][y] = float(dataset[x][y])
            if random.random() < split:
                trainingSet.append(dataset[x])
            else:
                testSet.append(dataset[x])

#def square_rooted(x, length):
#    return round(sqrt(sum([a*a for a in x])),length)
#
#def cosine_similarity(v1,v2):
#    sumxx, sumxy, sumyy = 0, 0, 0
#    for j in range(len(v1)):
#            x = v1[j]; y = v2[j]
#            sumxx += x*x
#            sumyy += y*y
#            sumxy += x*y
#    return sumxy/math.sqrt(sumxx*sumyy)
#def cosine_similarity(x, y, length):
#    numerator = sum(a*b for a,b in zip(x,y))
#    denominator = square_rooted(x)*square_rooted(y)
#    return round(numerator/float(denominator),length)
    #dot_product - np.dot(a, b)
    #norm_a = np.linalg.norm(a)
    #norm_b = np.linalg.norm(b)
    #return dot_product / (norm_a * norm_b)

def euclideanDistance(instance1, instance2, length):
    distance = 0
    for x in range(length):
        distance += pow((instance1[x] - instance2[x]), 2)
    return math.sqrt(distance)

def getNeighbors(trainingSet, testInstance, k):
    distances = []
#    length = len(testInstance) - 1
    b = np.array(trainingSet)
    c = np.array(testInstance)
    for x in range(len(trainingSet)):
        dist = np.cosine(b[x], c)
        #dist = euclideanDistance(testInstance, trainingSet[x], length)
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

def main():
    # preparing
    trainingSet = []
    testSet = []
    split = 0.67
    loadDataset('spambase.data', split, trainingSet, testSet)
    print 'Train set: ' + repr(len(trainingSet))
    print 'Test set: ' + repr(len(testSet))
    # predictions
    predictions = []
    k = input("Masukkan nilai dari k: ")
    for x in range(len(testSet)):
        neighbors = getNeighbors(trainingSet, testSet[x], k)
        result = getResponse(neighbors)
        predictions.append(result)
        print('> predicted=' + repr(result) + ', actual=' + repr(testSet[x][-1]))
    accuracy = getAccuracy(testSet, predictions)
    print('Accuracy: ' + repr(accuracy) + '%' + '\n')

main()
