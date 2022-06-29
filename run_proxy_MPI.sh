fail () {
  echo "ERROR: $@"
  exit 1
}

INPUT=$1
HOSTFILE=$2
NODERANK=$3
ITSTOP=$4
OUTFILENAME=$5

# if [ ! -d "results" ]; then
# mkdir results || fail "Could not create the results directory"
# fi

# Run command inside docker at directory $(pwd)/bench
docker run --rm --user=$(id -u):$(id -g) -v $(pwd):$(pwd) -w $(pwd)/bench ubuntu:mpi-dev \
	mpirun -np $NODERANK --host $HOSTFILE ../build/lmp -in $INPUT -enablePI -itStop $ITSTOP -outFilePI $OUTFILENAME 1> results/in.spce.results.N.2.out 2> results/in.spce.results.N.2.err || \
	fail "Error when executing LAMMPS"
