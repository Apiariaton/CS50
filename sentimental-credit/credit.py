#TODO

def main():

    my_user_input = input("Enter card number: ")
    check_card_type(my_user_input)

def luhn_algo_check(user_input):
    #Phase 1
    total_of_digits = 0
    for i in range(len(user_input) - 2, -2, -2): #16 long card
        print(i)
        print(user_input[i])
        doubled = int(user_input[i]) * 2
        print(f"Doubled is {doubled}")
        if len(str(doubled)) > 1: #Account for \0 null character
            doubled = int(str(doubled)[0]) + int(str(doubled)[1])
            total_of_digits += int(doubled)
        else:
            total_of_digits += int(doubled)
        print(f"Total of digits is {total_of_digits}")
    for i in range(0,len(user_input),2):
        total_of_digits += int(user_input[i])
        print(f"Total of digits is {total_of_digits}")
        print(f"User_input[i] is {user_input[i]}")
    if total_of_digits % 10 == 0:
        return True
    return False


#Master Card - No: 5555555555554444 No: 5105105105105100
#AMEX - Yes
#Visa - No: 4012888888881881 No: 4111111111111111



def check_card_type(user_input):
    #First check which of the cards the number corresponds to
    cards = {"American_Express":{"length":[15],"start":[34,37]},"MasterCard":{"length":[16],"start":[51,52,53,54,55]},"Visa":{"length":[13,16],"start":[4]}}
    global card_type
    card_type = ""
    l_user_input = len(user_input)
    if l_user_input in cards["American_Express"]["length"] and int(user_input[0:2]) in cards["American_Express"]["start"]:
        card_type = "American_Express"
    elif l_user_input in cards["MasterCard"]["length"] and int(user_input[0:2]) in cards["MasterCard"]["start"]:
        card_type = "MasterCard"
    elif l_user_input in cards["Visa"]["length"] and int(user_input[0]) in cards["Visa"]["start"]:
        card_type = "Visa"
    else:
        print("Invalid Card...")
        return False
    print(f"Card type is {card_type}")

    if luhn_algo_check(user_input) == True:
        print(f"Genuine {card_type} card...")
        return True
    else:
        print("Fake card...")
        return False


main()