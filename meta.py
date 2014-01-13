
import re
import string
import sets

grammar_path = 'meta_v0_0_0.grammar'


def is_token(s):
    return re.match(r"[a-z]+", s)


def is_start_symbol(s):
    return re.match(r'[a-z]+', s) or s[0] == '"'


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
                self.dict[k] = map(lambda r: GrammarRule(r), self.dict[k])
                #for r in self.dict[k]:
                #    r = GrammarRule(r)

    def match_token(self, token_name, s):
        rs = re.match(self.dict[token_name], s)
        if not rs:
            return False
        return rs.group(0)

    def construct_start_symbol(self):
        cont = True
        while cont:
            cont = False
            for name in self.dict:
                if is_token(name):
                    continue
                for rule in self.dict[name]:
                    if is_start_symbol(rule.nodes[0].name):
                        continue
                    derived_rule_name = rule.nodes[0].name
                    new_syms = sets.Set(rule.start_syms)
                    for sub_rule in self.dict[derived_rule_name]:
                        new_syms.update(sub_rule.start_syms)
                    if new_syms != rule.start_syms:
                        rule.start_syms = new_syms
                        cont = True

    def print_dict(self):
        for k in sorted(self.dict):
            print k
            if re.match('[a-z]', k):
                print '    ', self.dict[k]
                continue
            for v in self.dict[k]:
                print '    ', v.rule_expr

    def print_start_symbol(self):
        for k in sorted(self.dict):
            print k
            if re.match('[a-z]', k):
                print '    ', self.dict[k]
                continue
            for rule in self.dict[k]:
                print '    ', rule.rule_expr
                print '    ', rule.start_syms


class GrammarRule(object):
    def __init__(self, rule_expr):
        self.rule_expr = rule_expr
        self.nodes = []
        rule_expr = rule_expr.lstrip()
        while rule_expr:
            n, rule_expr = GrammarRuleNode.parse_rule(rule_expr)
            self.nodes.append(n)
            rule_expr = rule_expr.lstrip()
        self.start_syms = sets.Set()
        if is_start_symbol(self.nodes[0].name):
            self.start_syms.add(self.nodes[0].name)
        #print self.nodes
        #print self.start_syms

    def __str__(self):
        s = self.rule_expr + "\n"
        #s += "\n".join([("    "+str(n)) for n in self.nodes])
        return s


class GrammarRuleNode(object):
    def __init__(self, name, lower_limit=1, separator=None):
        self.name = name
        self.lower_limit = lower_limit
        self.separator = separator

    def __str__(self):
        return "<%s ,%s, %d>"%\
                (self.name, self.separator, self.lower_limit)

    @staticmethod
    def parse_rule(s):
        name = GrammarRuleNode._accept_string_or_name(s)
        lower_limit = 1
        separator = None
        s = s[len(name):]
        if s:
            if s[0] == '{':
                lower_limit = 0
                separator = GrammarRuleNode._accept_string_or_name(s[1:])
                if s[len(separator)+1] != '}':
                    raise ValueError('"}" missing')
                s = s[len(separator)+2:]
            elif s[0] == '[':
                separator = GrammarRuleNode._accept_string_or_name(s[1:])
                if s[len(separator)+1] != ']':
                    raise ValueError('"]" missing')
                s = s[len(separator)+2:]
        return GrammarRuleNode(name, lower_limit, separator), s


    @staticmethod
    def _accept_string_or_name(s):
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
#grammar.print_dict()
grammar.construct_start_symbol()
grammar.print_start_symbol()
