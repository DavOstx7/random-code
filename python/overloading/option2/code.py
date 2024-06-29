import pkg2


@pkg2.funcx
def funcx(a: int):
    return 1


@pkg2.funcx
def funcx(a: int, b: int):
    return 2


@pkg2.tt
def t1(a: int):
    return 1


@pkg2.tt
def t2(a: int, b: str):
    return 2


print(t1(1, "b"))
