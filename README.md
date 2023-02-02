# Learn Message Passing Interface in 3 days 

Following [this course](http://archer.ac.uk/training/course-material/2014/07/MPI_Edi/) from EPCC, University of Edinburgh. 

### How to run 

On Mac, first install MPI locally 

```
brew install open-mpi
```

compile C file and run the program using the following commands

```
mpicc -o program ./program.c
mpirun -np [NUMBER_OF_PROCESSORS] ./program
```
