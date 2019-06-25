# model_api

C++ library for wrapping Python3 predictive models (e.g based in scikit-learn or tensorflow). The code in this repo. is part of the implementation of a light stream processing application to analyze system's logs (some kind of HIDS) that is currently in development.

## System requirements
* __OS Used in development:__ Ubuntu 18.04
* __Additional system information:__ Linux 4.18.0-21-generic #22~18.04.1-Ubuntu SMP Thu May 16 15:07:19 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
* __External dependencies:__ [Boost.Python](https://www.boost.org/doc/libs/1_37_0/libs/python/doc/index.html), [Boost.Python (Numpy)](https://www.boost.org/doc/libs/1_63_0/libs/python/doc/html/numpy/tutorial/simple.html) and [pip3](https://pypi.org/project/pip/) 
```
    $ sudo apt-get install -y libboost-python-dev libboost-numpy-dev python3-pip
```

## Usage
```
    $ make
    $ sudo make install
    # For testing
    $ make example
```

## API documentation
Please refer to *[this page.](https://grial1.github.io/model_api/)*

## Pending:

1) Make it cross-platform
2) Unit tests
