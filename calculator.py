from cs50 import get_int, get_float, get_string

import ast




acceptable_units = ['0','1','2','3','4','5','6','7','8','9','+','-','/','*']
operators = ['-','+','/','*']
non_duplicable_operators = ['+','/','*']
numbers_and_minus_sign = ["0123456789+-"]

   #"0","1","2","3","4","5","6","7","8","9","-"]


def calculate(key,number_1_string,number_2_string):
        print("Key:",key)
        print("This is number 1 string",number_1_string)
        print("This is number 2 string",number_2_string)
        number_1_string = int(number_1_string)
        number_2_string = int(number_2_string)
        number_3_string = 0
        if key == "/":
            number_3_string = number_1_string / number_2_string
        elif key == "*":
            number_3_string = number_1_string * number_2_string
        elif key == "+":
            number_3_string = number_1_string + number_2_string
        elif key == "-":
            number_3_string = number_1_string - number_2_string
        number_3_string = str(number_3_string)
        return number_3_string



def key_calculate(key,string):
    print("String is: ", string)
    char = 0





"""
    while char < len(string):
        if string[char] == key:
            #Back number
            print("Char is", char)
            bn = char - 1
            print("Bn is a string")
            yes = type(string[bn]) is str
            print(yes)
            while string[bn] in numbers_and_minus_sign and bn > -1:
                bn -= 1
            #Front number
            fn = char + 1
            while string[fn] in numbers_and_minus_sign and fn < len(string):
                fn += 1
            print("Bn is",bn,"Fn is", fn)
            nonlocal str_value_1 = string
            str_value_1 = string[bn + 1:char - 1] #Invalid sections
            nonlocal str_value_2 = string
            str_value_2 = string[char + 1: fn - 1]
            print("This is number_1_string_in_key_calculate",str_value_1)
            print(string[char + 1: fn - 1])
            new_value = calculate(key, string[bn + 1:char - 1],string[char + 1: fn - 1])
            string = string[0:bn] + new_value + string[fn:len(string)]
        char += 1
    return string
"""


#234234234 -- 23423423 4234// 234234 * 234234 + 234234234



def take_input():
    nonlocal string
    string = input("Enter sequence to calculate (+,-,/,* only, no brackets)")
    return string


def clean_arithmetic_sequence(string):
    #1. Remove unwanted characters
    for char in string:
        if char not in acceptable_units:
            string = string.replace(char,"")
    print(string)

    #2. Remove contiguous duplicates with exception of minuses, which require converting to plus
    pos = 0
    while pos < len(string):
        if string[pos] in non_duplicable_operators and string[pos] == string[pos + 1]:
            string = string[0:pos - 1] + string[pos + 1:len(string)]
        elif string[pos] == '-' and string[pos + 1] == '-':
            string = string[0:pos - 1] + "+" + string[pos + 2:len(string)]
        pos += 1

    print(string)
    return string



def produce_answer(string):
    #1. Which operators are present?
    o_present = {"divide":"N","times":"N","add":"N","subtract":"N"}
    for char in string:
        if char == "/":
            o_present["/"] = "Y"
        elif char == "*":
            o_present["*"] = "Y"
        elif char == "+":
            o_present["+"] = "Y"
        elif char == "-":
            o_present["-"] = "Y"

    #2. Move sequentially, converting numerical sequences to single numbers until last rel operation reached
    for key in o_present:
        if o_present[key] == "Y" and key == "/":
            string = key_calculate(key,string)
        elif o_present[key] == "Y" and key == "*":
            string = key_calculate(key,string)
        elif o_present[key] == "Y" and key == "+":
            string = key_calculate(key,string)
        elif o_present[key] == "Y" and key == "-":
             string = key_calculate(key,string)




    #3. Return the value of the calculation
    print(string)







answer = take_input()
answer = clean_arithmetic_sequence(string)
produce_answer(string)


















