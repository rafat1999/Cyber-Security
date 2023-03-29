def extend_to_48_bits(binary_value):
    # E-bit selection permutation table
    e_table = [32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
               16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1]

    # perform the E-bit selection permutation
    extended_value = ''.join([binary_value[i - 1] for i in e_table])

    # return the extended value as a binary string
    return extended_value


# example usage
binary_value = input("Enter 32 bit value: ")
extended_value = extend_to_48_bits(binary_value)
print(extended_value)