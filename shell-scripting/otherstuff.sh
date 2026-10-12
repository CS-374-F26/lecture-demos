#!/bin/bash

# Every process has a set of variables managed by the OS known
# as environment variables. They are always strings.
# When a child process is created by another parent process,
# the child process inherits the environment variables from its parent.
#
# However, a process may also change its own environment variables.

# In a shell script, when the script starts, the environment variables are
# exposed as regular shell variables.

# HOME is a standard environment variable.
# It stores the path to the current user's home directory.
echo "$HOME"

# There are many "standard" environment variables.
# HOME (as above)
# PATH: the system path. The system PATH stores a colon-separated list
#       of directories in which programs are located.
# USER: The name of the current user
# UID:  The ID of the current user
# SHELL: The current shell that is executing

# This modifies the shell variable known as PATH, but it does not update
# the process's environment variable known as PATH
PATH="$PATH:/bin"

# The export command can be used to "export" a shell variable into
# a corresponding environment variable
export PATH

# ./otherscript.sh # Inherits the new PATH environment variable


# /dev/null is a special "black hole" kind of file. It's always
# eternally empty.
cd fjdsafjdsajfdsajf &> /dev/null
cd_exit_status="$?"

# Maybe here we want to check if cd failed, and if so, handle the error
if [[ "$cd_exit_status" != 0 ]]
then
	echo "cd failed for some reason" >&2

	# The exit command takes no arguments or one argument.
	# If you give no arguments, it terminates the shell,
	# 	yielding an exit status of 0.
	# If you give an argument, it's the intended exit status.
	# exit 1
fi

# Command substitution: Suppose you want to execute a command,
# and capture its standard output
# cat $(ls)


# You can of course do arithmetic in a shell script.
# However, using basic Bash built-in syntax, we're limited to
# integer arithmetic.
# If you want to do floating point arithmeitc, you must delegate that
# to a more complicated calculator program like bc, awk, Python

# Integer arithmetic in bash:
result="$((1 + 7 * 2))"

echo "$result"

i=1
((i++)) # Shorthand, this increments i. Note: No $

echo "$i" # Prints 2

((i+=7)) # i is now 9
echo "$i" # Prints 9

echo "$((9 / 2))" # Prints 4. The rule is truncation. 4.5 is truncated to 4

echo "$((-9 / 2))" # Prints -4

# You can use parens for grouping
echo "$((7 - (2 + 2)))"

echo $((2 ^ 5)) # Bitwise XOR
echo $((2 ** 5)) # Exponentiation

# 0010
# 0101
# 0111
