extra_letter_pos = []


def generate_playfair_matrix(key):
    key = key.replace("J", "I")  # Replace J with I
    key += "ABCDEFGHIKLMNOPQRSTUVWXYZ"

    matrix = [[0] * 5 for _ in range(5)]
    used_letters = set()

    row = 0
    col = 0

    for letter in key:
        if letter not in used_letters:
            matrix[row][col] = letter
            used_letters.add(letter)
            col += 1
            if col == 5:
                col = 0
                row += 1
                if row == 5:
                    break

    return matrix


def find_letter(matrix, letter):
    for i in range(5):
        for j in range(5):
            if matrix[i][j] == letter:
                return i, j


def playfair_encrypt(plaintext, key):
    matrix = generate_playfair_matrix(key)
    plaintext = plaintext.replace("J", "I")
    print(matrix)

    # Add filler 'X' for repeated letters and make pairs
    pairs = []
    i = 0
    while i < len(plaintext):
        if i == len(plaintext) - 1 or plaintext[i] == plaintext[i + 1]:
            pairs.append(plaintext[i] + "X")
            i += 1
            extra_letter_pos.append(i)
        else:
            pairs.append(plaintext[i] + plaintext[i + 1])
            i += 2

    ciphertext = ""

    for pair in pairs:
        row1, col1 = find_letter(matrix, pair[0])
        row2, col2 = find_letter(matrix, pair[1])

        if row1 == row2:
            ciphertext += matrix[row1][(col1 + 1) % 5]
            ciphertext += matrix[row2][(col2 + 1) % 5]
        elif col1 == col2:
            ciphertext += matrix[(row1 + 1) % 5][col1]
            ciphertext += matrix[(row2 + 1) % 5][col2]
        else:
            ciphertext += matrix[row1][col2]
            ciphertext += matrix[row2][col1]

    return ciphertext


def playfair_decrypt(ciphertext, key):
    matrix = generate_playfair_matrix(key)
    ciphertext = ciphertext.replace(" ", "").upper()

    plaintext = ""

    for i in range(0, len(ciphertext), 2):
        row1, col1 = find_letter(matrix, ciphertext[i])
        row2, col2 = find_letter(matrix, ciphertext[i + 1])

        if row1 == row2:
            plaintext += matrix[row1][(col1 - 1) % 5]
            plaintext += matrix[row2][(col2 - 1) % 5]
        elif col1 == col2:
            plaintext += matrix[(row1 - 1) % 5][col1]
            plaintext += matrix[(row2 - 1) % 5][col2]
        else:
            plaintext += matrix[row1][col2]
            plaintext += matrix[row2][col1]

    return plaintext


# Main program
plaintext = input("Enter the plain text: ").replace(" ", "").upper()
key = input("Enter the key: ").replace(" ", "").upper()

encrypted_name = playfair_encrypt(plaintext, key)
print("Encrypted:", encrypted_name)

decrypted_name = playfair_decrypt(encrypted_name, key)
print("Decrypted: ", end="")

for char in decrypted_name:
    if decrypted_name.index(char) in extra_letter_pos:
        continue
    print(char, end="")
