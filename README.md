sa104x-kexjobb
==============

Implementation of a verifier for the Verificatum Mix-net

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
