# processScheduler

## What is Process Scheduling
According to [TutorialsPoint](https://www.tutorialspoint.com/operating_system/os_process_scheduling.htm), The Process Scheduling is the activity of the process manager that handles the removal of the running process from the CPU and the selection of another process on the basis of a particular strategy.

Process scheduling is an essential part of a Multiprogramming operating systems. Such operating systems allow more than one process to be loaded into the executable memory at a time and the loaded process shares the CPU using time multiplexing.

## Behavior

This C project implements 4 kinds of scheduling algorithms using a stack and two priority queues. These algorithms are:
* **First Come First Served** (FCFS) - used for *batch* systems (we want productivity).
* **Shortest Job First** (SJF) - used for *batch* systems (we want productivity).
* **Round Robin - cyclic executive** - used for *interactive* systems (we want fairness).
* **Round Robin - with priorities** - used for *interactive* systems (we want fairness).

Lets call `quantum` = how many *ticks* a process needs to be completed. We will define a *tick* later.
The program reads commands from an `input_file` and writes output to another file.

### Commands
The implemented commands are the following:
* `t` - **tick**, time passes
* `a name x y` - **add** a new process named `name` that has quantum `x` and priority `y`
* `ma name1 x1 y1 name2 x2 y2 ...` **multiple add**, the same meaning as **add** but with more processes
* `w` - **wait**, the RUNNING process goes to WAITING
* `e name` - **event**, an event wakes process `name` from WAITING
* `s` - **show**, prints info about the RUNNING process: `name_of_the_process quantum_of_current_process`

After the following commands, an implicit `t` is executed: `a`, `ma`, `w`, `e`.

### About the `input_file`
The input_file has the following form:\
`1 / 2 / 3 x / 4 x y / 5 x y`\
`command1`\
`command2`\
`command3`\
`...`

where 1/2/3/4/5 are the type of scheduling algorithms used:
* 1 = `FCFS`, 2 = `SJF` 3 = `RR - cyclic executive`,
4 = `RR - with priorities`, 5 = `RR - with dynamic priorities` (*dynamic* means that the scheduler can update the priorities in time).
* `x` = quantum and `y` = the number of priority levels

## How to run it
1. Compile `planificator.c` using make or your favourite compiler.
2. Write your `input_file`. You can find an example in `fisier1`.
3. Run your program and don't forget to mention `input_file` and `output_file`.\
`./planificator input_file output_file`
4. Remember, all the output will be written into the `output_file` you specified inside the command.

## Have fun and keep on coding! :)
