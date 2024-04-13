"""
# strip all of the unnecessary duplicate spaces which are not inside of a ''.
# a way for the start parser would be to take an argument string, and search for the first occurrence of the char:'-',
which is not inside a "" or ''. Then you can strip the result.
# a better way for the end parser would be to take an argument string, and search for the last occurrence of the char: '-' or '--',
which is not inside a "" or ''. Then find it or the word after and take it from there and strip the result.

~~~~~~~~ ANOTHER SOLUTION ~~~~~~~~
Make the parser so it parses one after the other (even though it is not as good).
What I mean is:
# parse the starting arguments then remove them
# parse the tags and remove them
# parse the end and remove them

~~~~~~~~ AFTER PARSING ~~~~~~~~
# Maybe make a dict which would be {STARTING: _, BOOL_TAGS: _, NAME_TAGS: _, ENDING: _}
"""

