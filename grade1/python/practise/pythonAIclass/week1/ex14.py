from sys import argv

script, user_name = argv
prompt = ">"

print(f"Hi {user_name}, I'm the {script} script.")
print("I'd like to ask you a few questions.")
print(f"Do you like me {user_name}")
likes = input(prompt)
print(f"")
