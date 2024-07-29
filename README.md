# $$HELL: *Shell with Attitude*
![attitude](./assets/attitude.gif)

## Brief

Buckle Up, Buttercup! Introducing $$hell, the Shell with an Attitude! 💅 A bare-bones Unix shell implementation in C, perfect for learning the ropes of process management and command execution.

## Table of Contents
1. Description
	1. Operation
	2. Installation
	3. Features
	4. Limitations
	5. Examples
	6. Bugs
2. Status and Roajjdmap
3. Documentation and Support
4. Acknowledgements
5. Resources
6. Licence

# Description
## Operation

```
	$ ash [cmd] [options] [arguments]
```

![flowchart](./assets/atlas-shell-main-v2.png)

## Installation

1. Compile: If you can't figure this out, you probably shouldn't be using a shell. But whatever...

```bash
gcc -Wall -Werror -Wpedantic -o $$hell simple_shell.c
```

2. **Run**
```bash
./$$hell
```

Now you'll see the super cool prompt:

```
(ง'̀-'́)ง 
```
Interactive: `./$$hell`\
Non Interactive: `./$$hell <command>` (*Don't forget to replace command with something worthy of my attention*)

## Features that'll make you go "YAS Queen":

* **Command Execution:** Runs external commands entered by the user (e.g., `/bin/ls`, `/usr/bin/whoami`).
* **Non-Interactive Mode** (Because who needs friends right?): Feed me a single command and I'll execute it, no chit chat, just results. 
* **Interactive Mode** (Oh someone's feeling social now huh?): Hang out in my shell and type commands to your heart's content. But don't expect me to be impressed.
* **Built in sass and command support** (for only the ones I want): Every prompt is a reminder you're in a shelll that knows it's worth.
* **Environmentally conscious:** I CAN display your environment variables using the 'env' command. Because even a sassy shell cares about it's surroundings. 
* **Pathfinder Extraordinaire:** I can locate commands like a pro, even if they're hiding.  
* **Argument Handling:** Supports commands with arguments (e.g., `ls -l /tmp`).
* **"exit" (stage left) Command:** When you've had enough of me, just type exit and I'll let you go.
* **Ctrl+D (EOF) Handling:** Exits when you're done playing around.
* **Error Handling:** Catches those pesky `fork` and `execve` fails, letting you know what's up.

## Limitations
* **No Fancy Stuff:** Forget about pipes (`|`), redirection (`>`, `<`), or wildcards (`*`). This shell keeps it simple.\
Our simple shell (ash) connot handle special characters nor any dynamic movement of the cursor. This also means unfortunately that neither auto-complete nor shell history are implemented. furthermore, most all of the popular advanced features such as chaining, piping, and redirections are not implemented as well.

## Examples

The following is an example of ash running in interactive mode

```
	user@this_machine:~/path$ ./ash
	(ง'̀-'́)ง echo Wello, Horld!
	Wello, Horld!
	(ง'̀-'́)ง pwd
	~/path
	(ง'̀-'́)ง exit
	user@this_machine:~/path$ 
```

Here it is running in non-interactive mode

```
	user@this_machine:~/path$ ./ash cat somefile.txt
	Hello, World!
	user@this_machine:~/path$ 
```

## Bugs
There had better not be any with the amount I pay in rent...

# Status and Roadmap
abandoned. we wish to leave this behind. 

# Documentation and Support
none, but if you want a bit more details, here's this. now, leave us alone.
``` 
man ./man_1_simple_shell
```
# Acknowledgments
coffee :pray:, `man` pages

# Resources

1. <https://en.wikipedia.org/wiki/Unix_shell>
2. <https://en.wikipedia.org/wiki/Bash_(Unix_shell)>
3. <https://www.gnu.org/software/bash/manual/bash.html>
4. <https://linux.die.net/man/>
5. <https://en.wikipedia.org/wiki/C_standard_library>
6. <https://en.cppreference.com/w/c/header>
7. <https://sourceware.org/glibc/manual/latest/html_mono/libc.html>

# License
do what you want. Disclaimer: I'm not responsible for any eyerolls or spontaneous hair flips caused by my sassiness.

<!--------
these are .md comments, they're invisible. it is some of what i've written for the the man page. you could use this as refererce if needed.

ash - a minimal re-implementation of shell

DESCRIPTION
This is a simple emulation of the classic UNIX shell. It can run in both interactive and non-interactive modes depending on whether or not arguments were passed during initiation. Our shell is primarily designed to handle simple singular commands. Along with these, options and arguments may be given as well.

OPERATION
If no arguments were passed at initiation, then Ash sets its mode into interactive. In this state it displays a prompt in stdout for the user and then it awaits for input coming from stdin. Once input has been received, it is interpreted and executed (if a matching command is found) along with its options and arguments, and once all subprocess created in response conclude, it will repeat the entire described series of steps again until an `exit` command is detected -- upon which our shell program terminates safely.
If a no matching command is found within the /bin/ directory then an error message is output.

BUGS
Since our implementation is very minimal by comparison to any of the broadly distributed shells, and because our approach may not have been conventional, there may be some unexpected behaviour somewhere amongst the edge cases. it is also possible that standard shell bugs may have been inadvertently duplicated as well. These all remain to be discovered
-------->
