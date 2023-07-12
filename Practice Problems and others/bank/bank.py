greeting = (input("Greeting: ")).lower().strip()

if greeting.startswith('h'):
    if 'hello' in greeting:
        print("$0")
    else:
        print("$20")
else:
    print("$100")