import re


def readin():
    l = []
    while True:
        try:
            l.append(input())
        except EOFError:
            return "\n".join(l)


text = readin()
print("\\verb")
for i in [("\\", "\\b "), ("{", "\\{"), ("}", "\\}"), ("\n}\n", "\n\\greatsk\n"), ("\n\n", "\n\\sk\n")]:
    text = text.replace(i[0], i[1])

def highlight(text):
    def sp(begin, end, name, t):
        if begin not in t:
            return None

        pre, post = t.split(begin, 1)
        post = post.split(end, 1)
        if len(post) == 1:
            post.append("")

        # The recursion level will be at most 5
        return (highlight(pre) + "\\%s{%s%s%s}" % (name, begin, post[0], end), post[1])

    l = []
    while True:
        for b, e, n in [("//", "\n", "com"), ("/*", "*/", "com"), ("#", "\n", "dir"), ("\"", "\"", "str"), ("'", "'", "str")]:
            res = sp(b, e, n, text)
            if res is not None:
                l.append(res[0])
                text = res[1]
                break
        else:
            break

    def repl(word, name, text):
        return re.sub(r"(^|\W)(%s)($|\W)" % word, r"\1\\%s{%s}\3" % (name, word), text)


    for i in ["int", "char", "vector", "string", "map", "set", "ll", "ld", "pair", "auto", "bool", "unsigned", "signed", "short", "unordered_map", "unordered_set", "void"]:
        text = repl(i, "typ", text)

    for i in ["auto", "for", "while", "if", "else", "switch", "case", "break", "continue", "do", "const", "static", "public", "return", "typedef", "rep", "per"]:
        text = repl(i, "key", text)

    for i in ["true", "false", "PI", "pi", "INF", "inf", "eps", "EPS", "epsilon", "EPSILON", "INFINITY", "infinity"]:
        text = repl(i, "con", text)

    text = re.sub(r"(^|\W)(-?\d+(\.\d+)?(e-?\d+)?)($|\W)", r"\1\\con{\2}\5", text)
    l.append(text)
    return "".join(l)

print(highlight(text))
print("\\egroup")
