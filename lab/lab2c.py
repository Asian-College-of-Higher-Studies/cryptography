parity_drop=[57, 49, 41, 33, 25, 17,  9,  1,
             58, 50, 42, 34, 26, 18, 10,  2,
             59, 51, 43, 35, 27, 19, 11,  3,
             60, 52, 44, 36, 63, 55, 47, 39,
             31, 23, 15,  7, 62, 54, 46, 38,
             30, 22, 14,  6, 61, 53, 45, 37,
             29, 21, 13,  5, 28, 20, 12,  4]
compression = [
    14, 17, 11, 24,  1,  5,
     3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
]
round=1
def des(data,paritydrop,compress,round):
    result=""
    for i in paritydrop:
        result+=data[i-1]
    first_28=result[:28]
    second_28=result[28:]
    while(round<=16):
        if(round==1 or round==2 or round==9 or round==16):
            first_28=first_28[1:]+first_28[:1]
            second_28=second_28[1:]+second_28[:1]
        else:
            first_28=first_28[2:]+first_28[:2]
            second_28=second_28[2:]+second_28[:2]
        result=""
        total_56=first_28+second_28
        for i in compress:
            result+=total_56[i-1]
        print("round:",round,"=",result)
        round+=1
        
data="1100110100000000110011001111111111110001101010101111000010101010"
des(data,parity_drop,compression,round)