from abc import ABC, abstractmethod
from typing import Optional, Union


class Gate(ABC):
    def __init__(self, output_to: Optional["Gate"] = None):
        self.output_to = output_to

    @abstractmethod
    def is_ready(self) -> bool:
        """ Return whether or not the Gate is ready to be activated. """
        pass

    @abstractmethod
    def calculate_output(self) -> bool:
        """ Calculate the output from the source input/inputs. """

    @abstractmethod
    def receive_input(self, source_input: bool):
        """ Receive input from an external source. Make sure the input/inputs are not already set. """

    def activate(self):
        """
        Check if the Gate is ready to be activated.
        Calculate output from the source input/input.
        Pass the output to the next Gate it if it exists (and activate it), else print the output.
        """

        if not self.is_ready():
            return

        output = self.calculate_output()

        if self.output_to:
            self.output_to.receive_input(output)
            self.output_to.activate()
        else:
            print(f"Output -> {output}")

