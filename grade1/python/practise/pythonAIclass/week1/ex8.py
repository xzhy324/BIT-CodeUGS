formatter = "{0} {2} {1} {3}"

print(formatter.format(1,2,3,4))
print(formatter)
print(formatter.format('one','two','three','four'))
print(formatter.format(True,False,True,False))
print(formatter.format(formatter,formatter,formatter,formatter))
print(formatter.format("and ",'that','counts','well'))