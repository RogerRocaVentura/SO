using System;
using System.Data;
using MySql.Data.MySqlClient;

namespace ChessDBClient
{
    class Program
    {
        static void Main(string[] args)
        {
            string connectionString = "server=localhost;user=root;database=ChessDB;port=3306;password=yourpassword";
            MySqlConnection connection = new MySqlConnection(connectionString);
            
            try
            {
                connection.Open();
                
                // Insert a new player
                Console.WriteLine("Inserting a new player...");
                MySqlCommand command = new MySqlCommand("INSERT INTO Players(name, country, rating, birthdate, gender) VALUES(@name, @country, @rating, @birthdate, @gender)", connection);
                command.Parameters.AddWithValue("@name", "Magnus Carlsen");
                command.Parameters.AddWithValue("@country", "Norway");
                command.Parameters.AddWithValue("@rating", 2847);
                command.Parameters.AddWithValue("@birthdate", new DateTime(1990, 11, 30));
                command.Parameters.AddWithValue("@gender", "M");
                int rowsAffected = command.ExecuteNonQuery();
                Console.WriteLine("{0} row(s) affected", rowsAffected);
                
                // Retrieve all players
                Console.WriteLine("Retrieving all players...");
                command = new MySqlCommand("SELECT * FROM Players", connection);
                MySqlDataReader reader = command.ExecuteReader();
                while (reader.Read())
                {
                    Console.WriteLine("{0} - {1} ({2})", reader["id"], reader["name"], reader["country"]);
                }
                reader.Close();
                
                // Update a player's rating
                Console.WriteLine("Updating a player's rating...");
                command = new MySqlCommand("UPDATE Players SET rating = @rating WHERE name = @name", connection);
                command.Parameters.AddWithValue("@rating", 2851);
                command.Parameters.AddWithValue("@name", "Magnus Carlsen");
                rowsAffected = command.ExecuteNonQuery();
                Console.WriteLine("{0} row(s) affected", rowsAffected);
                
                // Delete a player
                Console.WriteLine("Deleting a player...");
                command = new MySqlCommand("DELETE FROM Players WHERE name = @name", connection);
                command.Parameters.AddWithValue("@name", "Magnus Carlsen");
                rowsAffected = command.ExecuteNonQuery();
                Console.WriteLine("{0} row(s) affected", rowsAffected);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            finally
            {
                connection.Close();
            }
        }
    }
}
 