import pkg1
import pkg2

func_overload = pkg1.new("funcs")


@func_overload
def func(a: int):
    return 1


@func_overload
def func(a: int, b: int):
    return 2


t_overload = pkg2.new("t")


@t_overload
def t1(a: int):
    return 1


@t_overload
def t2(a: int, b: str):
    return 2


print(func(1))
print(t_overload.call(1, "2"))
