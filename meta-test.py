
from meta import *
import nose
from nose.tools import assert_equal


def test_integer_tokenizer():
    assert_equal(try_token('-123abc', integer), '-123')
    assert_equal(try_token('+123abc', integer), '+123')
    assert_equal(try_token('123', integer), '123')
    assert_equal(try_token('abc', integer), None)
    assert_equal(try_token('+', integer), None)
    assert_equal(try_token('-', integer), None)

def test_identifier_tokenizer():
    assert_equal(try_token('abc', identifier), 'abc')
    assert_equal(try_token('_abc', identifier), '_abc')
    assert_equal(try_token('123', identifier), None)

def test_newline_tokenizer():
    assert_equal(try_token('\r\nab', newline), '\r\n')
    assert_equal(try_token('09\r\nab', newline), None)

def test_operator_tokenizer():
    assert_equal(try_token('|||', logicalBinaryOperator), '||')
    assert_equal(try_token('|', logicalBinaryOperator), None)
    assert_equal(try_token('>>>', bitwiseBinaryOperator), '>>>')
    assert_equal(try_token('>>', bitwiseBinaryOperator), '>>')
    assert_equal(try_token('^', bitwiseBinaryOperator), '^')
    assert_equal(try_token('&', bitwiseBinaryOperator), '&')
    assert_equal(try_token('|', bitwiseBinaryOperator), '|')
