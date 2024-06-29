import inspect
from typing import Callable, Dict, List


class Function:
    def __init__(self, obj: Callable):
        self.obj = obj
        self.name = obj.__name__
        self.signature = inspect.signature(obj)

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


class OverloadManager:
    def __init__(self):
        self.data: Dict[str, List[Function]] = {}

    def add(self, function: Function):
        if function.name in self.data:
            if self._is_signature_already_registered(function):
                raise ValueError(f"Signature {function.signature} is already registered for function '{function.name}'")
            self.data[function.name].append(function)
        else:
            self.data[function.name] = [function]

    def find(self, name: str, *args, **kwargs) -> Function:
        functions = self.data[name]
        matches = [function for function in functions if function.do_arguments_match(*args, **kwargs)]
        if len(matches) == 0:
            raise ValueError(f"The provided arguments for function '{name}' do not match any signature")
        elif len(matches) > 1:
            raise ValueError(f"The provided arguments for function '{name}' match more than a single signature")
        return matches[0]

    def _is_signature_already_registered(self, function: Function):
        functions = self.data[function.name]
        for f in functions:
            if f.signature == function.signature:
                return True
        return False


manager = OverloadManager()


def pyoverload(f: Callable):
    name = f.__name__
    manager.add(Function(f))

    def wrapper(*args, **kwargs):
        function = manager.find(name, *args, **kwargs)
        return function(*args, **kwargs)

    return wrapper
