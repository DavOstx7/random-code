import pkg


def func1(a: int):
    return 1


def func2(a: int, b: int):
    return 2


pkg.add("funcs", func1, func2)


def t1(a: int):
    return 1


def t2(a: int, b: str):
    return 2


pkg.add("ts", t1, t2)

print(pkg.call("tss", 1, "b"))
