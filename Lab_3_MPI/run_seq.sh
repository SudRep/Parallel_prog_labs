#!/bin/bash
#SBATCH --job-name=SEQ_Matrix
#SBATCH --time=0:05:00
#SBATCH --ntasks-per-node=1
#SBATCH --partition batch

cd $SLURM_SUBMIT_DIR

../seq_prog