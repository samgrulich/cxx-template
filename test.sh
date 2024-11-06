#!/bin/bash
echo "Compiling..."
cmake -B build -S .
cmake --build build

filepath=$(find build/src -type f -executable -print)

if [ -z "$filepath" ]; then
    echo "No executable files found"
    exit 1
fi

# create tests/out directory
if [ ! -d "tests/out" ]; then
    mkdir tests/out
fi

# parse options
VERBOSE="f"
getopts "v" opt; 
case "$opt" in
    v) VERBOSE="t"
    ;;
    *) echo "unknown argument passed ${OPTARG}"
    ;;
esac


# run the program for each in file in tests/data
input_files=$(ls tests/data | grep .in)
tests_passed=()
tests_failed=()
tests=0
echo
echo "Running tests..."
for file in $input_files; do
    filename="${file%.in}" # remove the extension
    # generate out files
    ./$filepath < tests/data/$file > tests/out/$filename.out 2> tests/out/$filename.err
    # test the outputs
    error_output=$(diff tests/out/$filename.out tests/data/$filename.out)
    ret=$?
    if [ $ret -eq 0 ]; then
        echo "$filename test passed"
        tests_passed+=( ${file} )
    else
        echo "$filename test failed"
        tests_failed+=( ${file} )
        echo 
        echo "Diff output: "
        printf '%s\n' ${error_output}
        echo 
    fi
    if [ $VERBOSE = "t" -o $ret -ne 0 ]; then
        echo "Program output: "
        cat tests/out/$filename.err
        echo "---------------------------------"
    fi

    let tests++;
done

echo
echo "Tests summary: "
echo "${#tests_passed[*]}/${tests} passed"
if [ ${#tests_failed[*]} -eq 0 ]; then
    echo "All tests passed"
else
    echo "Tests failed: ${tests_failed[*]}"
fi

