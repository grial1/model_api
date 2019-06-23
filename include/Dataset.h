///  author  Gastón Rial
///  date    2019-06-16

#ifndef MODEL_API_INCLUDE_DATASET_H_
#define MODEL_API_INCLUDE_DATASET_H_

#pragma once

#include <string>
#include <boost/python.hpp>
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
            Dataset( const nda& oFM );                        ///< Copy constructor
            
            virtual void operator=( const nda& oFM )         ///< Copy assigment operator
            {

                this->oFilesMatrix = new nda(oFM);

            }
            
            virtual void operator=( nda&& oFM )        ///< Move assigment operator
            {

                this->oFilesMatrix = &oFM;

            }

            virtual nda& getFileMatrix() const             ///< Accessor method
            {
                
                if( this->oFilesMatrix != nullptr )
                    return *(this->oFilesMatrix);

            }

            //virtual nda& getPredictions() const            ///< Accessor method
            //{
//
            //    if( this->oPredictions != nullptr )
            //        return *(this->oPredictions);
//
            //}

            virtual void setFileMatrix( nda& oFM)     ///< Mutator method
            {

                this->oFilesMatrix = &oFM;

            }

            //virtual void setPredictions( nda& oP)     ///< Mutator method
            //{
//
            //    this->oPredictions = &oP;
//
            //}

        private:
            nda* oFilesMatrix = nullptr;                        ///< Bidimensional array associated with encoded log file
            //nda* oPredictions = nullptr;                        ///< Predictions on files
    };

};

#endif ///< MODEL_API_INCLUDE_DATASET_H_