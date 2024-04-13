class Position:
    def __init__(self, row: int, column: int):
        self.row = row
        self.column = column

    def walk_directions(self, row_direction: int, column_direction: int) -> "Position":
        return Position(self.row + row_direction, self.column + column_direction)

    def __eq__(self, other: "Position") -> bool:
        return self.row == other.row and self.column == other.column

    def __str__(self) -> str:
        return f"({self.row}, {self.column})"
