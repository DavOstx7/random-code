from game.pieces.base import Piece, Color, Position


class Pawn(Piece):
    def __init__(self, color: Color):
        super().__init__(color)
        self.directions = [(1, 1)]
        self.has_moved = False

    def can_move_to(self, current: Position, destination: Position) -> bool:
        if not self.has_moved:
            pass

    def can_capture(self, current: Position, destination: Position):
        return move_up_left(current, ONCE) or move_up()
        raise NotImplementedError()
