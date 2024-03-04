#!/usr/bin/env python

import json


class Token():
    def __init__(self, type, value):
        self.type = type
        self.value = value

    def __str__(self):
        return f'Token({self.type}, {self.value})'

    def __repr__(self):
        return self.__str__()


class Scanner():
    # Tokens are already lexex. We will just simulate the scanner
    def __init__(self, tokens):
        self.tokens = tokens
        self.current = 0

    def next(self):
        if self.current < len(self.tokens):
            token = self.tokens[self.current]
            self.current += 1
            return token
        return None

    def peek(self):
        if self.current < len(self.tokens):
            return self.tokens[self.current]
        return None

    def __str__(self):
        return f'Scanner({self.tokens})'


class Node():
    def __init__(self):
        pass

    def __str__(self):
        return f'Node()'


class BinaryNode(Node):
    def __init__(self, op, left, right):
        self.op = op
        self.left = left
        self.right = right

    def __str__(self):
        return f'Node({self.op}, {self.left}, {self.right})'


class UnaryNode(Node):
    def __init__(self, op, right):
        self.op = op
        self.right = right

    def __str__(self):
        return f'Node({self.op}, {self.right})'


class Literal(Node):
    def __init__(self, value):
        self.value = value

    def __str__(self):
        return f'Literal({self.value})'

    def __repr__(self):
        return self.__str__()


def parse_expr(scanner: Scanner) -> Node:
    stack = []

    while True:
        tok = scanner.peek()
        if tok is None:
            return None

        if tok.type == 'Punctuation' and tok.value == ';':
            if len(stack) == 1:
                return stack.pop()
            else:
                return None

        scanner.next()

        if tok.type == 'Literal':
            stack.append(Literal(tok.value))
            continue

        if tok.type == 'Punctuation' and tok.value == '(':
            r = parse_expr(scanner)
            if r is None:
                return None
            stack.append(r)
            continue

        if tok.type == 'Punctuation' and tok.value == ')':
            if len(stack) == 1:
                return stack.pop()
            else:
                return None

        if tok.type == 'Operator':
            op = tok.value
            r = parse_expr(scanner)
            if r is None:
                return None
            if len(stack) == 0:
                # Unary operator
                stack.append(UnaryNode(op, r))
                continue
            if len(stack) == 1:
                left = stack.pop()
                stack.append(BinaryNode(op, left, r))
                continue
            else:
                return None

    return None


def main():
    # tokens = [Token('Operator', '-'),
    #           Token('Literal', 2), Token('Punctuation', ';')]
    # (4+4)
    tokens = [Token('Punctuation', '('), Token('Literal', 4),
                Token('Operator', '+'), Token('Literal', 4), Token('Punctuation', ')'), Token('Punctuation', ';')]
    scanner = Scanner(tokens)
    node = parse_expr(scanner)
    print(json.dumps(node, default=lambda o: o.__dict__))


if __name__ == '__main__':
    main()
