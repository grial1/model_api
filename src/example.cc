/// author Gastón Rial
/// date 2019-06-30

#include <iostream>
#include <vector>
#include <string>
#include "InputDataset.h"
#include "utils/jsonparser_impl.h"

using namespace std;
namespace ma = model_api;

int main(int argc, char** argv)
{
 
    Py_Initialize();
    np::initialize();
    
    ///< Initizalize a 2x2 matrix
    py::list l1;    ///< First row
    l1.append(0);
    l1.append(1);
    py::list l2;    ///< Second row
    l2.append(1);
    l2.append(0);
    py::list l;     ///< Matrix
    l.append(l1);
    l.append(l2);
    py::list l3 = l1;   ///< Example of prediction for training
    nda oFileMatExample = np::array(l);
    nda oPredictionsExample = np::array(l3);
    py::tuple shape = py::make_tuple(1, 2);
    np::dtype dtype = np::dtype::get_builtin<float>();
    nda oPredictions = np::empty(shape,dtype); ///< Output

    if (argc < 2 || atoi(argv[1]) == 0)
    {

        Json oJsonConfig; oJsonConfig = std::string{"{\"module\":\"model\"}"};
        ma::InputDataset oID{oFileMatExample,oJsonConfig};
        //ma::InputDataset oID{oFileMatExample};

        cout << py::extract<const char*>(py::str(oID.getFileMatrix())) << endl;

        oID.initModel(oFileMatExample, oPredictionsExample);
        oID.predict(oPredictions);
        cout << py::extract<const char*>(py::str(oPredictions)) << endl;

        ///< Evaluating model
        nda oFileMatTest = np::array(l);
        nda oPredictionsTest = np::array(l2);
        std::vector<PerformaceMetric> oPMList;
        oID.testModel(oFileMatTest,oPredictionsTest,oPMList);

        for(auto oPM : oPMList)
            cout << oPM <<"\n" << endl;

    } 
    else if( atoi(argv[1]) == 1)
    {
        ///< Example of configurable predictive model module
        Json oJsonConfig; oJsonConfig = std::string{"{\"module\":\"model_in_tensorflow\"}"};
        ma::InputDataset oID{oFileMatExample,oJsonConfig};

        cout << py::extract<const char*>(py::str(oID.getFileMatrix())) << endl;

        oID.initModel(oFileMatExample, oPredictionsExample);
        oID.predict(oPredictions);
        cout << py::extract<const char*>(py::str(oPredictions)) << endl;

        /*
        ///< Evaluating model
        nda oFileMatTest = np::array(l);
        nda oPredictionsTest = np::array(l2);
        std::vector<PerformaceMetric> oPMList;
        oID.testModel(oFileMatTest,oPredictionsTest,oPMList);

        for(auto oPM : oPMList)
            cout << oPM <<"\n" << endl;
         */
    }
    
    return 0;
}