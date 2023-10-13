#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstring>

class SHA512 {
public:
    SHA512(const std::string& input) : input_string(input) {
    }

    std::string calculate() {
        uint64_t message[80];
        std::string padded_message = padMessage();
        size_t numBlocks = padded_message.size() / 128;

        uint64_t H[8] = {
            0x6a09e667f3bcc908, 0xbb67ae8584caa73b,
            0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
            0x510e527fade682d1, 0x9b05688c2b3e6c1f,
            0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
        };

        for (size_t block = 0; block < numBlocks; ++block) {
            const char* blockStart = padded_message.c_str() + block * 128;
            for (int i = 0; i < 16; ++i) {
                message[i] = bytesToUInt64(blockStart + i * 8);
            }

            for (int i = 16; i < 80; ++i) {
                uint64_t s0 = rightRotate(message[i - 15], 1) ^ rightRotate(message[i - 15], 8) ^ (message[i - 15] >> 7);
                uint64_t s1 = rightRotate(message[i - 2], 19) ^ rightRotate(message[i - 2], 61) ^ (message[i - 2] >> 6);
                message[i] = message[i - 16] + s0 + message[i - 7] + s1;
            }

            uint64_t a = H[0];
            uint64_t b = H[1];
            uint64_t c = H[2];
            uint64_t d = H[3];
            uint64_t e = H[4];
            uint64_t f = H[5];
            uint64_t g = H[6];
            uint64_t h = H[7];

            for (int i = 0; i < 80; ++i) {
                uint64_t S1 = rightRotate(e, 14) ^ rightRotate(e, 18) ^ rightRotate(e, 41);
                uint64_t ch = (e & f) ^ ((~e) & g);
                uint64_t temp1 = h + S1 + ch + k[i] + message[i];
                uint64_t S0 = rightRotate(a, 28) ^ rightRotate(a, 34) ^ rightRotate(a, 39);
                uint64_t maj = (a & b) ^ (a & c) ^ (b & c);
                uint64_t temp2 = S0 + maj;

                h = g;
                g = f;
                f = e;
                e = d + temp1;
                d = c;
                c = b;
                b = a;
                a = temp1 + temp2;
            }

            H[0] += a;
            H[1] += b;
            H[2] += c;
            H[3] += d;
            H[4] += e;
            H[5] += f;
            H[6] += g;
            H[7] += h;
        }

        std::stringstream hashStream;
        for (int i = 0; i < 8; ++i) {
            hashStream << std::setfill('0') << std::setw(16) << std::hex << H[i];
        }

        return hashStream.str();
    }

private:
    std::string input_string;
    const uint64_t k[80] = {
        0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
        0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
        0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
        0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
        0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
        0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
        0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
        0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
        0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
        0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
        0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
        0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
        0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34c7dc3d5ffbb4b6,
        0x534b00e19b5a820e, 0x550c7dc3d5ffb4e2, 0x586e04bf1a7a0b0e, 0x61372b9f5f53c2f7,
        0x695550c84edf4736, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72,
        0x8cc702081a6439ec, 0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
        0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e,
        0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae,
        0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
        0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec,
        0x6c44198c4a475817
    };

    std::string padMessage() {
        uint64_t originalLength = input_string.length() * 8;
        uint64_t appendLength = 128 - (originalLength + 1) % 128;
        if (appendLength < 16) {
            appendLength += 128;
        }
        uint64_t newLength = originalLength + appendLength + 64;
        std::string padded_message(newLength / 8, 0);

       
        std::memcpy(&padded_message[0], input_string.c_str(), input_string.length());

        
        padded_message[input_string.length()] = 0x80;

        
        for (int i = 0; i < 8; ++i) {
            padded_message[newLength / 8 - 1 - i] = (originalLength >> (i * 8)) & 0xFF;
        }

        return padded_message;
    }

    uint64_t rightRotate(uint64_t value, int shift) {
        return (value >> shift) | (value << (64 - shift));
    }

    uint64_t bytesToUInt64(const char* bytes) {
        uint64_t result = 0;
        for (int i = 0; i < 8; ++i) {
            result = (result << 8) | (static_cast<uint64_t>(bytes[i]) & 0xFF);
        }
        return result;
    }
};

int main() {
    std::string input_string = "Hello, World!";
    
    SHA512 sha512_calculator(input_string);
    std::string hashed_string = sha512_calculator.calculate();

    std::cout << "SHA-512 Hash: " << hashed_string << std::endl;

    return 0;
}
Description:
SHA-512 (Secure Hash Algorithm 512-bit) is a cryptographic hash function that belongs to the SHA-2 family. It takes an input message and produces a fixed-size (512-bit or 64-byte) hash value, which is typically represented as a hexadecimal string. The SHA-512 algorithm works through the following steps:

Message Padding: The input message is first padded to a length that is a multiple of 1024 bits (or 128 bytes). The padding includes adding a single '1' bit, followed by '0' bits, and then appending the original message length in binary representation as a 128-bit integer.

Initialization: SHA-512 uses eight 64-bit words (A, B, C, D, E, F, G, H) as initial values for hashing. These values are derived from the first 64 bits of the fractional parts of the square roots of the first eight prime numbers (2, 3, 5, 7, 11, 13, 17, 19).

Message Block Processing: The padded message is divided into 1024-bit (128-byte) blocks. For each block, the algorithm performs the following operations:

a. Message Expansion: The 1024-bit block is divided into 80 64-bit words. The first 16 words are derived directly from the block. The remaining 64 words are derived through a series of bitwise operations.

b. Compression Function: The compression function operates on the 80 words from the message expansion, and it goes through 80 rounds. In each round, the algorithm updates the eight 64-bit working variables (A, B, C, D, E, F, G, H) based on these steps:

Sigma Functions: SHA-512 uses four different "sigma" functions, each applied to different parts of the working variables. These functions involve bit rotations and bitwise operations.
Maj Function: The "maj" function performs a majority selection operation on three of the working variables.
Ch Function: The "ch" function performs a choice operation using two of the working variables.
c. Update Hash Values: After all 80 rounds, the eight working variables (A, B, C, D, E, F, G, H) are used to update the hash values (H0, H1, H2, H3, H4, H5, H6, H7) by addition modulo 2^64.

Final Output: After processing all blocks, the resulting hash value is a 512-bit message digest. It is typically represented as a hexadecimal string, with each byte (8 bits) represented as two hexadecimal characters.

SHA-512 is designed to be a secure and cryptographically strong hash function. It exhibits properties such as pre-image resistance, second pre-image resistance, and collision resistance, which make it suitable for various cryptographic applications, including data integrity verification and digital signatures. It is widely used in security protocols and applications to ensure the integrity and authenticity of data.


SHA512 Class:
The SHA512 class is the central component of this code. It implements the SHA-512 hashing algorithm.

SHA512(const std::string& input): This is the constructor of the SHA512 class. It takes a single argument, which is the input string that you want to hash. The constructor initializes an instance of the SHA512 class with the provided input.

std::string calculate(): This member function is responsible for performing the SHA-512 hash calculation. It takes the input string provided in the constructor and returns the resulting hash as a hexadecimal string.

std::string input_string: This is a private member variable that stores the input string. It is used to hold the input data that needs to be hashed.

const uint64_t k[80]: This is another private member variable, and it contains an array of 80 constant values that are used in the SHA-512 algorithm. These constants are used during the message block processing to ensure the hash's unpredictability and security.

std::string padMessage(): This is a private member function within the SHA512 class. Its main purpose is to pad the input message according to the SHA-512 padding rules. Padding is necessary to ensure that the input message has a length that is a multiple of 1024 bits (128 bytes). The padding involves adding a single '1' bit, followed by '0' bits, and then appending the original message's length in binary representation as a 128-bit integer.

uint64_t rightRotate(uint64_t value, int shift): This private member function performs a right rotation operation on a 64-bit value. Right rotation is a bitwise operation that shifts the bits to the right by a specified number of positions while wrapping the bits that are shifted out back to the beginning.

uint64_t bytesToUInt64(const char* bytes): This private member function converts an array of 8 bytes to a single 64-bit integer. It does this by combining the bytes into a 64-bit integer using bitwise operations.

main Function:
The main function is the entry point of the program and demonstrates how to use the SHA512 class to calculate the SHA-512 hash of an input string.

std::string input_string: This string variable contains the message you want to hash. You can change its value to hash a different message. In this code, the input message is set to "Hello, World!" for demonstration.

SHA512 sha512_calculator(input_string): Here, an instance of the SHA512 class is created, taking the input_string as an argument. This instance represents the SHA-512 hash calculator.

std::string hashed_string = sha512_calculator.calculate(): This line calls the calculate function of the SHA512 class to compute the SHA-512 hash of the input string. The resulting hash is then stored in the hashed_string variable.

std::cout << "SHA-512 Hash: " << hashed_string << std::endl;: Finally, this line prints the calculated SHA-512 hash to the console, displaying the message "SHA-512 Hash:" followed by the hash value.

In summary, the provided code defines a SHA512 class that encapsulates the SHA-512 hashing algorithm and provides methods to perform the hashing. The main function demonstrates how to use the class to hash an input string and print the result. This code follows the principles of object-oriented programming (OOP) by encapsulating the algorithm within a class, making it modular and reusable for hashing different messages.

