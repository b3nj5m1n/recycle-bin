# Input contains a number of pairs of parentheses, extract each group seperately

stack = []
pairs = []

s = "Outer (First inner (first nested group) group) parentheses (another group)"

for i, char in enumerate(s):
    if char == "(":
        stack.append(i)
    elif char == ")":
        pairs.append((stack.pop(), i))

for pair in pairs:
    print(s[pair[0] : pair[1]+1])

# Extract the group starting at the given index
# This will fail if the starting index has a ) before
# the next ( but I'm too lazy to fix it
def get_group(ii, s):
    stack = []
    for i, char in enumerate(s[ii:]):
        if char == "(":
            stack.append(i)
        elif char == ")":
            j = stack.pop()
            if not stack:
                return (j+ii, i+ii)

test = get_group(19, s)
print(s[test[0] : test[1]+1])
test = get_group(0, s)
print(s[test[0] : test[1]+1])

print("noice")
