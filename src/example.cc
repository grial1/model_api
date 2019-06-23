/// author Gastón Rial
/// date 2019-06-12

#include "InputDataset.h"
#include <iostream>

using namespace std;
namespace ma = model_api;

int main(int argc, char** argv)
{
    //setenv("PYTHONPATH", ".", 1);
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

    ma::InputDataset oID{oFileMatExample};
    //oID.setPredictions(oPredictions);

    cout << py::extract<const char*>(py::str(oID.getFileMatrix())) << endl;

    oID.initModel(oFileMatExample, oPredictionsExample);

    py::tuple shape = py::make_tuple(1, 2);
    np::dtype dtype = np::dtype::get_builtin<float>();
    nda oPredictions = np::empty(shape,dtype); ///< Output

    oID.predict(oPredictions);
    cout << py::extract<const char*>(py::str(oPredictions)) << endl;
    
    return 0;
}