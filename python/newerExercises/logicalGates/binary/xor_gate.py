from binary.binary_gate import BinaryGate


class XorGate(BinaryGate):
    def calculate_output(self) -> bool:
        return self.source_inputs[0] != self.source_inputs[1]

