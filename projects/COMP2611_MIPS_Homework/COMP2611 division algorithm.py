# COMP2611 Division algorithm calculator

# for 8-bit dividend and 8-bit divisor
D=19
R=115
R*=2
R_0=""
# 0. 00000000 01110011
# 1a. 00000000 11100110
    # 1b. 00000000 11100110 (undo)
    # 1c. 00000001 11001100 (R)
    # 2a. 00000001 11001100
    # 2b. 00000001 11001100 (undo)
    # 2c. 00000011 10011000 (R)
    # 3a. 00000011 10011000
    # 3b. 00000011 10011000 (undo)
    # 3c. 00000111 00110000 (R)
    # 4a. 00000111 00110000
    # 4b. 00000111 00110000 (undo)
    # 4c. 00001110 01100000 (R)
    # 5a. 00001110 01100000 
    # 5b. 00001110 01100000 (undo)
    # 5c. 00011100 11000000 (R)
    # 6a. 00001001 11000000 
    # 6b. 00010011 10000001 
print("{0:016b}" .format(R))
print("=====")
for i in range(0,8):
    print("i={}" .format(i+1))
    leftR = (R//(2**8))-D
    print("left(R)={} or {}" .format(leftR, bin(leftR&0b11111111))) # 8 bits because we flip bits
    if leftR>=0:
        R=(leftR*(2**8))+(R%(2**8))
        R*=2
        R+=1
    else:
        R*=2
    R_0+=str(R%2)
    print("R_0 = {}" .format(R_0))
    print("{0:016b}" .format(R))
    print("=====")
# adjustment shift
Q=R//(2**8)
Q=Q//2
R=R%(2**8)
R+=Q*(2**8)
print("{0:016b}" .format(R))
print("R_0 {}" .format(R_0))
