///  author  Gastón Rial
///  date    2019-06-16

#ifndef MODEL_API_INCLUDE_INPUT_DATASET_H_
#define MODEL_API_INCLUDE_INPUT_DATASET_H_

#pragma once

#include "Dataset.h"

namespace model_api
{
  
    /// class InputDataset
    /// brief Abstract class that represents a data set used to be predicted
    class InputDataset:public Dataset
    {

        public:
            InputDataset()=delete;                  ///< Delete default construtor
            ~InputDataset();                        ///< Destructor
            InputDataset(const nda& oFM);           ///< Copy constructor
            InputDataset(const nda&& oFM);          ///< Move constructor
            void operator=(const nda& oFM);         ///< Copy assigment operator
            void operator=(const nda&& oFM);        ///< Move assigment operator
            nda& getFileMatrix() const;             ///< Accessor method
            nda& getPredictions() const;            ///< Accessor method
            void setFileMatrix(const nda& oFM);     ///< Mutator method
            void setPredictions(const nda& oP);     ///< Mutator method
            void predict();                         ///< Make prediction from filesmatrix
            std::string& string() const;            ///< Convert to string

    };

};

#endif ///< MODEL_API_INCLUDE_INPUT_DATASET_H_