import re


# Reads the whole stdin
def readin():
    l = []
    while True:
        try:
            l.append(input())
        except EOFError:
            return "\n".join(l)


text = readin()
print("\\verb") # start verbatim

text = re.sub("^ +$", "", text)
for i in [("\\", "\\b "), ("{", "\\{"), ("}", "\\}"), ("\n\\}\n\n", "\n\\}\\greatsk\n"), ("\n\n", "\n\\sk\n")]:
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


    d = {
        "typ": "bool char signed unsigned short long int ll ld float double void auto string ull".split(),
        "tem": "array vector deque forward_list list set map multiset multimap unordered_set unordered_map unordered_multiset unordered_multimap stack queue priority_queue pair".split(),
        "key": "break case class const continue delete do else for friend goto if inline namespace new private public return static struct switch this typedef using while rep per".split(),
        "con": "true false PI pi INF inf EPS eps NULL MOD MAXN MAXM".split()
    }

    for name in d.keys():
        for kw in d[name]:
            text = repl(kw, name, text)
            text = repl(kw, name, text)


    text = re.sub(r"(^|\W)(-?\d+(U?L?L|(\.\d+)?(e-?\d+)?))($|\W)", r"\1\\con{\2}\6", text)
    l.append(text)
    return "".join(l)

print(highlight(text))
print("\\egroup")
