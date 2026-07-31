# ztop

A lightweight macOS process monitor written in C.

ztop is a command-line project I’m building to better understand how macOS represents and manages processes. The goal is to gradually build a process monitoring tool similar to `top` while learning how programs interact with operating-system APIs.

## Current Status

**Version 1 — Process Listing**

The first version of ztop can enumerate running processes and display information about them, including:

* Process ID (PID)
* Process name
* Process state

Example:

```text
PID       PROCESS              STATE
1         launchd              running
324       Safari               sleeping
891       Terminal             running
```

The project currently focuses on learning how to retrieve process information from macOS rather than building a full terminal UI.

## Technologies

* C
* Clang
* macOS APIs
* libproc
* Git
* LLDB
* Make

## How It Works

ztop uses macOS's `libproc` APIs to retrieve information about running processes.

The basic process is:

1. Ask macOS for the list of running process IDs.
2. Retrieve information about each process.
3. Determine the process name and state.
4. Display the results in the terminal.

This has been a useful introduction to working with operating-system APIs and understanding how process information is exposed to user-space programs.

## Building

Clone the repository and build the project:

```bash
git clone https://github.com/JacobZhang0/ztop.git
cd ztop
make
```

Then run:

```bash
./ztop
```

## Debugging

I use Clang's debugging and sanitizing tools while developing ztop.

Compile with:

```bash
clang -Wall -Wextra -g -fsanitize=address,undefined *.c
```

Debug with LLDB:

```bash
lldb ./ztop
```

Useful LLDB commands include:

```text
breakpoint set
run
bt
frame variable
memory read
```

## Development Roadmap

ztop is being developed incrementally, with each version focusing on a different operating-system concept.

### Version 1 — Process Listing

* [x] Enumerate running processes
* [x] Display process IDs
* [x] Display process names
* [x] Display process states

### Version 2 — Memory Usage

* [ ] Display process memory usage
* [ ] Learn about virtual and resident memory
* [ ] Format memory values for the terminal

### Version 3 — CPU Usage

* [ ] Sample process CPU time
* [ ] Calculate CPU utilization
* [ ] Display CPU percentage

### Version 4 — Refresh Loop

* [ ] Continuously refresh process information
* [ ] Add terminal screen clearing
* [ ] Add update timestamps

### Version 5 — Sorting

* [ ] Sort by CPU usage
* [ ] Sort by memory usage
* [ ] Sort by PID
* [ ] Sort by process name

### Version 6 — Process Details

* [ ] Inspect an individual process with `--pid`
* [ ] Display thread count
* [ ] Display parent process
* [ ] Display detailed CPU and memory information

### Version 7 — Process Control

* [ ] Add optional signal handling
* [ ] Support terminating processes with `SIGTERM`
* [ ] Handle process permissions

## Future Ideas

If the core monitor is completed, I may add additional features such as:

* Thread monitoring
* File descriptor information
* Memory pressure information
* More detailed process hierarchy information
* An interactive terminal interface using `ncurses`

## Why I Built This

I wanted a project that would force me to work closer to the operating system instead of only using high-level libraries.

Building ztop gives me hands-on experience with:

* Processes and process IDs
* System information APIs
* Memory management
* CPU accounting
* Signals
* Threads
* Debugging with LLDB
* Low-level C programming on macOS

The project is intentionally being built one feature at a time so I can understand how each part works before adding more complexity.
