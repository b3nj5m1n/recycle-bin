import re

# Take a string of a mathematical expression and parse it
# Only supports +,-,*,/ and =

tests = [
    "x+-5.0",
    "3.00-1",
    "2*-4005",
    "-7/3    x",
    "x = -5*-4*y",
    "-4.35     *        y",
    "5x",
]

class m_ex:
    stack = []
    def __init__(self, expression):
        self.stack = []
        self.history_num = []
        self.history_opr = []
        self.history_dot = []
        for char in expression:
            if self.is_number(char) > 0:
                if self.is_new_symbol(char):
                    self.stack.append(char)
                else:
                    if self.is_implicit_mult(char):
                        self.stack.append('*')
                        self.stack.append(char)
                    else:
                        self.stack[-1] = self.stack[-1] + char
                self.history_num.append(len(self.stack))
            if self.is_operator(char):
                self.stack.append(char)
                self.history_opr.append(len(self.stack))
            if self.is_dot(char):
                self.stack[-1] = self.stack[-1] + char
                self.history_dot.append(len(self.stack))
        print(self.stack)
    def is_implicit_mult(self, num):
        if self.is_number(self.stack[-1]) == 0:
            return False
        if not self.is_number(self.stack[-1]) == self.is_number(num):
            return True
        return False
    def is_new_symbol(self, num):
        # If the last token was a number
        if len(self.history_num) > 0 and self.history_num[-1] == len(self.stack):
            return False
        # If the last operator was immediately followed by another operator
        if len(self.history_opr) >= 2 and self.history_opr[-1] - self.history_opr[-2] == 1 and self.history_opr[-1] == len(self.stack):
            # Make sure the last operator was only an operator and not something like -4
            if len(self.stack[-2]) == 1:
                return False
        # If there is a dot and an operator in the history and the last dot is before the last operator
        if len(self.history_dot) > 0 and len(self.history_opr) > 0 and self.history_dot[-1] > self.history_opr[-1]:
            return False
        # If there is a dot but not an operator in the history
        if len(self.history_dot) > 0 and len(self.history_opr) == 0:
            return False
        # If the first token was an operator
        if len(self.history_opr) > 0 and self.history_opr[0] == 1 and len(self.stack) == 1:
            return False
        return True
        
    def is_number(self, char):
        # result will be 1 if it's a number, 2 if it's a variable
        result = 1 if bool(re.search('[0-9]', char)) else (2 if bool(re.search('[a-z]', char)) else 0)
        return result
    def is_operator(self, char):
        return bool(re.search('[\/\+\-\*=]', char))
    def is_dot(self, char):
        return char == '.'
        


# test1 = m_ex(tests[-1])
for test in tests:
    m_ex(test)
