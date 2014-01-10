
import re
import string


grammar_path = 'meta_v0_0_0.grammar'


class Grammar(object):
    def __init__(self, grammar_file):
        key_str = None
        grammar_dict = {}
        for line in grammar_file:
            rawline = line.split('#')[0].rstrip()
            if not rawline:
                continue
            if re.match('[^\s]+', rawline):
                key_str = rawline[:-1]
                grammar_dict[key_str] = []
            else:
                grammar_dict[key_str].append(rawline.strip())
        self.dict = grammar_dict
        for k in self.dict:
            if re.match('[a-z]', k):
                if len(self.dict[k]) != 1:
                    raise ValueError('token invalid')
                self.dict[k] = self.dict[k][0]

    def match_token(self, token_name, s):
        rs = re.match(self.dict[token_name], s)
        if not rs:
            return False
        return rs.group(0)

    def print_dict(self):
        for k in sorted(self.dict):
            print k
            if re.match('[a-z]', k):
                print '    ', self.dict[k]
                continue
            for v in self.dict[k]:
                print '    ', v


class RuleNode(object):
    def __init__(self, rule, lower_limit=1, separator=None):
        self.rule = rule
        self.lower_limit = lower_limit
        self.separator = separator


def parseRule(rule):
    rule = rule.strip()
    node = None
    rs = []
    while rule:
        m = re.match('[ 0-9\s]+', rule)
        if m:
            if not node:
                node = RuleNode(m.group(0))
                rule = rule[len(node.rule):]
                if rule:
                    rs.append(rule)
                    return rs
                if rule[0] == '[':
                    rule.lower_limit = 1


                









#grammar = Grammar(open(grammar_path))
#grammar.print_dict()

newRuleNode('"func{nnn} function "{"')
