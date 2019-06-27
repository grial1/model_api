"""

    file    core.py
    author  Gastón Rial Saibene
    date    2019-06-19

"""
from sklearn.neighbors import KNeighborsClassifier
import numpy as np

class Model:

    def __init__(self):
        """ 
            Class constructor 
        """
        self.model = KNeighborsClassifier(n_neighbors=1,\
                                                weights="distance",\
                                                algorithm="kd_tree",\
                                                leaf_size=30,\
                                                p=2,\
                                                metric="minkowski")
        self.matrix = None
        self.prediction = None
    
    def setDataset(self, matrix):
        if matrix is not None:
            self.matrix = matrix

    def setPrediction(self, prediction):
        if prediction is not None:
            self.prediction = prediction
    
    def getPrediction(self):
        return self.prediction

    def predict(self):
        if self.matrix is not None:
            self.prediction = self.model.predict(self.matrix)

    def train(self):
        if self.matrix is not None and self.prediction is not None:
            self.model.fit(self.matrix, self.prediction)

    def test(self):
        if self.matrix is not None and self.prediction is not None:
            testPrediction = self.model.predict(self.matrix)
            real = self.getPrediction()     # Real values
            diff=testPrediction-((real+1)*real)
            unique, counts = np.unique(diff, return_counts=True)
            # Concepts in the totals dictionary
            # -2 => False negative
            #  0 => True negative
            # -1 => True positive
            #  1 => False positive
            totals = dict(zip(unique, counts))
            if ( not -1 in totals ) and ( not -2 in totals ):
                return (4, totals.get(-1,0),totals.get(0,0),totals.get(1,0),totals.get(-2,0))
            recall = float(totals.get(-1,0)/(totals.get(-1,0)+totals.get(-2,0)))
            if ( not -1 in totals ) and ( not 1 in totals ):
                return (5, totals.get(-1,0),totals.get(0,0),totals.get(1,0),totals.get(-2,0),recall)
            precision = float(totals.get(-1,0)/(totals.get(-1,0)+totals.get(1,0)))
            f1 = (2*precision*recall)/(precision+recall)
            # Returns TP, TN, FP and FN
            return (7, totals.get(-1,0),totals.get(0,0),totals.get(1,0),totals.get(-2,0), recall, precision, f1)
        else:
            raise Exception("ERROR: No test dataset defined")      
