from abc import ABC
from gate import Gate
from typing import Optional


class UnaryGate(Gate, ABC):
    def __init__(self, source_input: bool = None, output_to: Optional["Gate"] = None):
        super().__init__(output_to)
        self.source_input = source_input

    def is_ready(self) -> bool:
        return self.source_input is not None

    def receive_input(self, source_input: bool):
        if self.is_ready():
            raise ValueError("Input Is Already Set!")

        self.source_input = source_input
