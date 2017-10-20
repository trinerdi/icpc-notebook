import re
import sys


text = sys.stdin.read()
print("\\verb") # start verbatim

# Handle whitespace, blank lines and special characters
text = re.sub("^ +$", "", text)
for i in [("\\", "\\b "), ("{", "\\{"), ("}", "\\}"), ("\n\\}\n\n", "\n\\}\\greatsk\n"), ("\n\n", "\n\\sk\n")]:
    text = text.replace(i[0], i[1])


def highlight(text):
    def sp(begin, end, name, t):
        """Highlight the first occurence of [begin]text[end] in text."""
        if begin not in t:
            return None

        pre, post = t.split(begin, 1)
        post = post.split(end, 1)
        if len(post) == 1:
            post.append("")

        pre, text, post = pre, post[0], post[1]

        # The recursion level will be at most 5
        return (highlight(pre) + "\\%s{%s%s%s}" % (name, begin, text, end), post)

    l = []
    while True:
        # The order is important: /* "string" */ will be highlighted as a comment
        # TODO: preprocessor directives should be ^#.*, but we don't support regexes here
        for b, e, n in [("//", "\n", "com"), ("/*", "*/", "com"), ("#", "\n", "dir"), ("\"", "\"", "str"), ("'", "'", "str")]:
            res = sp(b, e, n, text)
            if res is not None:
                l.append(res[0])
                text = res[1]
                break
        else:
            break

    def repl(words, name, text):
        return re.sub(r"(^|\W)(%s)((?= )|$|\W)" % words, r"\1\\%s{\2}\3" % (name), text)


    # Types, templated types, keywords, constants
    d = {
        "typ": "bool char signed unsigned short long int ll ld float double void auto string ull",
        "tem": "array vector deque forward_list list set map multiset multimap unordered_set unordered_map unordered_multiset unordered_multimap stack queue priority_queue pair",
        "key": "break case class const continue delete do else for friend goto if inline namespace new private public return static struct switch this typedef using while rep per FOR",
        "con": "true false PI pi INF inf EPS eps NULL MOD MAXN MAXM"
    }

    for name in d.keys():
        text = repl(d[name].replace(" ", "|"), name, text)


    text = re.sub(r"(^|\W)(-?\d+(U?L?L|(\.\d+)?(e-?\d+)?))((?= )|$|\W)", r"\1\\con{\2}\6", text)
    l.append(text)
    return "".join(l)

print(highlight(text))
print("\\egroup")
