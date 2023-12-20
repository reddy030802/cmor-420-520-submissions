#!/bin/bash

# is project name provided?
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 project_name"
    exit 1
fi

project=$1

# create .build directory if it doesn't exist
mkdir -p .build

# compile
pdflatex -output-directory .build "$project.tex"

# move back
mv ".build/$project.pdf" .

echo "Build completed for $project"
