from abc import ABC, abstractmethod
from game.color import Color
from game.position import Position


class Piece(ABC):
    def __init__(self, color: Color):
        self.color = color
        self.directions = set()

    @abstractmethod
    def can_move_to(self, current: Position, destination: Position) -> bool:
        """ Return whether or not the piece can move to the destination """
        raise NotImplementedError()

    @abstractmethod
    def can_capture_at(self, current: Position, destination: Position) -> bool:
        """ Return whether or not the piece can capture a piece at the destination """
        raise NotImplementedError()
