// author   Gastón Rial
// date     17-06-2019

#include "Dataset.h"

using namespace model_api;

Dataset::Dataset( nda& oFM ):oFilesMatrix{ &oFM }{}

Dataset::Dataset( nda&& oFM ):oFilesMatrix{ &oFM }{}

Dataset::~Dataset()
{

    if(this->oFilesMatrix != nullptr)
        delete this->oFilesMatrix;
    if(this->oPredictions != nullptr)
        delete this->oPredictions;

}