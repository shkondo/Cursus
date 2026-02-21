# 42 - Philosophers

*This project has been created as part of the 42 curriculum by shkondo.*

## 1. Description

This project is a simulation of the classic **Dining Philosophers Problem**, designed to teach the fundamentals of concurrent programming in C.

One or more philosophers sit around a circular table with a large bowl of spaghetti in the center. Each philosopher alternates between three states: **eating**, **thinking**, and **sleeping**. A philosopher needs two forks (one on their left, one on their right) to eat, but there is only one fork between each pair of adjacent philosophers.

The simulation ends when a philosopher dies of starvation, or when all philosophers have eaten a specified number of times (if provided).

**Key constraints:**
- Each philosopher runs as an individual **thread** (mandatory part).
- Each fork is protected by a **mutex** to prevent data races.
- No global variables are allowed.
- A philosopher must not starve — a death message must be printed within 10ms of the actual death.

## 2. Instructions

### Compile

```sh
cd philo
make
```

### Run

```sh
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|----------|-------------|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` (ms) | Time in ms since the last meal (or simulation start) before a philosopher dies |
| `time_to_eat` (ms) | Time in ms a philosopher takes to eat (holds two forks during this time) |
| `time_to_sleep` (ms) | Time in ms a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | *(optional)* Simulation ends when all philosophers have eaten at least this many times |

### Example

```sh
./philo 5 800 200 200
./philo 5 800 200 200 7
```

### Clean

```sh
make clean   # Remove object files
make fclean  # Remove object files and binary
make re      # Rebuild from scratch
```

## 3. Resources

- [The Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming — Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/)
- [pthread_mutex_lock(3) man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [gettimeofday(2) man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)
- [42 Norm v4.1](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf)

### AI Usage

Claude Code (claude-sonnet-4-6) was used in this project to assist with:
- Generating the initial `README.md` content based on the project specification.
- Reviewing code structure and logic for correctness and compliance with the 42 Norm.

All core implementation (threading logic, mutex handling, philosopher simulation) was written by the author.
