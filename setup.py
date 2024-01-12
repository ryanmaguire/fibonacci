"""
################################################################################
#                                   LICENSE                                    #
################################################################################
#   This file is free software: you can redistribute it and/or modify          #
#   it under the terms of the GNU General Public License as published by       #
#   the Free Software Foundation, either version 3 of the License, or          #
#   (at your option) any later version.                                        #
#                                                                              #
#   This file is distributed in the hope that it will be useful,               #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with this file.  If not, see <https://www.gnu.org/licenses/>.        #
################################################################################
#   Purpose:                                                                   #
#       Compiles all of the C code and assembles the Python module.            #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       January 10, 2024                                               #
################################################################################
"""

# Tools being used for compiling and assembling together the Python module.
from distutils.core import setup, Extension

# List of files needed to be compiled for module.
srclist = [

    # This is the C-Python API stuff.
    'src/fibonacci.c',

    # The rest is plain C code. The code for the fibonacci routines.
    'src/fibonacci_iterative.c',
    'src/fibonacci_power_law.c',
    'src/fibonacci_power_law_naive.c',
    'src/fibonacci_recursive.c',
    'src/fibonacci_table.c'
]

# Create the module.
setup(
    name = 'fibonacci',
    version = '0.1',
    description = 'Simple python extension for Fibonacci functions.',
    author = 'Ryan Maguire',
    ext_modules = [Extension('fibonacci', srclist)]
)
