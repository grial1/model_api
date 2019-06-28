// author   Gastón Rial Saibene
// date     18-06-2019

#include "InputDataset.h"

using namespace std;

static inline 
void splitString(const string& str, vector<string>& output, char delim = ' ')
{
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim)) {
        output.push_back(token);
    }
}

static inline 
double getDoubleValue(const char* element)
{

    vector<string> oVecDouble;
    splitString(string{element},oVecDouble,'.');
    double value = static_cast<double>(atoi(oVecDouble[0].c_str()));
    double raw_decimal = static_cast<double>(atoi(oVecDouble[1].c_str()));
    double power =  ceil(raw_decimal/10);
    double decimal = raw_decimal/pow(10,power);
    value += decimal;
    return value;

}

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
         * BEGIN: Provisorial implementation
        */
        int size = py::extract<int>(oTuple[0]);


        for( int i = 1; i < size+1 ; ++i )
        {

            const char* strValue = py::extract<const char*>(py::str(oTuple[i]));
            switch (i)
            {
                case 1:
                {
                    double metric = static_cast<double>(atoi(strValue));
                    oPMList.push_back(TruePositive(metric));
                    break;
                }
                case 2:
                {   
                    double metric = static_cast<double>(atoi(strValue));
                    oPMList.push_back(TrueNegative(metric));
                    break;
                }            
                case 3:
                {
                    double metric = static_cast<double>(atoi(strValue));
                    oPMList.push_back(FalsePostive(metric));
                    break;

                }
                case 4:
                {
                    double metric = static_cast<double>(atoi(strValue));
                    oPMList.push_back(FalseNegative(metric));
                    break;
                }                    
                case 5:
                {
                    double metric = getDoubleValue(strValue);
                    oPMList.push_back(Recall(metric));
                    break;
                }
                case 6:
                {
                    double metric = getDoubleValue(strValue);
                    oPMList.push_back(Precision(metric));
                    break;
                }                
                case 7:
                {
                    double metric = getDoubleValue(strValue);
                    oPMList.push_back(F1Score(metric));
                    break;
                }
                
            }

        } 

        /**
         * END: Provisorial implementation
        */

    } catch ( const py::error_already_set& )
    {

        PyErr_Print();
        throw std::runtime_error("Error when testing the Model");

    }

}