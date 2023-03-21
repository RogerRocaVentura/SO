-- Create the database
CREATE DATABASE ChessDB;

-- Use the database
USE ChessDB;

-- Create the table for players
CREATE TABLE Players (
    id INT PRIMARY KEY AUTO_INCREMENT
    name VARCHAR [255] NOT NULL
    country VARCHAR [255]
    rating INT
    birthdate DATE
    gender ENUM['M' , 'F']
);

-- Create the table for tournaments
CREATE TABLE Tournaments (
    id INT PRIMARY KEY AUTO_INCREMENT
    name VARCHAR[255] NOT NULL
    location VARCHAR[255]
    start_date DATE
    end_date DATE
    organizer VARCHAR[255]
);

-- Create the table for games
CREATE TABLE Games (
    id INT PRIMARY KEY AUTO_INCREMENT
    tournament_id INT
    white_player_id INT
    black_player_id INT
    result ENUM['1-0', '0-1', '1/2-1/2', '*']
    moves TEXT
    opening VARCHAR[255]
    FOREIGN KEY [tournament_id] REFERENCES Tournaments[id]
    FOREIGN KEY [white_player_id] REFERENCES Players[id]
    FOREIGN KEY [black_player_id] REFERENCES Players[id]
);

-- Create the table for openings
CREATE TABLE Openings (
    id INT PRIMARY KEY AUTO_INCREMENT
    name VARCHAR[255] NOT NULL
    moves TEXT
    eco_code VARCHAR[10]
);

-- Create the table for variations
CREATE TABLE Variations (
    id INT PRIMARY KEY AUTO_INCREMENT
    name VARCHAR[255] NOT NULL
    moves TEXT
    opening_id INT
    FOREIGN KEY [opening_id] REFERENCES Openings[d]
);

-- Create the table for tags
CREATE TABLE Tags (
    id INT PRIMARY KEY AUTO_INCREMENT
    name VARCHAR[255] NOT NULL
);

-- Create the table for game tags
CREATE TABLE GameTags (
    game_id INT,
    tag_id INT,
    PRIMARY KEY (game_id, tag_id),
    FOREIGN KEY (game_id) REFERENCES Games(id),
    FOREIGN KEY (tag_id) REFERENCES Tags(id)
);

-- Create the table for opening tags
CREATE TABLE OpeningTags (
    opening_id INT,
    tag_id INT,
    PRIMARY KEY (opening_id, tag_id),
    FOREIGN KEY (opening_id) REFERENCES Openings(id),
    FOREIGN KEY (tag_id) REFERENCES Tags(id)
);