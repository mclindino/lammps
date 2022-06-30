fail () {
  echo "ERROR: $@"
  exit 1
}

INPUT=$1
NODES=$2
HOSTS=$3
RANK=$4
# if [ ! -d "results" ]; then
# mkdir results || fail "Could not create the results directory"
# fi

# Run command inside docker at directory $(pwd)/bench
docker run --rm --user=$(id -u):$(id -g) -v $(pwd):$(pwd) -w $(pwd)/bench ubuntu:mpi-dev \
	mpirun --allow-run-as-root -np $NODES --host $HOSTS ../build/lmp -in $INPUT 1> results/in.spce.results.$RANK.out 2> results/in.spce.results.$RANK.err || \
	fail "Error when executing LAMMPS"

