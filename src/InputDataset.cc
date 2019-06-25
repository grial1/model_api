// author   Gastón Rial Saibene
// date     18-06-2019

#include "InputDataset.h"

using namespace model_api;

InputDataset::~InputDataset() {}                        ///< Destructor

InputDataset::InputDataset( nda& oFM ) : Dataset{oFM} {

    setenv("PYTHONPATH", ".", 1);   ///< Allow Python to load modules from the current directory
    Py_Initialize();                ///< Initialize Python
    
    try
    {
    
        pyObject model = py::import("model");
        this->oModel = model.attr("Model")();

    } catch (const py::error_already_set& )
    {

        PyErr_Print();
        throw std::runtime_error("Error when using Model");

    }

}           ///< Copy constructor

InputDataset::InputDataset(nda&& oFM) : Dataset{oFM} {}          ///< Move constructor

void InputDataset::operator=(nda& oFM) {

    Dataset::operator=(oFM);
    setenv("PYTHONPATH", ".", 1);   ///< Allow Python to load modules from the current directory
    Py_Initialize();                ///< Initialize Python
    
    try
    {
    
        pyObject model = py::import("model");
        this->oModel = model.attr("Model");

    } catch (const py::error_already_set& )
    {

        PyErr_Print();
        throw std::runtime_error("Error when using Model");

    }

}         ///< Copy assigment operator

void InputDataset::operator=(nda&& oFM) {

    Dataset::operator=(oFM);

}        ///< Move assigment operator

nda& InputDataset::getFileMatrix() const
{

    return Dataset::getFileMatrix();

}             ///< Accessor method
        
//nda& InputDataset::getPredictions() const {

//    return Dataset::getPredictions();

//}            ///< Accessor method
            
void InputDataset::setFileMatrix(nda& oFM) {

    Dataset::setFileMatrix(oFM);

}     ///< Mutator method

//void InputDataset::setPredictions(nda& oP)
//{
//
//    Dataset::setPredictions(oP);
//
//}     ///< Mutator method
        
void InputDataset::predict(nda& out){

    setenv("PYTHONPATH", ".", 1);   ///< Allow Python to load modules from the current directory
    Py_Initialize();                ///< Initialize Python
    
    try
    {

        this->oModel.attr("setDataset")(this->getFileMatrix());
        this->oModel.attr("predict")();
        nda oArr = np::array(oModel.attr("getPrediction")());
        out = oArr;

    } catch (const py::error_already_set& )
    {

        PyErr_Print();
        throw std::runtime_error("Error when using Model");

    }

}

void InputDataset::initModel(const nda& oFMTrain,const nda& oPTrain)
{
    setenv("PYTHONPATH", ".", 1);   ///< Allow Python to load modules from the current directory
    Py_Initialize();                ///< Initialize Python

    try
    {

        this->oModel.attr("setDataset")(oFMTrain);
        this->oModel.attr("setPrediction")(oPTrain);
        this->oModel.attr("train")();

    } catch (const py::error_already_set& )
    {

        PyErr_Print();
        throw std::runtime_error("Error when using Model");

    }

}
