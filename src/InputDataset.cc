// author   Gastón Rial Saibene
// date     18-06-2019

#include "InputDataset.h"

using namespace model_api;

InputDataset::~InputDataset() {}                        ///< Destructor

InputDataset::InputDataset( nda& oFM ) : Dataset{oFM} {}           ///< Copy constructor

InputDataset::InputDataset(nda&& oFM) : Dataset{oFM} {}          ///< Move constructor

void InputDataset::operator=(nda& oFM) {

    Dataset::operator=(oFM);

}         ///< Copy assigment operator

void InputDataset::operator=(nda&& oFM) {

    Dataset::operator=(oFM);

}        ///< Move assigment operator

nda& InputDataset::getFileMatrix() const
{

    return Dataset::getFileMatrix();

}             ///< Accessor method
        
nda& InputDataset::getPredictions() const {

    return Dataset::getPredictions();

}            ///< Accessor method
            
void InputDataset::setFileMatrix(nda& oFM) {

    Dataset::setFileMatrix(oFM);

}     ///< Mutator method

void InputDataset::setPredictions(nda& oP)
{

    Dataset::setPredictions(oP);

}     ///< Mutator method
        
void InputDataset::predict(){

    setenv("PYTHONPATH", ".", 1);   ///< Allow Python to load modules from the current directory
    Py_Initialize();                ///< Initialize Python
    
    try
    {

        pyObject model = py::import("model");
        pyObject oModel = model.attr("Model");
        oModel.attr("setDataset")(this->getFileMatrix());
        oModel.attr("train")();
        oModel.attr("predict")();
        nda oArr = np::array(oModel.attr("getPrediction")());
        this->setPredictions(oArr);

    } catch (const py::error_already_set& )
    {

        PyErr_Print();
        throw std::runtime_error("Error when using Model");

    }

}                         ///< Make prediction from filesmatrix
