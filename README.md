# model_api

C++ library for wrapping Python3 predictive models (e.g based in scikit-learn or tensorflow). The code in this repo. is part of the implementation of a light stream processing application to analyze system's logs (some kind of HIDS) that is currently in development.

## System requirements
* __OS Used in development:__ Ubuntu 18.04
* __Additional system information:__ Linux 4.18.0-21-generic #22~18.04.1-Ubuntu SMP Thu May 16 15:07:19 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
* __External dependencies:__ [Boost.Python](https://www.boost.org/doc/libs/1_37_0/libs/python/doc/index.html), [Boost.Python (Numpy)](https://www.boost.org/doc/libs/1_63_0/libs/python/doc/html/numpy/tutorial/simple.html) and [pip3](https://pypi.org/project/pip/) 
```
    $ sudo apt-get install -y libboost-python-dev libboost-numpy-dev python3-pip python3-venv
```

## Usage
```
    $ make
    $ sudo make install
    # For testing predictive model induced with scikit-learn's K-NN
    $ make example EXAMPLE=0
    $ source src/module_1/bin/activate
    $ ./example.bin 0
    $ deactivate
    # For testing predictive model induced with tensorflow's K-NN
    $ make example EXAMPLE=1
    $ source src/module_2/bin/activate
    $ ./example.bin 1
    $ deactivate
```

## API documentation
Please refer to *[this page.](https://grial1.github.io/model_api/)*

## Pending:

1) Make it cross-platform
2) Unit tests
