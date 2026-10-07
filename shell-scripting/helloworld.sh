#!/bin/bash

# This is a comment

#ls
#pwd
#echo Hello

# In a bash script, you have to be VERY careful about ALL spaces.

# More advanced bash features
# Variables:
I_LIKE_SPAGHETTI=true

# There are no "types" in Bash scripts.
# Everything is a string.
# So I_LIKE_SPAGHETTI is essentially a string variable
# storing the word "true"

# The same syntax can be used to change the value of a variable
OH=oh
YEAH=yeah
I_LIKE_SPAGHETTI="$OH $YEAH"

# Nothing is expanded within single quotes. The characters are all
# left as-is, treated literally

# To "retrieve" the value of a variable, prefix its name with
# $
echo $I_LIKE_SPAGHETTI

# Generally speaking, in a given Bash command, whitespace separates
# arguments.
#
echo "hello         world"

printf 'Hello%d\n' 7

# In almost all cases, when you expand a variable,
# you should do so inside double quotes

count="20"
if [[ "$count" -eq 20 ]]
then
	# Body goes here
	echo "Hello, World"
elif [[ "$count" -eq 21 ]]
then
	echo "Goodbye, World"
else
	# Some body goes here
	: # : is a no-op
fi


# Suppose I want an if statement that executes if and only if
# the file hello.txt exists and is readable:
if [[ -r hello.txt ]]
then
	echo "hello.txt exists and is readable. Here are its contents:"
	cat hello.txt
else
	echo "hello.txt does not exist, or it is not readable"
fi

# -r checks if the file is readable
# -e checks if the file exists
# -x check if the file is executable
# -f checks if the file exists and is a regular file
# -d checks if the file exists and is a directory

if [[ ! ( "$count" -lt 10 || "$count" -gt 25 ) ]]
then
	echo "Between 10 and 25"
fi

# &&: logical and
# ||: logical or
# !: logical not

if [[ ! -e somefile.txt ]]
then
	echo "somefile.txt does not exist"
fi

# While loop syntax is similar to if statement syntax
i=0
while [[ "$i" -lt 10 ]]
do
	# Loop body goes here
	echo "$i. Hello, World"

	# To increment a variable:
	i=$((i+1))
done

# For loops, far more interesting
for itr in hello goodbye world 1 2 3 a b c
do
	# For loop body goes here
	echo "$itr"
done

# * in Bash is a glob pattern / wildcard
# (apparently doesn't match hidden files)

# Print names of all  files in working directory ending with .txt
for f in ./*.txt
do
	echo "$f"
done

# You can create functions in Bash
foo() (
	# Body goes here
	echo "foo() was called"

	# Retrieves the first argument passed to foo (NOT the first
	# shell script argument)
	echo "$1"

	# Similarly, $2, $0, $3, $#
)

foo hello goodbye

# In a given shell script, there are special variables
# that you can use to reference the command-line arguments
# passed to said shell script:
# 0, 1, 2, 3, ...
echo "$0" # basically the same thing as argv[0] in a C program
echo "$1" # basically the same thing as argv[1] in a C program

# There's also a special variable in every Bash script
# named # that tells you the number of command-line arguments
# that were passed to the shell script, not counting
# command name (basically, argc - 1)
echo "$#"

# In a bash command, you can redirect the command's standard output,
# standard input, and standard error streams to files
# >: standard output redirection operator, in truncate mode (overwrites
#     existing file contents, if any)
# >>: standard output appending redirection operator
echo "Hello, World" >> data.txt

# <: Standard input redirection operator
# 2>: standard error redirection operator, truncation
# 2>>: standard error redirection operator, append

# You can also redirect the standard output of one command
# into the standard input of another command
# |: pipe operator (does as described above)

echo "Hello, world" | cat
echo -e "world\nhello\ncat" | sort

ls { a b }

for itr in "$@"
do
	echo "$itr"
done
