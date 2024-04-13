from game.pieces.base import Piece
from game.color import Color
from game.position import Position
from typing import Optional


class BoardSquare:
    def __init__(self, position: Position, color: Color, piece: Optional[Piece] = None):
        self.position = position
        self.color = color
        self.piece = piece
