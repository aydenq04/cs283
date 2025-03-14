1. How does the remote client determine when a command's output is fully received from the server, and what techniques can be used to handle partial reads or ensure complete message transmission?

The remote client determine when a command's output is fully received by waiting for a newline character to be read. Since each command input into the client ends with a newline the client will always be able to read a newline character at the end of the command line. Other ways to do this would be to wait for a null terminating character.

2. This week's lecture on TCP explains that it is a reliable stream protocol rather than a message-oriented one. Since TCP does not preserve message boundaries, how should a networked shell protocol define and detect the beginning and end of a command sent over a TCP connection? What challenges arise if this is not handled correctly?

One way that the shell could detect the end of a command is by waiting for a newline or null terminating character before executing the command. If not handled correctly the shell to attempt to execute an incomplete command or multiple commands could be read in a single packet.

3. Describe the general differences between stateful and stateless protocols.

A stateful protocol maintains session information about the client across multiple requests. Meaning the server keeps track of previous interactions allowing for more continuous communication. A stateless protocol does not maintain session information and each request is treated independently with no knowledge of previous interactions.

4. Our lecture this week stated that UDP is "unreliable". If that is the case, why would we ever use it?

Even though UDP is considered unreliable it is still used commonly due to it's speed, efficiency, and suitability for certain applications.

5. What interface/abstraction is provided by the operating system to enable applications to use network communications?

The operating system provides the socket API for applications to use network communication. Sockets allow applications to send/receive using standard protocols like TCP and UDP.