/// author Gastón Rial
/// date 2019-06-12

#include "InputDataset.h"
#include <iostream>

using namespace std;
namespace ma = model_api;

int main(int argc, char** argv)
{
    setenv("PYTHONPATH", ".", 1);
    Py_Initialize();
    np::initialize();

    ///< Initizalize a 2x2 matrix
    py::list l1;    ///< First row and example of prediction for training
    l1.append(0);
    l1.append(1);
    py::list l2;    ///< Second row
    l2.append(1);
    l2.append(0);
    py::list l;     ///< Matrix
    l.append(l1);
    l.append(l2);

    nda oFileMatExample = np::array(l);
    nda oPredictions = np::array(l1);

    ma::InputDataset oID{oFileMatExample};
    oID.setPredictions(oPredictions);

    cout << py::extract<const char*>(py::str(oID.getFileMatrix())) << endl;
    cout << py::extract<const char*>(py::str(oID.getPredictions())) << endl;
    
    return 0;
}