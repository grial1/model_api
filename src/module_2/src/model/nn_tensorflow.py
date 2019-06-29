"""

    file    nn_tensorflow.py
    author  Gastón Rial Saibene
    date    2019-06-29

"""
import numpy as np
import tensorflow as tf




class Model:

    def __init__(self):
        """ 
            Class constructor 
        """
        self.matrix = None
        self.prediction = None
        self.matTrain = None
        self.pTrain = None
        self.model = None
    
    def setDataset(self, matrix):
        if matrix is not None:
            # First time that is called, training dataset is stored
            if self.matTrain is None:
                self.matTrain = matrix
            else:
                self.matrix = matrix

    def setPrediction(self, prediction):
        if prediction is not None:
            # First time that is called, training labels is stored
            if self.pTrain is None:
                self.pTrain = prediction
            else:
                self.prediction = prediction
    
    def getPrediction(self):
        return self.prediction

    def predict(self):
        # Nearest Neighbor calculation using manhatan distance
        # Calculate manhatan distance
        matTrain = tf.placeholder(tf.float32,self.matTrain.shape)
        matrix = tf.placeholder(tf.float32,self.matrix[0].shape)
        distance = tf.reduce_sum(tf.abs(tf.add(matTrain, tf.negative(matrix))), reduction_indices=1)
        # Prediction: Get min distance index (Nearest neighbor)
        pred = tf.math.argmin(distance, 0)
        result = []
        # Initialize the variables (i.e. assign their default value)
        init = tf.global_variables_initializer()

        # Start training
        with tf.Session() as sess:
        
            # Run the initializer
            sess.run(init)

            # loop over test data
            for i in range(len(self.matrix)):
                # Get nearest neighbor
                nn_index = sess.run(pred, feed_dict={matTrain: self.matTrain, matrix: self.matrix[i]})
                result.append(self.pTrain[nn_index]) # Add label to result
                # Get nearest neighbor class label and compare it to its true label
        self.prediction = np.array(result)

    def train(self):
        """
            Not implemented because it is not necessary
        """
        pass