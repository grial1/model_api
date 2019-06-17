///  author  Gastón Rial
///  date    2019-06-16

#ifndef MODEL_API_INCLUDE_TESTING_DATASET_H_
#define MODEL_API_INCLUDE_TESTING_DATASET_H_

#pragma once

#include "Dataset.h"

namespace model_api
{

    /// class TestingDataSet
    /// brief Abstract class that represents a data set used to be predicted
    class TestingDataSet:public Dataset
    {

        public:
            TestingDataSet()=delete;                ///< Delete default construtor
            ~TestingDataSet();                      ///< Destructor
            TestingDataSet(const nda& oFM);         ///< Copy constructor
            TestingDataSet(const nda&& oFM);        ///< Move constructor
            void operator=(const nda& oFM);         ///< Copy assigment operator
            void operator=(const nda&& oFM);        ///< Move assigment operator
            nda& getFileMatrix() const;             ///< Accessor method
            nda& getPredictions() const;            ///< Accessor method
            void setFileMatrix(const nda& oFM);     ///< Mutator method
            void setPredictions(const nda& oP);     ///< Mutator method
            void test();                            ///< Test model
            std::string& string() const;                 ///< Convert to string

    };

};
#endif ///< MODEL_API_INCLUDE_TESTING_DATASET_H_