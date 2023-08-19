def ceaser(key,message):
    encrypted=""
    decrypted=""
    message=message.upper()
    for letter in message:
        numeric=ord(letter)-ord('A')
        numeric=(numeric+key)%26
        letter=chr(numeric+ord('A'))
        encrypted+=letter
        
    print(encrypted)
    for letter in encrypted:
        numeric=ord(letter)-ord('A')
        numeric=(numeric-key)%26
        letter=chr(numeric+ord('A'))
        decrypted+=letter
    print(decrypted)
    
ceaser(5,"netra Bahadur bista")
    