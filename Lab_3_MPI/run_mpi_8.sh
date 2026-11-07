#!/bin/bash
#SBATCH --job-name=MPI_Matrix
#SBATCH --time=0:05:00
#SBATCH --ntasks-per-node=8
#SBATCH --partition batch

module load intel/mpi5

cd $SLURM_SUBMIT_DIR

mpirun -np 8 ../mpi_prog