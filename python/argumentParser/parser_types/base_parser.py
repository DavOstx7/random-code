from abc import ABC, abstractmethod


class BaseParserType(ABC):
    @abstractmethod
    def parse(self):
        pass

    @abstractmethod
    def get_arguments(self):
        pass
