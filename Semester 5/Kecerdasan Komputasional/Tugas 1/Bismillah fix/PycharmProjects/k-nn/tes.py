from sklearn.metrics.pairwise import cosine_similarity
import random
import math
import operator
import csv
import numpy as np
from scipy import spatial


def getdata(filename):
    with open(filename,'rb') as f:
        reader = csv.reader(f)
        return list(reader)

#len(i_data)

def shuffle(data): # Splitting and shuffling data
    random.shuffle(data)
    length = len(data)
    train_data = data[:int(0.67*length)]
    test_data = data[int(0.67*length):]
    return train_data, test_data


def cosine_similarity(v1,v2):
    "compute cosine similarity of v1 to v2: (v1 dot v2)/{||v1||*||v2||)"
    sumxx, sumxy, sumyy = 0, 0, 0
    for i in range(len(v1)):
        x = float(v1[i]); y = float(v2[i])
        sumxx += x*x
        sumyy += y*y
        sumxy += x*y
    return sumxy/math.sqrt(sumxx*sumyy)


def CosineSimilarity(xixi, xaxa):
    d = 0.0
    npx = np.array(xixi)
    npx = npx.reshape(-1, 1)
    npxa = np.array(xaxa)
    npxa = npxa.reshape(-1, 1)
    result = cosine_similarity(npx, npxa)
#    d = 1 - spatial.distance.cosine(npx, npxa)
    return result[0]


def euclideanDist(x, xi):
    d = 0.0
    for i in range(len(x)-1):
        d += pow((float(x[i])-float(xi[i])),2)
    d = math.sqrt(d)
    return d


def predict(test_data, train_data, k_value):
    for i in test_data:
        eu_Distance =[]
        dist = []
        knn = []
        spam = 0
        notspam = 0
        for j in train_data: # Comparing the test with the training-data
            #eu_dist = euclideanDist(i, j)
            cosim = cosine_similarity(i, j)
            dist.append((j[57], cosim))
            dist.sort(key = operator.itemgetter(1))
            knn = dist[:k_value]
            #eu_Distance.append((j[57], eu_dist))
            #eu_Distance.sort(key = operator.itemgetter(1))
            #knn = eu_Distance[:k_value]
            for k in knn:
                if k[0] =='1':
                    spam += 1
                else:
                    notspam +=1
        if spam > notspam:
            i.append('1')
        elif spam < notspam:
            i.append('0')
        else:
            i.append('NaN')


def accuracy(test_data):
    correct = 0
    for i in test_data:
        if i[57] == i[58]:
            correct += 1

    accuracy = float(correct)/len(test_data) *100
    return accuracy


dataset = getdata('spambase.data')  #getdata function call with csv file as parameter
train_dataset, test_dataset = shuffle(dataset) #train test data split
K = input("Masukkan nilai dari k: ") # Assumed K value
predict(test_dataset, train_dataset, K)
# print test_dataset
akurasi = accuracy(test_dataset)
print "Accuracy : ", akurasi