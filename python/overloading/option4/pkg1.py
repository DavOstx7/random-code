import inspect
from typing import Callable, Dict, List


class Function:
    def __init__(self, obj: Callable):
        self.obj = obj
        self.signature = inspect.signature(obj)

    @property
    def name(self) -> str:
        return self.obj.__name__

    def do_arguments_match(self, *args, **kwargs) -> bool:
        try:
            bound_args = self.signature.bind(*args, **kwargs)
            bound_args.apply_defaults()

            for name, value in bound_args.arguments.items():
                param = self.signature.parameters[name]
                if param.annotation != inspect.Parameter.empty:
                    if not isinstance(value, param.annotation):
                        return False

            return True
        except (TypeError, ValueError):
            return False

    def __call__(self, *args, **kwargs):
        return self.obj(*args, **kwargs)


class FunctionManager:
    def __init__(self, functions: List[Function]):
        self.functions: List[Function] = list(functions)

    def add(self, function: Function):
        self.functions.append(function)

    def find_matches(self, name: str, *args, **kwargs):
        return [function for function in self.functions if function.do_arguments_match(*args, **kwargs)
                and function.name == name]

    def is_signature_registered(self, function: Function):
        for f in self.functions:
            if function.signature == f.signature:
                return True
        return False


class OverloadManager:
    def __init__(self):
        self.managers_by_group: Dict[str, FunctionManager] = {}

    def add(self, group: str, function: Function):
        if group in self.managers_by_group:
            if self.managers_by_group[group].is_signature_registered(function):
                raise ValueError(f"Signature {function.signature} is already registered in group '{group}'")
            self.managers_by_group[group].add(function)
        else:
            self.managers_by_group[group] = FunctionManager([function])

    def find(self, group: str, name: str, *args, **kwargs) -> Function:
        matches = self.managers_by_group[group].find_matches(name, *args, **kwargs)
        if len(matches) == 0:
            raise ValueError(f"The provided arguments for group|name '{group}'|'{name}' do not match any signature")
        elif len(matches) > 1:
            raise ValueError(f"The provided arguments for group|name '{group}'|'{name}' "
                             f"match more than a single signature")
        return matches[0]


manager = OverloadManager()


def new(group: str):
    return pyoverload(group)


def pyoverload(group: str):
    def decorator(f: Callable):
        name = f.__name__
        manager.add(group, Function(f))

        def wrapper(*args, **kwargs):
            function = manager.find(group, name, *args, **kwargs)
            return function(*args, **kwargs)

        return wrapper

    return decorator
