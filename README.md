# Printer Server Simulator

This is a simple print server written in C++, providing multi-threaded handling of print jobs. The project allows the producer to receive print jobs from clients and place them into a queue, while the consumer is responsible for taking jobs from the queue and performing the print operation.

- Supports communication between client and server using the TCP/IP protocol.
- Supports multi-threaded processing by running the producer and consumer in parallel, allowing for more efficient handling of print jobs.
- Uses a priority queue to manage print jobs, sorting them based on priority.

# Description

The goal of this print server project is to simulate an actual printing service that can receive print requests from clients and queue the print jobs based on their priority. The server listens on a specified port using the TCP protocol and processes incoming client connections. The producer is responsible for receiving print jobs from the client and placing them in the queue, while the consumer retrieves jobs from the queue and simulates the printing process. The entire printing process is thoroughly logged into the log file. Queue operations use a mutex to ensure exclusive access to the queue between threads. This design not only ensures efficient and accurate handling of print jobs but also guarantees that each step in the process is clearly recorded.

# How to use

**Compile:** `$ make`

**There are two ways to run the print server:**
1. Using the default port (default is 55555): 
`$ ./print_server`
2. Specifying a custom port (e.g., 56789): 
`$ ./print_server 56789`

**Usage Example:**  
Run the print server:
   ```
   $ ./print_server 56789
   ```

Send Print Jobs with job_id, pages, and priority:
   ```
   $ echo "1,5,2" | nc 127.0.0.1 56789
   $ echo "2,3,1" | nc 127.0.0.1 56789
   $ echo "3,9,5" | nc 127.0.0.1 56789
   ```

Sample Log Output for the Above Commands:
   ```
   2025-01-01 00:00:00 Received job ID=1, pages=5, priority=2
   2025-01-01 00:00:00 Job 1 enqueued
   2025-01-01 00:00:00 Printing job ID=1
   2025-01-01 00:00:01 Received job ID=2, pages=3, priority=1
   2025-01-01 00:00:01 Job 2 enqueued
   2025-01-01 00:00:02 Received job ID=3, pages=9, priority=5
   2025-01-01 00:00:02 Job 3 enqueued
   2025-01-01 00:00:04 Completed job ID=1
   2025-01-01 00:00:04 Printing job ID=3
   2025-01-01 00:00:13 Completed job ID=3
   2025-01-01 00:00:13 Printing job ID=2
   2025-01-01 00:00:16 Completed job ID=2
   ```