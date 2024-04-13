from gate import Gate
from binary import AndGate, OrGate
from unary import NotGate


def activate_gates(*gates: Gate):
    for gate in gates:
        gate.activate()


def input_ex(*inputs: bool):
    inner_or_gate = OrGate()
    outer_or_gate = OrGate([inputs[0], inputs[1]], inner_or_gate)
    outer_and_gate = AndGate([inputs[2], inputs[3]], inner_or_gate)

    activate_gates(outer_or_gate, outer_and_gate)


def bonus_ex(*inputs: bool):
    inner_or_gate = OrGate()
    outer1_or_gate = OrGate([None, inputs[4]], inner_or_gate)
    outer1_not_gate = NotGate(inputs[5], inner_or_gate)
    outer2_or_gate = OrGate([None, None], outer1_or_gate)
    outer3_or_gate = OrGate([inputs[0], inputs[1]], outer2_or_gate)
    outer3_and_gate = AndGate([inputs[2], inputs[3]], outer2_or_gate)

    activate_gates(outer3_or_gate, outer3_and_gate, outer1_not_gate)


input_ex(False, False, False, False)
input_ex(False, False, False, True)
input_ex(False, False, True, False)
input_ex(False, False, True, True)
input_ex(False, True, False, False)
input_ex(False, True, False, True)
input_ex(False, True, True, False)
input_ex(False, True, True, True)
input_ex(True, False, False, False)

print('-' * 50)

bonus_ex(False, False, False, True, False, True)
