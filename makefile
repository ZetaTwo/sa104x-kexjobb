# Compiler
CC=g++

# Linker flags
LDFLAGS=-lgmp -gmpxx -lssl -lcrypto

# Options to compiler.
CFLAGS=-c -IArithmetic -ICrypto -IVerifier

#Archiver to make static library
AR=ar rcs

OUT_DIR=Output

ARITHMETIC_OBJ = BaseLeaf.o BaseNode.o DataLeaf.o IntLeaf.o Node.o
CRYPTO_OBJ = ElGamal.o H_SHA.o PRG.o RO.o RandomArray.o
VERIFIER_OBJ = DecryptionFactorsVerifier.o DecryptionVerifier.o KeyVerifier.o ProofOfShuffle.o ShufflingVerifier.o Utilities.o Verifier.o main.o

OUT_ARITHMETIC_OBJ = $(addprefix $(OUT_DIR)/Arithmetic/,$(ARITHMETIC_OBJ))
OUT_CRYPTO_OBJ = $(addprefix $(OUT_DIR)/Crypto/,$(CRYPTO_OBJ))
OUT_VERIFIER_OBJ = $(addprefix $(OUT_DIR)/Verifiers/,$(VERIFIER_OBJ))

all: arithmetic crypto verifiers

arithmetic: $(OUT_ARITHMETIC_OBJ)
	$(AR) $(OUT_DIR)/Arithmetic/libarithm.a $(OUT_ARITHMETIC_OBJ)

crypto: $(OUT_CRYPTO_OBJ) arithmetic
	$(AR) $(OUT_DIR)/Crypto/libcrypt.a $(OUT_CRYPTO_OBJ)

verifiers: $(OUT_VERIFIER_OBJ) arithmetic crypto
	$(CC) $(LDFLAGS) $(OUT_VERIFIER_OBJ) $(OUT_DIR)/Arithmetic/libarithm.a $(OUT_DIR)/Crypto/libcrypt.a -o $(OUT_DIR)/verifier


$(OUT_DIR)/Arithmetic/%.o: Arithmetic/%.cpp
	$(CC) $(CFLAGS) $< -o $@

$(OUT_DIR)/Crypto/%.o: Crypto/%.cpp
	$(CC) $(CFLAGS) $< -o $@

$(OUT_DIR)/Verifiers/%.o: Verifier/%.cpp
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -rf $(OUT_ARITHMETIC_OBJ) $(OUT_CRYPTO_OBJ) $(OUT_VERIFIER_OBJ) $(OUT_DIR)/Arithmetic/libarithm.a $(OUT_DIR)/Crypto/libcrypt.a
	rmdir $(OUT_DIR)/Arithmetic $(OUT_DIR)/Crypto $(OUT_DIR)/Verifiers



$(shell   mkdir -p $(OUT_DIR) $(OUT_DIR)/Arithmetic $(OUT_DIR)/Crypto $(OUT_DIR)/Verifiers)
