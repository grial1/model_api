"""

    file    core.py
    author  Gastón Rial Saibene
    date    2019-06-19

"""
from sklearn.neighbors import KNeighborsClassifier

class Model:

    def __init__(self):
        """ 
            Class constructor 
        """
        self.model = KNeighborsClassifier(n_neighbors=10,\
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
