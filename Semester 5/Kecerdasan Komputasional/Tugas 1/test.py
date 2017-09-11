import numpy as np
import sklearn
from sklearn.preprocessing import Imputer
from sklearn.cross_validation import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score

spambase_data = np.genfromtxt(fname ='spambase.data', delimiter= ',', dtype= float)

print "Dataset Length:: ", len(spambase_data)
print "Dataset:: ", str(spambase_data)
print "Dataset Shape:: ", spambase_data.shape
#removing type, as it is biased to spam
spambase_data = np.delete(arr = spambase_data, obj= 57, axis = 1)
X = spambase_data[:,range(0,56)]
Y = spambase_data[:,56]

X_train, X_test, y_train, y_test = train_test_split(X, Y, test_size = 0.67, random_state = 100)
y_train = y_train.ravel()
y_test = y_test.ravel()
