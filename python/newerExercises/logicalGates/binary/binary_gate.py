from abc import ABC
from gate import Gate
from typing import Optional, List


class BinaryGate(Gate, ABC):
    def __init__(self, source_inputs: List[bool] = None, output_to: Optional["Gate"] = None):
        super().__init__(output_to)
        self.source_inputs = source_inputs if source_inputs else [None, None]

    def is_ready(self) -> bool:
        return self.source_inputs[0] is not None and self.source_inputs[1] is not None

    def receive_input(self, source_input: bool):
        if self.is_ready():
            raise ValueError("Inputs Are Already Set!")

        if self.source_inputs[0] is None:
            self.source_inputs[0] = source_input
        else:
            self.source_inputs[1] = source_input

