#!/bin/bash
PATH=$PATH:$PWD/lib
export PATH

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/lib
export LD_LIBRARY_PATH
exec "./QtRptDesigner"
