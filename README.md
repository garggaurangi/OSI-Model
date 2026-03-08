# OSI-Model

I wrote this animation in C++ using graphics.h library to create a visual representation of the message encapsulation and decapsulation as the message travels through the OSI layers.

The center (purple) box is the message. As the message moves down the OSI stack, every layer wraps the data (encapsulation) with it's own information (protocol headers and trailers). 

## At the Sender's end: Encapsulation

The growing boxes in the animation represents encapsulation of data.

This is what happens at each layer : 

| Layer | What Happens |
|------|-----------|
| Application Layer| Message is created |
| Presentation Layer | Formatting/encoding information is added |
| Session Layer | Session control information is added |
| Transport Layer | TCP/UDP headers are added |
| Network Layer | IP header is added |
| Data Link Layer | Frame header + trailer is added |
| Physical Layer | The bits are sent on wire | 

## At the Receiever's end: Decapsulation

Each layer removes it's headers until the application receives the original message.

Enjoy the animation!

