cmake -B build -S .
cmake --build build

filepath=find "build/src" "-type" "f" "-executable" "-print"

if [ -z "$filepath" ]; then
    echo "No executable files found"
    exit 1
fi

# create tests/out directory
if [ ! -d "tests/out" ]; then
    mkdir tests/out
fi

# run the program for each in file in tests/data
input_files=$(ls tests/data | grep .in)
# for file in $input_files; do
#     filename="${file}"
#     ./build/src/$filepath < tests/data/$file > tests/out/$filename.out 2> tests/out/$filename.err
# done

# run diff tests/out with tests/data for each .out file
output_files=$(ls tests/data | grep .out)
my_output_files=$(ls tests/out | grep .out)
