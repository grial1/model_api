///  author  Gastón Rial
///  date    2019-06-16

#ifndef MODEL_API_INCLUDE_DATASET_H_
#define MODEL_API_INCLUDE_DATASET_H_

#pragma once

#include <string>
#include <boost/python/numpy.hpp>

namespace np = boost::python::numpy;
using nda = np::ndarray;

namespace model_api
{
    
    /// class Dataset
    /// brief Abstract class that represents a data set
    class Dataset
    {

        public:
            Dataset()=delete;                       ///< Delete default construtor
            virtual ~Dataset()=0;                   ///< Destructor

        protected:
            Dataset(const nda& oFM);                        ///< Copy constructor
            Dataset(const nda&& oFM);                       ///< Move constructor
            virtual void operator=(const nda& oFM);         ///< Copy assigment operator
            virtual void operator=(const nda&& oFM);        ///< Move assigment operator
            virtual nda& getFileMatrix() const;             ///< Accessor method
            virtual nda& getPredictions() const;            ///< Accessor method
            virtual void setFileMatrix(const nda& oFM);     ///< Mutator method
            virtual void setPredictions(const nda& oP);     ///< Mutator method
            virtual std::string& string() const;                 ///< Convert to string

        private:
            nda* oFilesMatrix = nullptr;                        ///< Bidimensional array associated with encoded log file
            nda* oPredictions = nullptr;                        ///< Predictions on files
    };

};

#endif ///< MODEL_API_INCLUDE_DATASET_H_