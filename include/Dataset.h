/// @file Dataset.h
/// @author Gastón Rial
/// @date 2019-06-16
/// @brief abstract class to be extended and implemented by InputDataset

#ifndef MODEL_API_INCLUDE_DATASET_H_
#define MODEL_API_INCLUDE_DATASET_H_

#pragma once

#include <string>
#include <vector>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include "evaluation.h"

namespace np = boost::python::numpy;
using nda = np::ndarray;

/// @namespace model_api
/// @brief Namespace that gathers all the API classes
namespace model_api
{
    
    /// @class Dataset
    /// @brief Abstract class that represents a data set
    class Dataset
    {

        public:
            Dataset()=delete;                           ///< Delete default construtor
            virtual ~Dataset()=0;                       ///< Destructor

        protected:
            /// @param oFM ndarray with data instances
            Dataset( const nda& oFM );                  ///< Copy constructor
            
            /// @param oFM ndarray with data instances
            virtual void operator=( const nda& oFM )    ///< Copy assigment operator
            {

                this->oFilesMatrix = new nda(oFM);

            }

            /// @param oFM ndarray with data instances
            virtual void operator=( nda&& oFM )        ///< Move assigment operator
            {

                this->oFilesMatrix = &oFM;

            }

            /// @return ndarray with data instances
            virtual nda& getFileMatrix() const        ///< Accessor method
            {
                
                if( this->oFilesMatrix != nullptr )
                    return *(this->oFilesMatrix);

            }

            /// @param oFM ndarray with data instances
            virtual void setFileMatrix(nda& oFM)    ///< Mutator method
            {

                this->oFilesMatrix = &oFM;

            }
            /// @param oPMList list of metrics to be returned
            virtual void testModel(const std::vector<PerformaceMetric>& oPMList)=0;  ///< Method that returns a list of evaluation metrics from a tested model

        private:
            nda* oFilesMatrix = nullptr; ///< Bidimensional array associated with encoded log file
    };

};

#endif ///< MODEL_API_INCLUDE_DATASET_H_