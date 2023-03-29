CREATE TABLE Usuarios (
    IdUsuario INT PRIMARY KEY,
    Nombre VARCHAR(50) NOT NULL
);
CREATE TABLE Actividades (
    IdActividad INT PRIMARY KEY,
    Nombre VARCHAR(50) NOT NULL,
    Barrio VARCHAR(50) NOT NULL
);
CREATE TABLE Participaciones (
    IdUsuario INT,
    IdActividad INT,
    Puntuacion INT,
    PRIMARY KEY(IdUsuario, IdActividad),
    FOREIGN KEY (IdUsuario) REFERENCES Usuarios(IdUsuario),
    FOREIGN KEY (IdActividad) REFERENCES Actividades(IdActividad)
);
SELECT Actividades.Nombre 
FROM Actividades 
INNER JOIN Participaciones ON Actividades.IdActividad = Participaciones.IdActividad 
WHERE Actividades.Barrio = 'Sants' AND Participaciones.Puntuacion >= 4;
