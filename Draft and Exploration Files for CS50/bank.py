greeting = input("You walk into a bank... What do you say?")
financial_rewards = ["$0","$20","$100"]
greeting = greeting.strip(" ").lower()

if greeting == "hello":
    print(financial_rewards[0])
elif greeting[0] == "h":
    print(financial_rewards[1])
else:
    print(financial_rewards[2])
