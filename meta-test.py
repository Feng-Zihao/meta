
from meta import *
from nose.tools import assert_equal


def test_token_matcher():
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

def test_grammar_parser():
    params = [
        ('"for"{","}', '"for"', '","', 0),
        ('identifier[newline]', 'identifier', 'newline', 1),
        ('","{newline}', '","', 'newline', 0),
        ('newline', 'newline', None, 1),
        ('"[]"["[]"]', '"[]"', '"[]"', 1)
        ]
    for p in params:
        n, s = GrammarRuleNode.parse_rule(p[0])
        assert_equal(n.name, p[1])
        assert_equal(n.separator, p[2])
        assert_equal(n.lower_limit, p[3])


for k in sorted(grammar.dict):
    if re.match('[a-z]', k):
        continue
    print k
    for v in grammar.dict[k]:
        print v

