# Minitalk

Create a communication program in the form of a client and server. The server must be launched first, and after being launched it must display its PID. The client must communicate the string passed as a parameter to the server. Once the string has been received, the server must display it. Communication between your programs should ONLY be done using UNIX signals.

The client will take as parameters:

The server PID.
The string that should be sent.
Only SIGUSR1 and SIGUSR2 can be used.

# Bonus

- The server confirms every signal received by sending a signal to the client. (Not implemented)
- Support Unicode characters!
