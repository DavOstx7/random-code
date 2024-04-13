from binary.binary_gate import BinaryGate


class AndGate(BinaryGate):
    def calculate_output(self) -> bool:
        return self.source_inputs[0] and self.source_inputs[1]
