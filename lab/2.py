import numpy as np

def name_to_numbers(name, mapping):
    return [mapping[char] for char in name]

def numbers_to_name(numbers, mapping):
    return ''.join([mapping[num] for num in numbers])

def matrix_mod_inverse(matrix, modulus):
    # Compute the inverse of the matrix modulo modulus
    det = np.linalg.det(matrix)
    det_inverse = pow(int(det), -1, modulus)  # Modular multiplicative inverse of the determinant

    # Calculate the adjugate matrix and multiply by the determinant inverse
    adjugate = det_inverse * np.linalg.inv(matrix) * det
    return adjugate.astype(int) % modulus

def find_valid_key():
    # Iterate through possible key matrices until finding a valid one
    for a in range(1, 26):
        for b in range(1, 26):
            for c in range(1, 26):
                for d in range(1, 26):
                    key = np.array([[a, b],
                                    [c, d]])
                    det = (a * d - b * c) % 26
                    if det % 2 != 0 and det % 13 != 0:
                        return key
    raise ValueError("No valid key found.")

def hill_cipher(message, key, operation):
    mapping = {chr(i + 65): i for i in range(26)}  # Mapping A->0, B->1, ..., Z->25

    # Convert the message to uppercase and remove spaces
    message = message.upper().replace(" ", "")

    # Check if the length of the message is divisible by 2, if not, pad with 'X'
    if len(message) % 2 != 0:
        message += 'X'

    # Convert the name to numbers using the mapping
    numbers = name_to_numbers(message, mapping)

    # Split the numbers into pairs and create the matrix
    matrix = np.array([numbers[i:i+2] for i in range(0, len(numbers), 2)])

    # Perform encryption or decryption based on the operation
    if operation == "encrypt":
        result_matrix = (matrix @ key) % 26
    elif operation == "decrypt":
        key_inverse = matrix_mod_inverse(key, 26)
        result_matrix = (matrix @ key_inverse) % 26
    else:
        raise ValueError("Invalid operation. Use 'encrypt' or 'decrypt'.")

    # Flatten the result matrix and convert back to name using the mapping
    result_numbers = result_matrix.flatten()
    result_name = numbers_to_name(result_numbers, {v: k for k, v in mapping.items()})
    
    return result_name

if __name__ == "__main__":
    # Get the user's full name
    full_name = input("Enter your full name: ")

    # Find a suitable valid key matrix
    key = find_valid_key()

    # Perform encryption
    encrypted_name = hill_cipher(full_name, key, "encrypt")
    print(f"Encrypted name: {encrypted_name}")

    # Perform decryption using the same encrypted text
    decrypted_name = hill_cipher(encrypted_name, key, "decrypt")
    print(f"Decrypted name: {decrypted_name}")
