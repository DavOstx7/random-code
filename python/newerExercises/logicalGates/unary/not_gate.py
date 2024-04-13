from unary.unary_gate import UnaryGate


class NotGate(UnaryGate):
    def calculate_output(self) -> bool:
        return not self.source_input
