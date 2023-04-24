CREATE DATABASE chess_db;

USE chess_db;

CREATE TABLE players (
    id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(255) NOT NULL,
    country VARCHAR(255) NOT NULL,
    date_of_birth DATE NOT NULL,
    rating INT NOT NULL
);

CREATE TABLE games (
    id INT PRIMARY KEY AUTO_INCREMENT,
    white_player_id INT NOT NULL,
    black_player_id INT NOT NULL,
    date_played DATE NOT NULL,
    result VARCHAR(10) NOT NULL,
    moves TEXT NOT NULL,
    FOREIGN KEY (white_player_id) REFERENCES players(id),
    FOREIGN KEY (black_player_id) REFERENCES players(id),
);

INSERT INTO players (name, country, date_of_birth, rating)
VALUES ('Magnus Carlsen', 'Norway', '1990-11-30', 2847),
       ('Fabiano Caruana', 'United States', '1992-07-30', 2820),
       ('Ding Liren', 'China', '1992-10-24', 2805),
       ('Ian Nepomniachtchi', 'Russia', '1990-07-14', 2801),
       ('Levon Aronian', 'Armenia', '1982-10-06', 2797),
       ('Wesley So', 'United States', '1993-10-09', 2784),
       ('Alexander Grischuk', 'Russia', '1983-10-31', 2777),
       ('Shakhriyar Mamedyarov', 'Azerbaijan', '1985-04-12', 2770),
       ('Maxime Vachier-Lagrave', 'France', '1990-10-21', 2760),
       ('Anish Giri', 'Netherlands', '1994-06-28', 2759);



USE chess_db;
DELIMITER $$

CREATE PROCEDURE add_player(
    IN p_name VARCHAR(255),
    IN p_country VARCHAR(255),
    IN p_date_of_birth DATE,
    IN p_rating INT
)
BEGIN
    INSERT INTO players (name, country, date_of_birth, rating)
    VALUES (p_name, p_country, p_date_of_birth, p_rating);
END$$

DELIMITER ;

USE chess_db;
DELIMITER $$

CREATE PROCEDURE delete_player(
    IN p_id INT
)
BEGIN
    DELETE FROM players WHERE id = p_id;
END$$

DELIMITER ;

USE chess_db;
DELIMITER $$

CREATE PROCEDURE get_player_games(
    IN p_id INT
)
BEGIN
    SELECT * FROM games
    WHERE white_player_id = p_id OR black_player_id = p_id;
END$$

DELIMITER ;




