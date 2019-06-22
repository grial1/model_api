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

    py::list l1;
    l1.append(0);
    l1.append(1);
    py::list l2;
    l2.append(1);
    l2.append(0);
    py::list l;
    l.append(l1);
    l.append(l2);

    nda oArr = np::array(l);

    ma::InputDataset oID{oArr};
    cout << py::extract<const char*>(py::str(oID.getFileMatrix())) << endl;
    
    return 0;
}