# Custom Shell

## Running the Shell :

```
$make

$./a.out

```

<br>
<hr>

## Functionality:

This shell supports

a) Builtin commands like ls,cd, echo, pwd etc

b) Background and Foreground process using execvp()

c) User defined functions pinfo to display process information and repeat to repeat multiple commands.

d) Piping and Redirection

e) Transfer of processes from the backround to the foreground and vice versa

f) Handles signals for Ctrl + C and Ctrl + Z

<br>
<hr>

## Structure:

a) Each command has its own file and header file , for example, ls.c and ls.h

b) File prompt is used to display the shell prompt.

c) File bg_exit is used for making custom exit statements for background process.

d) Display_history.c and hist.c are used for the history command

e) print_path file generate the path required in the prompt.

f) File jobs handles the user-defined jobs command. This file reads the status of all background processes and prints relevant information.

g) File sig.c is used to send signals to different processes using the kill command

h) Files fg.c amd fg.h are used to bring background processes to the foreground.

i) Files bg.c and bg.h are used to change the state of background processes from stopped to running.

j) Main.c handles the general running of the shell including but not limited to tokenisation of input , redirection , piping etc.

k) File ctrlc.c and ctrlz.c handle the signals for ctrl + c and ctrl + z respectively.
