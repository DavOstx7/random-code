from enum import Enum


class Color(Enum):
    WHITE = "WHITE"
    BLACK = "BLACK"

    @staticmethod
    def opposite(color: "Color") -> "Color":
        if color == Color.WHITE:
            return Color.BLACK
        else:
            return Color.WHITE
