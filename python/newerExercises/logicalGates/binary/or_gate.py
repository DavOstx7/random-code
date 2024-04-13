from binary.binary_gate import BinaryGate


class OrGate(BinaryGate):
    def calculate_output(self) -> bool:
        return self.source_inputs[0] or self.source_inputs[1]
