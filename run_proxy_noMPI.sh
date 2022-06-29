function fail() {
  echo "ERROR: $@"
  exit 1
}

INPUT=$1
ITSTOP=$2
OUTFILENAME=$3

if [ ! -d "results" ]; then
mkdir results || fail "Could not create the results directory"
fi

# Run command inside docker at directory $(pwd)/bench
docker run --rm --user=$(id -u):$(id -g) -v $(pwd):$(pwd) -w $(pwd)/bench ubuntu:mpi-dev \
	../build/lmp -in $INPUT -enablePI -itStop $ITSTOP -outFilePI $OUTFILENAME 1> results/in.spce.results.out 2> results/in.spce.results.err || \
	fail "Error when executing LAMMPS"