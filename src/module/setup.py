#! /usr/bin/env python3
"""
File    setup.py

Brief   This is the script that installs the predictive model module. Please, refer 
        to model/core.py for the implementation using sklearn

Author  Gastón Rial

Date    15/10/2018
"""
from setuptools import setup


#with open('README.md') as f:
#   readme = f.read()

setup(
    name='model',
    version='2.1',
    description='This module wrapps the implementation of different machine learning algorithms used in binary classification',
    #long_description=readme,
    author='Gastón Rial',
    #test_suite="tests",
    py_module=['model'],
    packages=['model'],
    package_dir={'model':'src/model/'}
)