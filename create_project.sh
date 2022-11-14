#!/usr/bin/env sh

if [ $# -ne 1 ]
  then
    echo "Provide the name of the project as the first argument"
    exit
fi

# Clean up the project name (Convert special chars to _, uppercase to lowercase)
project_name="$(echo "$1" | sed -e 's/[^A-Za-z0-9._-]/_/g' | tr '[:upper:]' '[:lower:]')"

projects_directory="./thestuff/"

project_directory="./thestuff/$project_name/"

if [ -d "$project_directory" ]; then
    echo "Project seems to already exist"
    exit
fi

mkdir "$project_directory"

echo "# $project_name" > "$project_directory/README.md"
