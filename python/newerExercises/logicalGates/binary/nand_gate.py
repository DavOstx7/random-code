from binary.binary_gate import BinaryGate


class NandGate(BinaryGate):
    def calculate_output(self) -> bool:
        return not (self.source_inputs[0] and self.source_inputs[1])
