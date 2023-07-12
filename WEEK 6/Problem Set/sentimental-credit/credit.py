card_str = input("Card Number: ")
lenght_card = len(card_str)
if lenght_card not in [13, 15, 16] or not card_str.isdigit():
    print("INVALID")
    exit(1)

i = lenght_card - 1
sum = 0
sum2 = 0

for index, digit in enumerate(card_str[::-1]):
    if index % 2 == 0:
        sum2 += int(digit)
    else:
        curr_digit = int(digit) * 2
        if curr_digit > 9:
            sum += (curr_digit % 10) + (curr_digit // 10)
        else:
            sum += curr_digit

if (sum + sum2) % 10 == 0:
    if card_str[0:2] in ["51", "52", "53", "54", "55"] and lenght_card == 16:
        print("MASTERCARD")
    elif card_str[0:2] in ["34", "37"] and lenght_card == 15:
        print("AMEX")
    elif card_str[0] == "4" and lenght_card in [13, 16]:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
