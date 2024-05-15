```
	  ██╗   ██╗██╗██╗   ██╗ █████╗     ███╗   ███╗██╗   ██╗██████╗  ██████╗██╗ █████╗
	  ██║   ██║██║██║   ██║██╔══██╗    ████╗ ████║██║   ██║██╔══██╗██╔════╝██║██╔══██║
	  ██║   ██║██║██║   ██║███████║    ██╔████╔██║██║   ██║██████╔╝██║     ██║███████║
	  ╚██╗ ██╔╝██║╚██╗ ██╔╝██╔══██║    ██║╚██╔╝██║██║   ██║██╔══██╗██║     ██║██╔══██║
	   ╚████╔╝ ██║ ╚████╔╝ ██║  ██║    ██║ ╚═╝ ██║╚██████╔╝██║  ██║╚██████╗██║██║  ██║
	    ╚═══╝  ╚═╝  ╚═══╝  ╚═╝  ╚═╝    ╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═╝ ╚═════╝╚═╝╚═╝  ╚═╝

  	           PID: 0000			             By: las chorizo
  	⊱ ──────────────────────────────── {.⋅ ✯ ⋅.} ───────────────────────────────── ⊰
  
  ```
# Minitalk
> This repository contains a "Minitalk" project that is part of the École 42 curriculum.

Create a communication program in the form of a client and server. The server must be launched first, and after being launched it must display its PID. The client must communicate the string passed as a parameter to the server. Once the string has been received, the server must display it. Communication between your programs should ONLY be done using UNIX signals.

The client will take as parameters:

The server PID.
The string that should be sent.
Only SIGUSR1 and SIGUSR2 can be used.

## Bonus

- The server confirms every signal received by sending a signal to the client.
- Support Unicode characters!

## Usage
1️⃣ ```make```

2️⃣ Open a terminal and execute ```./server```

3️⃣ Open a new terminal and execute ```./client <server PID> <"The message you want to send to the server">```

4️⃣ Ctr + z to stop the program
