"BSON" stands for "binary JSON" - a binary storage format that is JSON inspired
(and adds a couple extra types such as Date).

This is the C++ implementation.  Implementations which translate BSON<->JSON
are available for most languages at bsonspec.org.


The build system here uses autotools, though indirectly. It is a bit
unconventional, but all you have to do is run make in the top level. Autotools
magic happens within build/.