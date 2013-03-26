# Compiler
CC=g++

# Set path to google test library... TODO: se till att detta ej behövs
PATH_TO_GTEST_LIB = ../../gtest-1.6.0/lib/.libs

# Linker flags
LDFLAGS= -lgmp -lcrypto -lssl $(PATH_TO_GTEST_LIB)/libgtest.a #-lgtest

# Options to compiler.
CFLAGS= -Wall -I../Arithmetic -I../Crypto -I../Verifier -I../../gtest-1.6.0/include/

INC_DIR = ../Output

VERIFIER_OBJ = DecryptionFactorsVerifier.o DecryptionVerifier.o KeyVerifier.o ProofOfShuffle.o ShufflingVerifier.o Utilities.o Verifier.o

VERIFIER_LINKS = $(addprefix $(INC_DIR)/Verifiers/,$(VERIFIER_OBJ))

LINKS = $(INC_DIR)/Arithmetic/libarithm.a $(INC_DIR)/Crypto/libcrypt.a $(VERIFIER_LINKS)

TEST_OBJS = ByteTreeTests.o IntLeafArithmeticsTests.o NodeArithmeticsTests.o NodeDataInitTests.o UtilitiesTests.o PRGTests.o ROTests.o

all: $(TEST_OBJS) $(LINKS) TestRunner.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(LINKS) $(TEST_OBJS)  TestRunner.o -o run

ByteTreeTests: $(LINKS) $(VERIFIER_LINKS) ByteTreeTests.o TestRunner.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(LINKS) ByteTreeTests.o TestRunner.o -o run

IntLeafArithmeticsTests: $(LINKS) $(VERIFIER_LINKS) IntLeafArithmeticsTests.o TestRunner.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(LINKS) IntLeafArithmeticsTests.o TestRunner.o -o run

NodeArithmeticsTests: $(LINKS) $(VERIFIER_LINKS) NodeArithmeticsTests.o TestRunner.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(LINKS) NodeArithmeticsTests.o TestRunner.o -o run

NodeDataInitTests: $(LINKS) $(VERIFIER_LINKS) NodeDataInitTests.o TestRunner.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(LINKS) NodeDataInitTests.o TestRunner.o -o run

UtilitiesTests: $(LINKS) $(VERIFIER_LINKS) UtilitiesTests.o TestRunner.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(LINKS) UtilitiesTests.o TestRunner.o -o run

PRGTests: $(LINKS) $(VERIFIER_LINKS) PRGTests.o TestRunner.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(LINKS) PRGTests.o TestRunner.o -o run

ROTests: $(LINKS) $(VERIFIER_LINKS) ROTests.o TestRunner.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(LINKS) ROTests.o TestRunner.o -o run

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@


../makefile: 
