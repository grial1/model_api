/// @file InputDataset.h  
/// @author Gastón Rial
/// @date 2019-06-16
/// @brief API to communicate with predictive model implemented in Python

#ifndef MODEL_API_INCLUDE_INPUT_DATASET_H_
#define MODEL_API_INCLUDE_INPUT_DATASET_H_

#pragma once

#include <exception>
#include <boost/python/object.hpp>
#include <boost/python/import.hpp>
#include "Dataset.h"

namespace py = boost::python;
using pyObject = py::object;
using pyTuple = py::tuple;

/// @namespace model_api
/// @brief Namespace that gathers all the API classes
namespace model_api
{
  
    /// @class InputDataset
    /// @brief API class that represents an input data set of unknows to be predicted
    class InputDataset:public Dataset
    {

        public:
            InputDataset()=delete;                                      ///< Delete default construtor
            ~InputDataset();                                            ///< Destructor
            /// @param oFM ndarray with data instances
            InputDataset(nda& oFM);                                     ///< Copy constructor
            /// @param oFM ndarray with data instances
            InputDataset(nda&& oFM);                                    ///< Move constructor
            /// @param oFM ndarray with data instances
            void operator=(nda& oFM);                                   ///< Copy assigment operator
            /// @param oFM ndarray with data instances
            void operator=(nda&& oFM);                                  ///< Move assigment operator
            /// @return ndarray with data instances
            nda& getFileMatrix() const;                                 ///< Accessor method
            /// @param oFM ndarray with data instances
            void setFileMatrix(nda& oFM);                               ///< Mutator method
            /// @param out ndarray with predictions (one entry for each row in oFM)
            void predict(nda& out);                                     ///< Make prediction from filesmatrix
            /// @param oFMTrain ndarray with train data instances
            /// @param oPTrain ndarray with train predictions (used for supervised learning)
            void initModel(const nda& oFMTrain,const nda& oPTrain);     ///< Initilize model and train, in case is neccessary
            /// @param oFMTest input data instances for testing the model
            /// @param oPTest Predictions of the tests dataset
            /// @param oPMList list of metrics to be returned
            void testModel(const nda& oFMTest,const nda& oPTest, std::vector<PerformaceMetric>& oPMList);  ///< Method that returns a list of evaluation metrics from a tested model
    
        private:
            pyObject oModel; ///< Instance of model.Model class

    };

};

#endif ///< MODEL_API_INCLUDE_INPUT_DATASET_H_