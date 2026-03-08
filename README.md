# OSI-Model
OSI Model animation in graphics.h

I wrote this animation to create a visual representation of the message encapsulation and decapsulation as the message travels through the OSI layers.

The center (purple) box is the message. As the message moves down the OSI stack, every layer wraps the data with it's own information (protocol headers and trailers). 

So on the sender's end, this is what happens at each layer : 
-------------
Layer | What Happens |
Application Layer| Message is created |
Presentation Layer | Formatting/encoding information is added |
Session Layer | Session control information is added |
Transport Layer | TCP/UDP headers are added |
Network Layer | IP header is added |
Data Link Layer | Frame header + trailer is added |
Physical Layer | The bits are sent on wire | 
