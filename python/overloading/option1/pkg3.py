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
    def __init__(self, name: str, *functions: Function):
        self.name = name
        self.functions: List[Function] = list(functions)

    def add(self, function: Function):
        assert function.name == self.name, f"Can only manage functions with name '{function.name}'"
        self.functions.append(function)

    def find_matches(self, *args, **kwargs):
        return [function for function in self.functions if function.do_arguments_match(*args, **kwargs)]

    def is_signature_registered(self, function: Function):
        for f in self.functions:
            if function.signature == f.signature:
                return True
        return False


class OverloadManager:
    def __init__(self):
        self.managers_by_name: Dict[str, FunctionManager] = {}

    def add(self, function: Function):
        if function.name in self.managers_by_name:
            if self.managers_by_name[function.name].is_signature_registered(function):
                raise ValueError(f"Signature {function.signature} is already registered for function '{function.name}'")
            self.managers_by_name[function.name].add(function)
        else:
            self.managers_by_name[function.name] = FunctionManager(function.name, function)

    def find(self, name: str, *args, **kwargs) -> Function:
        matches = self.managers_by_name[name].find_matches(*args, **kwargs)
        if len(matches) == 0:
            raise ValueError(f"The provided arguments for function '{name}' do not match any signature")
        elif len(matches) > 1:
            raise ValueError(f"The provided arguments for function '{name}' match more than a single signature")
        return matches[0]


manager = OverloadManager()


def pyoverload(f: Callable):
    name = f.__name__
    manager.add(Function(f))

    def wrapper(*args, **kwargs):
        function = manager.find(name, *args, **kwargs)
        return function(*args, **kwargs)

    return wrapper
