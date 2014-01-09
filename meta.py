
import re

integer = re.compile(r'(\+|\-)?[0-9]+')
identifier = re.compile(r'[a-zA-Z_][0-9a-zA-Z_]*')
newline = re.compile(r'[\r\n]+')
whitespace = re.compile(r'[ \r\n\t\v\f]+')
arithmeticOperator = re.compile(r'[+\-*/]')
logicalBinaryOperator = re.compile(r'&&|==|!=|\|\|')
logicalUnaryOperator = re.compile(r'!')
compareOperator = re.compile(r'<|>')
bitwiseBinaryOperator = re.compile(r'<<<|>>>|<<|>>|\^|\&|\|')

def try_token(src, target):
    if type(target) is type(re.compile('dummy')):
        m = target.match(src)
    elif isinstance(target, str):
        m = re.match(target, src)
    if m is not None and len(m.group(0)) > 0:
        return m.group(0)
    return None





