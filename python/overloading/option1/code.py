from pkg1 import pyoverload
from pkg2 import pyoverload
from pkg3 import pyoverload


@pyoverload
def funcx(a: int):
    return 1


@pyoverload
def funcx(a: int, b: int):
    return 2


@pyoverload
def t1(a: int):
    return 1


@pyoverload
def t1(a: int, b: str):
    return 2


print(t1(1))
