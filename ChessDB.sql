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

INSERT INTO moves (game_id, move_number, move_text) VALUES (1, 1, 'e4');
INSERT INTO moves (game_id, move_number, move_text) VALUES (1, 2, 'e5');
INSERT INTO moves (game_id, move_number, move_text) VALUES (1, 3, 'Nf3');
INSERT INTO moves (game_id, move_number, move_text) VALUES (1, 4, 'Nc6');
INSERT INTO moves (game_id, move_number, move_text) VALUES (1, 5, 'Bb5');
INSERT INTO moves (game_id, move_number, move_text) VALUES (1, 6, 'a6');
INSERT INTO moves (game_id, move_number, move_text) VALUES (1, 7, 'Ba4');
INSERT INTO moves (game_id, move_number, move_text) VALUES (1, 8, 'Nf6');
INSERT INTO moves (game_id, move_number, move_text) VALUES (1, 9, 'O-O');
INSERT INTO moves (game_id, move_number, move_text) VALUES (1, 10, 'Be7');
INSERT INTO moves (game_id, move_number, move_text) VALUES (1, 11, 'Re1');
INSERT INTO moves (game_id, move_number, move_text) VALUES (1, 12, 'b5');
INSERT INTO moves (game_id, move_number, move_text) VALUES (1, 13, 'Bb3');


