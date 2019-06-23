// author   Gastón Rial
// date     17-06-2019

#include "Dataset.h"

using namespace model_api;

Dataset::Dataset( const nda& oFM ):oFilesMatrix{ new nda(oFM) }{}

Dataset::~Dataset()
{

    if(this->oFilesMatrix != nullptr)
        delete this->oFilesMatrix;
    //if(this->oPredictions != nullptr)
    //    delete this->oPredictions;

}