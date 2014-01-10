
from meta import *
from nose.tools import assert_equal


def testTokenMatcher():
    params = [
        ('integer', '123', '123'),
        ('integer', '+123a', '+123'),
        ('integer', '-123a', '-123'),
        ('integer', 'aa', False),
        ('integer', '+', False),
        ('integer', '-', False),

        ('identifier', 'abc', 'abc'),
        ('identifier', 'a9_bd', 'a9_bd'),
        ('identifier', '____', '____'),
        ('identifier', '9ad', False),
        ('identifier', '', False),

        ('logicalBinaryOperator', '|||', '||'),
        ('bitwiseBinaryOperator', '^', '^'),
        ('bitwiseBinaryOperator', '||', '|')
    ]
    for p in params:
        assert_equal(grammar.match_token(p[0], p[1]), p[2])
