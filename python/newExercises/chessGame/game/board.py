from game.pieces import Pawn, Rook, Knight, Bishop, King, Queen
from game.color import Color
from game.position import Position
from game.square import BoardSquare
from typing import List

BOARD_SIZE = 8


class ChessBoard:
    def __init__(self):
        self._board: List[List[BoardSquare]] = None

    def create_initial_board(self):
        self._create_empty_board()
        self._arrange_pieces()

    def _create_empty_board(self):
        self._board = []
        color = Color.WHITE
        for row_number in range(BOARD_SIZE):
            self._add_empty_row(row_number, starting_color=color)
            color = Color.opposite(color)

    def _add_empty_row(self, row_number: int, starting_color: Color):
        color = starting_color
        row = []
        for column_number in range(BOARD_SIZE):
            position = Position(row_number, column_number)
            row.append(BoardSquare(position, color, piece=None))
            color = Color.opposite(color)
        self._board.append(row)

    def _arrange_pieces(self):
        self._arrange_first_row_pieces()
        self._arrange_second_row_pieces()

    def _arrange_first_row_pieces(self):
        self._arrange_first_row_black_pieces()
        self._arrange_first_row_white_pieces()

    def _arrange_second_row_pieces(self):
        self._arrange_second_row_black_pieces()
        self._arrange_second_row_white_pieces()

    def _arrange_first_row_black_pieces(self):
        self._board[0][0] = Rook(Color.BLACK)
        self._board[0][1] = Knight(Color.BLACK)
        self._board[0][2] = Bishop(Color.BLACK)
        self._board[0][3] = King(Color.BLACK)
        self._board[0][-4] = Queen(Color.BLACK)
        self._board[0][-3] = Bishop(Color.BLACK)
        self._board[0][-2] = Knight(Color.BLACK)
        self._board[0][-1] = Rook(Color.BLACK)

    def _arrange_first_row_white_pieces(self):
        self._board[-1][0] = Rook(Color.WHITE)
        self._board[-1][1] = Knight(Color.WHITE)
        self._board[-1][2] = Bishop(Color.WHITE)
        self._board[-1][3] = King(Color.WHITE)
        self._board[-1][-4] = Queen(Color.WHITE)
        self._board[-1][-3] = Bishop(Color.WHITE)
        self._board[-1][-2] = Knight(Color.WHITE)
        self._board[-1][-1] = Rook(Color.WHITE)

    def _arrange_second_row_black_pieces(self):
        for square in self._board[1]:
            square.piece = Pawn(Color.BLACK)

    def _arrange_second_row_white_pieces(self):
        for square in self._board[-2]:
            square.piece = Pawn(Color.WHITE)
