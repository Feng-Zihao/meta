
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
            else:
                for r in self.dict[k]:
                    r = GrammarRule(r)

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


class GrammarRule(object):
    def __init__(self, rule_str):
        self.rule_str = rule_str
        self.nodes = []
        rule_str = rule_str.lstrip()
        while rule_str:
            n, rule_str = GrammarNode.parse_rule(rule_str)
            self.nodes.append(n)
            rule_str = rule_str.lstrip()
        print self.nodes

    def __repr__(self):
        s = self.rule_str + "\n"
        s += "\n".join([("    "+repr(n)) for n in self.nodes])
        return s


class GrammarNode(object):
    def __init__(self, rule, lower_limit=1, separator=None):
        self.rule = rule
        self.lower_limit = lower_limit
        self.separator = separator

    def __repr__(self):
        return "<%s ,%s, %d>"%\
                (self.rule, self.separator, self.lower_limit)

    @staticmethod
    def parse_rule(s):
        rule = GrammarNode._accept_string_or_rule(s)
        lower_limit = 1
        separator = None
        s = s[len(rule):]
        if s:
            if s[0] == '{':
                lower_limit = 0
                separator = GrammarNode._accept_string_or_rule(s[1:])
                if s[len(separator)+1] != '}':
                    raise ValueError('"}" missing')
                s = s[len(separator)+2:]
            elif s[0] == '[':
                separator = GrammarNode._accept_string_or_rule(s[1:])
                if s[len(separator)+1] != ']':
                    raise ValueError('"]" missing')
                s = s[len(separator)+2:]
        return GrammarNode(rule, lower_limit, separator), s


    @staticmethod
    def _accept_string_or_rule(s):
        rs = ""
        if s[0] == '"':
            rs = '"'
            rs += re.match(r'[^\s"]+', s[1:]).group(0)
            if s[len(rs)] == '"':
                rs += '"'
            else:
                raise ValueError('\'"\' missing')
        else:
            rs = re.match(r'[^\s"\{\}\[\]]+', s).group(0)
        return rs


grammar = Grammar(open(grammar_path))


