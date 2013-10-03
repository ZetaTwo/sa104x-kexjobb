SA104X - Bachelor Project in Computer Science
==============

Implementation of a verifier for the Verificatum Mix-net. This was created as a part of our bchelor project at [KTH](http://www.kth.se). All material will be kept here for future reference.

Requirements
------------

* OpenSSL
* GMP
* RapidXML (http://rapidxml.sourceforge.net/)

Compilation
-----------

### Quick ###
Compile with make or VS.
Binary is placed in Output/verifier

### Detailed ###
The contents of the Verifier directory depends on RapidXML, the contents of Crypto and Arithmetic.
The contents of Crypto depends on Arthimetic and OpenSSL
The contents of Arithmetic depends on GMP.

Compilation order: Arithmetic, Crypto, Verifier
