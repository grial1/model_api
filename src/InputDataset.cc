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

    } catch ( const py::error_already_set& )
    {

        PyErr_Print();
        throw std::runtime_error("Error when using Model");

    }

}

void InputDataset::testModel(const nda& oFMTest,const nda& oPTest, std::vector<PerformaceMetric>& oPMList)
{

    setenv("PYTHONPATH", ".", 1);   ///< Allow Python to load modules from the current directory
    Py_Initialize();                ///< Initialize Python

    try
    {

        this->oModel.attr("setDataset")(oFMTest);
        this->oModel.attr("setPrediction")(oPTest);
        pyObject oResults = this->oModel.attr("test")();

        pyTuple oTuple = static_cast<pyTuple>(oResults);

        /**
         * Provisorial implementation
        */
        int size = py::extract<int>(oTuple[0]);

        for( int i = 1; i < size ; ++i )
        {

            double metric = py::extract<double>(oTuple[i]);

            switch (i)
            {
            case 1:
                oPMList.push_back(TruePositive(metric));
                break;
            case 2:
                oPMList.push_back(TrueNegative(metric));
                break;
            case 3:
                oPMList.push_back(FalsePostive(metric));
                break;
            case 4:
                oPMList.push_back(FalseNegative(metric));
                break;
            case 5:
                oPMList.push_back(Recall(metric));
                break;
            case 6:
                oPMList.push_back(Precision(metric));
                break;
            case 7:
                oPMList.push_back(F1Score(metric));
                break;
            }

        } 

        /**
         * Provisorial implementation
        */

    } catch ( const py::error_already_set& )
    {

        PyErr_Print();
        throw std::runtime_error("Error when testing the Model");

    }

}