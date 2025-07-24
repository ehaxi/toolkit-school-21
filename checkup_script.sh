#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Error! please write: bash $0 <file.c> <git/nogit>"
    exit 1
fi

file="$1"
flag="$2"
errors_counter=0

if [ ! -f "$file" ]; then
    echo "Error: file '$file' does not exist"
    exit 1
fi

if [ ! -f ".clang-format" ]; then
    echo "Error: file '.clang-format' not found"
    exit 1
fi

current_branch=$(git rev-parse --abbrev-ref HEAD)

if [ "$current_branch" != "develop" ]; then
    echo "Current branch is not develop"
    if git branch --list develop > /dev/null; then
        git switch develop
    else
        echo "Branch 'develop' does not exist"
        git checkout -b develop
        echo "Branch 'develop' created"
    fi
    echo "You are in the 'develop' branch"
    git push -u origin develop
fi

format_checker=$(clang-format -n "$file" 2>&1)

if [ -z "$format_checker" ]; then
    echo "The code stylized"
else
    echo "The code is not styled"
    echo "$format_checker" > format_errors.txt
    format_editor=$(clang-format -i "$file")
    echo "The code has been stylized"
fi

cppcheck_checker=$(cppcheck --enable=all --suppress=missingIncludeSystem "$file" 2>&1)

if echo "$cppcheck_checker" | grep -i -qE "error|warning"; then
    echo "'cppcheck' check failed"
    echo "$cppcheck_checker" > cppcheck_errors.txt
    echo "Errors are written to the file 'cppcheck_errors.txt'"
    ((errors_counter++))
else
    echo "'cppcheck' check passed succesfully"
fi

code_compiler=$(gcc -std=c11 -Wall -Wextra -Werror -o "${file%.c}" "$file" 2>&1)

if echo "$code_compiler" | grep -i -qE "error|warning"; then
    echo "Compilation error"
    echo "$code_compiler" > compile_errors.txt
    echo "Errors are written to the file 'compile_errors.txt'"
    ((errors_counter++))
else
    echo "Code compile successfully"
fi

if [ "$errors_counter" -lt 1 ]; then

    valgrind_checker=$(valgrind --tool=memcheck --leak-check=yes ./"${file%.c}" 2>&1)

    if echo "$valgrind_checker" | grep -i -qE "error|warning"; then
        echo "Leaks detected"
        echo "$valgrind_checker" > info_leaks.txt
        echo "Leaks are written to the file 'info_leaks.txt'"
        ((errors_counter++))
    else
        echo "No leaks found"
    fi
fi


if [ "$flag" == "git" ]; then
    if [ "$errors_counter" -eq 0 ]; then
        echo "Enter the commit name: "
        commit_text="$3"
        git add "$file"
        git commit -m "'$commit_text'"
        git push
    else
        echo "Fix the errors before commit and push"
    fi
fi
