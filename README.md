Boids-MPI
=========

Boids Algorithm with MPI


## Requirements:

### MPICH2

    $ sudo apt install mpich2 mpich2-doc


### SDL (1.2)

    $ sudo apt install libsdl1.2-dev libsdl1.2debian
  

## Setup Eclipse

`Project › Properties` › `C/C++ Build › Settings`:

C++ Compiler: `Command`  mpic++  <br /> 
├─ Preprocessor: `Defined Symbols` add  __GXX_EXPERIMENTAL_CXX0X__  <br /> 
└─ Miscellaneous: `other flags`  c -fmessage-length=0 -std=c++0x 

C++ Linker: `Command` $ mpic++ $ <br /> 
└─ Libraries: `Libraries`  SDL 
