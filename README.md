# bson-cpp

## The standalone BSON C++ implementation.

"BSON" stands for "binary JSON" - a binary storage format that is JSON inspired.

This is the C++ implementation, developed by [http://www.10gen.com/](10gen) for
[http://www.mongodb.org/](mongodb). This distribution merely rips it out of the
mongodb repository into its own.

Other BSON implementations are available for most languages at
http://bsonspec.org.

## Status: beta

Note that this is not yet ready for production. While all the majority of the code has been thoroughly tested in the mongodb distribution, this fork is not yet proved stable.

## Building

The build system here uses autotools. It is a bit unconventional: it hides all
the autotools magic inside of build/, so all you have to do is:

    make

=)

The top level Makefile will call configure and the generated Makefile (inside
build/). The product is build/libbsoncpp.la. You can then link against it.

## Installing

To install the library and headers in /usr/local, just run:

    make install

## Usage

You want to link against the library, and then:

    #include <bson/bson.h>

Check out the headers, particularly bson.h. The project is not fully well setup
though, so you may have to include other headers for now.

## License

I am not quite sure what BSON's license is. I'll check with 10gen. mongodb
carries both an Apache and a GNU-AGPL license (included in this dist).

