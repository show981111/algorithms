import random

# Generate a random two-digit number
a = random.randint(10, 99)
b = random.randint(10, 99)

print(f"{a} * {b} = ?")
while True:
    user_input = input("Enter a number: ")
    if a * b == int(user_input):
        print("CORRECT")
        break
    print("WRONG!")
