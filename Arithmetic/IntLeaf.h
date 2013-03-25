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

	/** Addition assignment
	  * Takes the IntLeaf and adds the input to the object.
	  * \param[in] leaf The IntLeaf containing the number to add.
	  * \return A reference to the IntLeaf object itself.
	  */
    IntLeaf &addTo(const IntLeaf &leaf);

	/** Addition assignment operator
	  * Takes the IntLeaf and adds the input to the object.
	  * \param[in] leaf The IntLeaf containing the number to add.
	  * \return A reference to the IntLeaf object itself.
	  */
	IntLeaf &operator+=(const IntLeaf &leaf);

	/** Addition
	  * Takes the IntLeaf, adds the input and returns the result.
	  * \param[in] leaf The IntLeaf containing the number to add.
	  * \return The result when adding the input to the IntLeaf object.
	  */
    IntLeaf add(const IntLeaf &leaf) const;

	/** Addition operator
	  * Takes the IntLeaf, adds the input and returns the result.
	  * \param[in] leaf The IntLeaf containing the number to add.
	  * \return The result when adding the input to the IntLeaf object.
	  */
    IntLeaf operator+(const IntLeaf &leaf) const;
    
	/** Multiply to
	  * Takes the IntLeaf and multiplies it with the input.
	  * \param[in] leaf The IntLeaf containing the number to multiply with.
	  * \return A reference to the IntLeaf object itself.
	  */
    IntLeaf &multTo(const IntLeaf &leaf);

	/** Multiply to operator
	  * Takes the IntLeaf and multiplies it with the input.
	  * \param[in] leaf The IntLeaf containing the number to multiply with.
	  * \return A reference to the IntLeaf object itself.
	  */
	IntLeaf &operator*=(const IntLeaf &leaf);

	/** Multiplication
	  * Takes the IntLeaf, multiplies with the input and returns the result.
	  * \param[in] leaf The IntLeaf containing the number to multiply with.
	  * \return The result when multiplying with the input to the IntLeaf object.
	  */
    IntLeaf mult(const IntLeaf &leaf) const;

	/** Multiplication operator
	  * Takes the IntLeaf, multiplies with the input and returns the result.
	  * \param[in] leaf The IntLeaf containing the number to multiply with.
	  * \return The result when multiplying with the input to the IntLeaf object.
	  */
    IntLeaf operator*(const IntLeaf &leaf) const;
    
	/** Multiplication assignment modulo
	  * Takes the IntLeaf, multiplies with the input and assigns the new result taken modulo.
	  * \param[in] leaf The IntLeaf containing the number to multiply with.
	  * \param[in] mod The IntLeaf containing the number to take modulo with.
	  * \return A reference to the IntLeaf object itself.
	  */
    IntLeaf &multToMod(const IntLeaf &leaf, const IntLeaf &mod);

	/** Multiplication modulo
	  * Takes the IntLeaf, multiplies with the input and returns the new result taken modulo.
	  * \param[in] leaf The IntLeaf containing the number to multiply with.
	  * \param[in] mod The IntLeaf containing the number to take modulo with.
	  * \return An IntLeaf containing the result of the opreation.
	  */
    IntLeaf multMod(const IntLeaf &leaf, const IntLeaf &mod) const;
    
	/** Addition assignment modulo
	  * Takes the IntLeaf and adds the input to the object modulo mod.
	  * \param[in] leaf The IntLeaf containing the number to add.
	  * \param[in] mod The IntLeaf containing the number to take modulo with.
	  * \return A reference to the IntLeaf object itself.
	  */
    IntLeaf &addToMod(const IntLeaf &leaf, const IntLeaf &mod);

	/** Addition modulo
	  * Takes the IntLeaf, adds the input and returns the result modulo mod.
	  * \param[in] leaf The IntLeaf containing the number to add.
	  * \param[in] mod The IntLeaf containing the number to take modulo with.
	  * \return The result when adding the input to the IntLeaf object.
	  */
    IntLeaf addMod(const IntLeaf &leaf, const IntLeaf &mod) const;

	/** Exponentiation assignment
	  * Takes the IntLeaf, raises it to the exponent and assigns the result.
	  * \param[in] exponent The expontent to which we raise the IntLeaf.
	  * \return A reference to the IntLeaf object itself.
	  */
    IntLeaf &expTo(unsigned long exponent);

	/** Exponentiation
	  * Takes the IntLeaf, raises it to the exponent and returns the result.
	  * \param[in] exponent The expontent to which we raise the IntLeaf.
	  * \return The result when rising the IntLeaf to the exponent.
	  */
    IntLeaf exp(unsigned long exponent) const;
    
	/** Exponentiation assignment modulo
	  * Takes the IntLeaf, raises it to the exponent and assigns the result modulo mod.
	  * \param[in] exponent The expontent to which we raise the IntLeaf.
	  * \param[in] mod The IntLeaf containing the number to take modulo with.
	  * \return A reference to the IntLeaf object itself.
	  */
    IntLeaf &expToMod(const IntLeaf &leaf, const IntLeaf &mod);

	/** Exponentiation modulo
	  * Takes the IntLeaf, raises it to the exponent and returns the result modulo mod.
	  * \param[in] exponent The expontent to which we raise the IntLeaf.
	  * \param[in] mod The IntLeaf containing the number to take modulo with.
	  * \return The result when rising the IntLeaf to the exponent.
	  */
    IntLeaf expMod(const IntLeaf &leaf, const IntLeaf &mod) const;
    
    bool operator==(const IntLeaf &leaf) const;
    bool operator!=(const IntLeaf &leaf) const;

    bool operator<(const IntLeaf &leaf) const;
    bool operator>(const IntLeaf &leaf) const;

    IntLeaf operator-(void) const;
    IntLeaf inverse(const IntLeaf &mod) const;

    mpz_class getBigInt(void) const;
    std::string toString(void) const;

	virtual bytevector toVector(void) const;
    virtual int32_t getLength(void) const;
private:
    mpz_class data;
    uint32_t length;
};

