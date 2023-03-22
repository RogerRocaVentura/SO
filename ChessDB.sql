CREATE TABLE players (
    id INT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    rating INT,
    country VARCHAR(255),
    dob DATE
);

CREATE TABLE games (
    id INT PRIMARY KEY,
    white_player_id INT NOT NULL,
    black_player_id INT NOT NULL,
    result VARCHAR(10),
    opening VARCHAR(255),
    date_played DATE,
    event VARCHAR(255),
    FOREIGN KEY (white_player_id) REFERENCES players(id),
    FOREIGN KEY (black_player_id) REFERENCES players(id)
);

CREATE TABLE moves (
    game_id INT NOT NULL,
    move_number INT NOT NULL,
    move_text VARCHAR(10) NOT NULL,
    algebraic_notation VARCHAR(10),
    moved_piece VARCHAR(10),
    moved_to_square VARCHAR(10),
    PRIMARY KEY (game_id, move_number),
    FOREIGN KEY (game_id) REFERENCES games(id)
);

INSERT INTO players (id, name) VALUES (1, 'Roger Roca');
INSERT INTO players (id, name) VALUES (2, 'Magnus Carlsen');

INSERT INTO games (id, white_player_id, black_player_id, result) VALUES (1, 1, 2, '1-0');

INSERT INTO moves (game_id, move_number, move_text, algebraic_notation, moved_piece, moved_to_square)
VALUES (1, 14, 'c4', 'c4', 'P', 'c4');

INSERT INTO moves (game_id, move_number, move_text, algebraic_notation, moved_piece, moved_to_square)
VALUES (1, 15, 'd3', 'd3', 'P', 'd3');

INSERT INTO moves (game_id, move_number, move_text, algebraic_notation, moved_piece, moved_to_square)
VALUES (1, 16, 'cxd5', 'cxd5', 'P', 'd5');

INSERT INTO moves (game_id, move_number, move_text, algebraic_notation, moved_piece, moved_to_square)
VALUES (1, 17, 'Nxd5', 'Nxd5', 'N', 'd5');

INSERT INTO moves (game_id, move_number, move_text, algebraic_notation, moved_piece, moved_to_square)
VALUES (1, 18, 'Bxd5', 'Bxd5', 'B', 'd5');

INSERT INTO moves (game_id, move_number, move_text, algebraic_notation, moved_piece, moved_to_square)
VALUES (1, 19, 'Qxd5', 'Qxd5', 'Q', 'd5');

INSERT INTO moves (game_id, move_number, move_text, algebraic_notation, moved_piece, moved_to_square)
VALUES (1, 20, 'Rad1', 'Rad1', 'R', 'a1');




