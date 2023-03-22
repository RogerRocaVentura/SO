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





