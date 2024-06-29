import inspect
from typing import Callable, Dict, Tuple, List

FUNC = Tuple[Callable, inspect.Signature]
NAME_TO_FUNCS: Dict[str, List[FUNC]] = {}


def pyoverload(func: Callable):
    name = func.__name__
    signature = inspect.signature(func)
    if name in NAME_TO_FUNCS:
        if _is_signature_already_registered(name, signature):
            raise ValueError(f"Signature {signature} is already registered for function '{name}'")
        else:
            NAME_TO_FUNCS[name].append((func, signature))
    else:
        NAME_TO_FUNCS[name] = [(func, signature)]

    def wrapper(*args, **kwargs):
        obj = _find_matching_func_obj(name, *args, **kwargs)
        return obj(*args, **kwargs)

    return wrapper


def _is_signature_already_registered(name: str, signature: inspect.Signature) -> bool:
    funcs = NAME_TO_FUNCS[name]
    for _, sig in funcs:
        if sig == signature:
            return True
    return False


def _is_signature_matching(signature: inspect.Signature, *args, **kwargs) -> bool:
    try:
        bound_args = signature.bind(*args, **kwargs)
        bound_args.apply_defaults()

        for name, value in bound_args.arguments.items():
            param = signature.parameters[name]
            if param.annotation != inspect.Parameter.empty:
                if not isinstance(value, param.annotation):
                    return False

        return True
    except (TypeError, ValueError):
        return False


def _find_matching_func_obj(name, *args, **kwargs) -> Callable:
    funcs = NAME_TO_FUNCS[name]
    matches = [obj for obj, sig in funcs if _is_signature_matching(sig, *args, **kwargs)]
    if len(matches) == 0:
        raise ValueError(f"The provided arguments for function '{name}' do not match any signature")
    elif len(matches) == 1:
        return matches[0]
    else:
        raise ValueError(f"The provided arguments for function '{name}' match more than a single signature")
