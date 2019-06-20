/// author Gastón Rial
/// date 2019-06-12

#include "InputDataset.h"

using namespace std;
namespace ma = model_api;

int main(int argc, char** argv)
{

    py::list l1;
    l1.append(0);
    l1.append(1);
    py::list l2;
    l2.append(1);
    l2.append(0);
    py::list l;
    l.append(l1);
    l.append(l2);

    ma::InputDataset oID{np::array(l)};
    
    return 0;
}