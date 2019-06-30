#! /usr/bin/env python3
"""
File    setup.py

Brief   This is the script that installs the predictive model module. Please, refer 
        to model/core.py for the implementation using sklearn

Author  Gastón Rial

Date    30/06/2019
"""
from setuptools import setup

setup(
    name='model_in_tensorflow',
    version='2.1',
    description='This module wrapps the implementation of different machine learning algorithms used in binary classification',
    author='Gastón Rial',
    py_module=['model_in_tensorflow'],
    packages=['model_in_tensorflow'],
    package_dir={'model_in_tensorflow':'src/model/'}
)