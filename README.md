# Minishell
A Mini Shell Project done with Lomeniga.

# Shell Screen
![image](https://user-images.githubusercontent.com/44801448/216525475-a9330c9f-944e-4d46-9ea2-fdf2fa5836c2.png)

# Features

Display a prompt waiting for a new command.

Have a functional history.

Search and launch the correct executable (based on the PATH environment variable or a relative or absolute path).

Do not use more than one global variable.

Handle ' (single quote) which prevent the shell from interpreting meta-characters present in the sequence between quotation marks.

Handle " (double quote) which prevent the shell from interpreting meta-characters present in the sequence between quotation marks except $ (dollar sign).

Implement the following redirections:

< redirect the input.

| redirect the output.

<< receive a delimiter and read the input given until encountering a line containing the delimiter.

|| redirect the output in append mode.

Implement pipes (| character). The output of each command in the pipeline is connected to the input of the following command via a pipe.

Handle environment variables ($ followed by a sequence of characters) which is substituted with their content.

Handle $? which is substituted with the exit status of the last foreground pipeline executed.

Handle ctrl-C, ctrl-D, and ctrl-\ which function as in bash.

In interactive mode:

ctrl-C displays a new prompt on a new line.

ctrl-D exits the shell.

ctrl-\ does nothing.

Our shell implement the following built-ins:

echo and the -n option

cd only with a relative or absolute path

pwd without any options

export without any options

unset without any options

env without any options or arguments

exit without any options.

# Project Grade

![image](https://user-images.githubusercontent.com/44801448/216527563-c0efb0bd-4beb-4105-b63d-5de55e14ef7b.png)
