import re
from parser_types.base_parser import BaseParserType
from typing import List, Union
from exceptions.parser_exception import ParserError
from consts import EMPTY_RESULT, EMPTY_ARGUMENTS

PATTERN = "\s((?:\w+\s*)+)\s*$"


class EndParser(BaseParserType):
    def __init__(self, arguments: Union[str, List[str]]) -> None:
        if type(arguments) == list:
            self.arguments = " ".join(arguments)
        elif type(arguments) == str:
            self.arguments = arguments
        else:
            raise ParserError("The argument parameter needs to be a string or a list of strings")
        self.parsed = False


    def parse(self) -> None:
        regex_result = re.findall(PATTERN, self.arguments)
        if regex_result == EMPTY_RESULT:
            self.ending_arguments = EMPTY_ARGUMENTS
        else:
            [self.ending_arguments] = regex_result
        self.parsed = True

    def get_list_of_arguments(self) -> List[str]:
        if not self.parsed:
            raise ParserError(f"The parsing needs to take place before a return can happen!")
        return self.ending_arguments.split()

    def get_arguments(self):
        if not self.parsed:
            raise ParserError(f"The parsing needs to take place before a return can happen!")
        return self.ending_arguments

if __name__ == "__main__":
    parser = EndParser("this is the start -ab -t -name dav --age 11 this is the end")
    parser.parse()
    print(parser.get_arguments())
    print(parser.get_list_of_arguments())

