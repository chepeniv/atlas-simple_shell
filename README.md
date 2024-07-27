# $$hell: A Shell with an Attitude
![attitude](./assets/attitude.gif)

## Brief

A bare-bones Unix shell implementation in C, perfect for learning the ropes of process management and command execution.

## Table of Contents
1. Description
	1. Operation
	2. Installation
	3. Features
	4. Limitations
	5. Examples
	6. Bugs
2. Status and Roadmap
3. Documentation and Support
4. Acknowledgements
5. Resources
6. Licence

# Description
## Operation
![flowchart](./assets/atlas-shell-main-v2.png)

## Installation

1. **Compile:**

```bash
gcc -Wall -Werror -Wpedantic -o $$$hell simple_shell.c

2. **Run**
Bash
./$$$hell

Now you'll see the super cool prompt:

$$$hell :: 
Type your command (with full path!) and hit Enter.

Example
$$$hell :: /bin/ls
$$$hell :: /usr/bin/whoami
$$$hell :: exit
exiting...
```
## Features

* **Command Execution:** Runs external commands entered by the user (e.g., `/bin/ls`, `/usr/bin/whoami`).
* **Argument Handling:** Supports commands with arguments (e.g., `ls -l /tmp`).
* **"exit" Command:** Gracefully terminates the shell.
* **Ctrl+D (EOF) Handling:** Exits when you're done playing around.
* **Error Handling:** Catches those pesky `fork` and `execve` fails, letting you know what's up.

## Limitations

* **No PATH Search:** You gotta give the full path to commands, no shortcuts!
* **No Built-ins:** No fancy `cd` or `env` commands here, just the basics.
* **No Fancy Stuff:** Forget about pipes (`|`), redirection (`>`, `<`), or wildcards (`*`). This shell keeps it simple.

## Examples
## Bugs

# Status and Roadmap
abandoned. we wish to leave this behind. 

# Documentation and Support
none, but if you want a bit more details, here's this. now, leave us alone.
``` 
man ./man_1_simple_shell
```
# Acknowledgments
coffee :pray: 
# Resources
# License
do what you want
