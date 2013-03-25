#pragma once
#include "BaseLeaf.h"

#include <gmp.h>
#include <gmpxx.h>

#include <string>
#include <fstream>

class IntLeaf :
    public BaseLeaf
{
public:
    static const int ARRAYORDER = 1; /**< Defines the endianess of whole arrays in the program. */
    static const int ENDIAN = 0; /**< Defines the endianess of each byte in the program. */
    static const int NAILS = 0; /**< GMP related define (TODO). */

	/** The default constructor.
	  */
    IntLeaf(void);

	/** Copy constructor
	  * \param[in] leaf The IntLeaf to copy.
	  */
    IntLeaf(const IntLeaf &leaf);

	/** Create an IntLeaf from a GMP mpz_class object. 
	  * \param[in] bigint The GMP object to copy.
	  */
    explicit IntLeaf(const mpz_class &bigint);

	/** Create an IntLeaf from an integer.
	  * \param[in] input The integer to create an IntLeaf from.
	  */
    IntLeaf(long int input);

	/** Create an IntLeaf from an integer with fixed length.
	  * \param[in] input The value of the IntLeaf object to create.
	  * \param[in] length The number of bytes this IntLeaf will occupy.
	  */
    IntLeaf(long int input, long int length);

	/** Create an IntLeaf from a decimal string.
	  * \param[in] input The string containing the number which we create the IntLeaf from.
	  */
    explicit IntLeaf(std::string input);
    
	/** Create an IntLeaf from a vector of bytes.
	  * \param[in] bytevec The data from which the IntLeaf is created.
	  */
	explicit IntLeaf(bytevector bytevec);
    
	/** Create an IntLeaf from a stream.
	  * \param[in] file The stream containing the data from which the IntLeaf is created.
	  */
	explicit IntLeaf(std::istream &file);
    ~IntLeaf(void);

	/** Create the IntLeaf data from a stream.
	  * Reads a number of bytes from the stream as specified and creates the IntLeaf data.
	  * \param[in] file The stream containing the data from which the IntLeaf is created.
	  * \param[in] length The number of bytes to read from the stream.
	  */
    static BaseNode *constructPartFromFile(std::istream &file, uint32_t length);

	/** Assignment operator.
	  * Assigns the input number to the IntLeaf
	  * \param[in] leaf The IntLeaf containing the input number.
	  * \return A reference to the IntLeaf object itself.
	  */
    IntLeaf &operator=(const IntLeaf &leaf);

	/** Assignment operator.
	  * Assigns the input number to the IntLeaf
	  * \param[in] input The integer containing the input number.
	  * \return A reference to the IntLeaf object itself.
	  */
    IntLeaf &operator=(long int input);

	/** Assignment operator.
	  * Assigns the the number in the decimal string input to the IntLeaf
	  * \param[in] input The decimal string containing the input number.
	  * \return A reference to the IntLeaf object itself.
	  */
    IntLeaf &operator=(std::string input);	
    
	/** Modulo assignment.
	  * Takes the IntLeaf modulo the input and assigns the result to the IntLeaf.
	  * \param[in] leaf The IntLeaf containing the modulo.
	  * \return A reference to the IntLeaf object itself.
	  */
    IntLeaf &modTo(const IntLeaf &leaf);

	/** Modulo assignment.
	  * Takes the IntLeaf modulo the input and returns the result.
	  * \param[in] leaf The IntLeaf containing the modulo.
	  * \return The resulting IntLeaf when taking modulo the input.
	  */
    IntLeaf mod(const IntLeaf &leaf) const;

    IntLeaf &addTo(const IntLeaf &leaf);
    IntLeaf add(const IntLeaf &leaf) const;
	IntLeaf &operator+=(const IntLeaf &leaf);
    IntLeaf operator+(const IntLeaf &leaf) const;
    
    IntLeaf &multTo(const IntLeaf &leaf);
    IntLeaf mult(const IntLeaf &leaf) const;
	IntLeaf &operator*=(const IntLeaf &leaf);
    IntLeaf operator*(const IntLeaf &leaf) const;
    
    IntLeaf &multToMod(const IntLeaf &leaf, const IntLeaf &mod);
    IntLeaf multMod(const IntLeaf &leaf, const IntLeaf &mod) const;
    
    IntLeaf &addToMod(const IntLeaf &leaf, const IntLeaf &mod);
    IntLeaf addMod(const IntLeaf &leaf, const IntLeaf &mod) const;

    IntLeaf &expTo(unsigned long exponent);
    IntLeaf exp(unsigned long exponent) const;
    
    IntLeaf &expToMod(const IntLeaf &leaf, const IntLeaf &mod);
    IntLeaf expMod(const IntLeaf &leaf, const IntLeaf &mod) const;
    
    bool operator==(const IntLeaf &leaf) const;
    bool operator!=(const IntLeaf &leaf) const;

    bool operator<(const IntLeaf &leaf) const;
    bool operator>(const IntLeaf &leaf) const;

    IntLeaf operator-(void) const;
    
    IntLeaf inverse(const IntLeaf &mod) const;

    mpz_class getBigInt(void) const;
    virtual bytevector toVector(void) const;
    virtual int32_t getLength(void) const;
    
    std::string toString(void) const;
	
private:
    mpz_class data;
    uint32_t length;
};

